#!/usr/bin/env bash
# SPDX-License-Identifier: LGPL-2.1-or-later
# Taken from the JukeDial project (same author): its tools/fatfs_exfat/make_fatfs.sh, paths adapted to this repo. Comments below still say "jc" / JukeDial where they were written there.
# FatFs with exFAT: a generated copy of $IDF_PATH/components/fatfs in idf/.generated/fatfs_exfat/fatfs (git-ignored, never committed) with exactly
# four edits, each of which must match once (else exit 1: an IDF upgrade fails loudly instead of building without exFAT):
#   src/ffconf.h      FF_FS_EXFAT 0 -> 1   (IDF hard-codes it, no Kconfig switch)
#                     FF_USE_LABEL CONFIG_FATFS_USE_LABEL -> 1 (f_setlabel: the card format writes the volume label JUKEDIAL, cardfmt 2026-11-14;
#                     also, with exFAT on, ff.c dir_read uses it in a C `if`, where an undefined CONFIG_ macro would not build)
#   vfs/vfs_fat.c     st->st_size = f_size(file);   and   st->st_size = info->fsize;
#                     a size above 0xFFFFFFFF is stored as 0xFFFFFFFF (-1 in the target's 32-bit signed off_t) instead of wrapping
# app/CMakeLists.txt puts the directory in EXTRA_COMPONENT_DIRS (a project component named fatfs replaces IDF's). A stamp (hash of the
# IDF sources copied + of this script) makes a second run a no-op. `--selftest` runs the patch step on fixtures (tools/check/host_lint.sh).
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/.." && pwd)

# sat(x): the expression stored into st_size (x is evaluated twice; both are plain field reads)
SAT_FSIZE='st->st_size = (f_size(file) > 0xFFFFFFFFu) ? (off_t)0xFFFFFFFFu : (off_t)f_size(file);   \/* jc: saturate, never wrap *\/'
SAT_INFO='st->st_size = (info->fsize > 0xFFFFFFFFu) ? (off_t)0xFFFFFFFFu : (off_t)info->fsize;   \/* jc: saturate, never wrap *\/'

# once FILE EXTENDED-REGEX SED-SUBSTITUTION : the pattern must match exactly one line, then it is replaced
once() {
    local file=$1 re=$2 sub=$3 n
    [ -f "$file" ] || { echo "make_fatfs: FAILED - $file is missing (IDF changed?). See tools/fatfs_exfat/README.md" >&2; return 1; }
    n=$(grep -cE -- "$re" "$file" || true)
    if [ "$n" != 1 ]; then
        echo "make_fatfs: FAILED - expected exactly one line matching '$re' in $file, found $n (IDF changed?). See tools/fatfs_exfat/README.md" >&2
        return 1
    fi
    sed -E -i "s/$re/$sub/" "$file"
}

# patch_tree DIR : the edits on a copy of components/fatfs
patch_tree() {
    local d=$1
    once "$d/src/ffconf.h" '^#define FF_FS_EXFAT[[:space:]]+0[[:space:]]*$' '#define FF_FS_EXFAT\t\t1   \/* jc: exFAT on (tools\/fatfs_exfat) *\/' || return 1
    once "$d/src/ffconf.h" '^#define FF_USE_LABEL[[:space:]]+CONFIG_FATFS_USE_LABEL[[:space:]]*$' '#define FF_USE_LABEL\t1   \/* jc: f_setlabel on (the card format names the volume, tools\/fatfs_exfat) *\/' || return 1
    once "$d/vfs/vfs_fat.c" '^[[:space:]]*st->st_size = f_size\(file\);[[:space:]]*$' "    $SAT_FSIZE" || return 1
    once "$d/vfs/vfs_fat.c" '^[[:space:]]*st->st_size = info->fsize;[[:space:]]*$' "    $SAT_INFO" || return 1
    grep -qE '^#define FF_FS_EXFAT[[:space:]]+1' "$d/src/ffconf.h" || { echo "make_fatfs: FAILED - FF_FS_EXFAT is not 1 after the edit" >&2; return 1; }
}

selftest() {
    local t; t=$(mktemp -d); trap 'rm -rf "$t"' RETURN
    mkfix() {   # mkfix DIR [skip-exfat|skip-label|skip-fsize|skip-info|dup-info]
        mkdir -p "$1/src" "$1/vfs"
        printf '/* fixture */\n#define FF_FS_EXFAT\t\t0\n/* switch */\n#define FF_USE_LABEL\tCONFIG_FATFS_USE_LABEL\n' > "$1/src/ffconf.h"
        printf 'static int fstat_(void)\n{\n    st->st_size = f_size(file);\n}\nstatic void upd(void)\n{\n    st->st_size = info->fsize;\n}\n' > "$1/vfs/vfs_fat.c"
        case ${2:-} in
        skip-exfat) sed -i '/FF_FS_EXFAT/d' "$1/src/ffconf.h" ;;
        skip-label) sed -i '/FF_USE_LABEL/d' "$1/src/ffconf.h" ;;
        skip-fsize) sed -i '/f_size(file)/d' "$1/vfs/vfs_fat.c" ;;
        skip-info)  sed -i '/info->fsize/d' "$1/vfs/vfs_fat.c" ;;
        dup-info)   echo '    st->st_size = info->fsize;' >> "$1/vfs/vfs_fat.c" ;;
        esac
    }
    local fail=0
    mkfix "$t/ok"
    if patch_tree "$t/ok" 2>"$t/ok.err" \
       && grep -qE '^#define FF_FS_EXFAT[[:space:]]+1' "$t/ok/src/ffconf.h" \
       && grep -qE '^#define FF_USE_LABEL[[:space:]]+1[[:space:]]' "$t/ok/src/ffconf.h" && [ "$(grep -c 'FF_USE_LABEL' "$t/ok/src/ffconf.h")" = 1 ] \
       && ! grep -q 'FF_USE_LABEL.CONFIG_FATFS_USE_LABEL' "$t/ok/src/ffconf.h" \
       && grep -q '0xFFFFFFFFu) ? (off_t)0xFFFFFFFFu : (off_t)f_size(file)' "$t/ok/vfs/vfs_fat.c" \
       && grep -q '0xFFFFFFFFu) ? (off_t)0xFFFFFFFFu : (off_t)info->fsize' "$t/ok/vfs/vfs_fat.c" \
       && ! grep -qE 'st_size = (f_size\(file\)|info->fsize);' "$t/ok/vfs/vfs_fat.c"; then echo "selftest ok: expected lines patched"
    else echo "selftest FAILED: the good fixture did not patch"; cat "$t/ok.err"; fail=1; fi
    local c
    for c in skip-exfat skip-label skip-fsize skip-info dup-info; do
        mkfix "$t/$c" $c
        if patch_tree "$t/$c" 2>"$t/$c.err"; then echo "selftest FAILED: $c was accepted"; fail=1
        elif grep -q 'make_fatfs: FAILED' "$t/$c.err"; then echo "selftest ok: $c refused"
        else echo "selftest FAILED: $c failed without the message"; fail=1; fi
    done
    return $fail
}

if [ "${1:-}" = "--selftest" ]; then selftest; exit $?; fi

dest="${FATFS_EXFAT_DEST:-$root/.generated/fatfs_exfat/fatfs}"   # override for a trial run
IDF_PATH="${IDF_PATH:-$HOME/.espressif/v6.1/esp-idf}"        # IDF v6.1
src="$IDF_PATH/components/fatfs"
[ -f "$src/src/ffconf.h" ] || { echo "make_fatfs: no FatFs in $src" >&2; exit 1; }
want=$( (cd "$src" && find . -type f -print0 | LC_ALL=C sort -z | xargs -0 sha256sum; sha256sum "$here/make_fatfs_exfat.sh" | cut -d' ' -f1) | sha256sum | cut -d' ' -f1)
if [ -f "$dest/.jc_stamp" ] && [ "$(cat "$dest/.jc_stamp")" = "$want" ]; then exit 0; fi
tmp="$dest.new"
rm -rf "$tmp"
mkdir -p "$(dirname "$dest")"
cp -a "$src" "$tmp"
if ! patch_tree "$tmp"; then rm -rf "$tmp"; exit 1; fi
echo "$want" > "$tmp/.jc_stamp"
rm -rf "$dest"
mv "$tmp" "$dest"
echo "make_fatfs: FatFs with exFAT ready in $dest"
