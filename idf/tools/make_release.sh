#!/usr/bin/env bash
# SPDX-License-Identifier: CC-BY-NC-SA-4.0
# Builds the firmware and collects the release files into <repo>/release/<version>/ (git-ignored; upload them as release assets, do not commit them):
#   tamapoke-fakepod-<v>-full.bin      bootloader + partition table + app in one image: flash at 0x0
#   tamapoke-fakepod-<v>-sprites.zip   the mons/ folder for the TF card
#   the three install guides, LICENSE, CREDITS.md, NOTICE-FAKEPOD.md, SHA256SUMS
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd); idf=$(cd "$here/.." && pwd); root=$(cd "$idf/.." && pwd)
ver=$(cat "$idf/version.txt"); out="$root/release/$ver"
# the IDF activate script decides "was I sourced?" from $0, which is this file: run each IDF step in a fresh `bash -c` where it works
idfrun() { bash -c "source \"\$HOME/.espressif/tools/activate_idf_v6.1.sh\" >/dev/null 2>&1; $1"; }
python3 "$root/tools/port/gen_protos.py" "$idf/main/tamapoke_app.cpp" "$idf/main/tamapoke_protos.h" >/dev/null
idfrun "cd '$idf' && idf.py --preview build >/dev/null"
rm -rf "$out"; mkdir -p "$out"
b="$idf/build"
idfrun "python -m esptool --chip esp32s31 merge-bin -o '$out/tamapoke-fakepod-$ver-full.bin' --flash-mode dio --flash-freq 80m --flash-size 16MB 0x2000 '$b/bootloader/bootloader.bin' 0x8000 '$b/partition_table/partition-table.bin' 0x10000 '$b/tamapoke_fakepod.bin' >/dev/null"
python3 - "$root/tools/sdcard" "$out/tamapoke-fakepod-$ver-sprites.zip" <<'PY'
import os, sys, zipfile
src, dst = sys.argv[1], sys.argv[2]
with zipfile.ZipFile(dst, 'w', zipfile.ZIP_DEFLATED, compresslevel=9) as z:
    for n in sorted(os.listdir(os.path.join(src, 'mons'))):
        z.write(os.path.join(src, 'mons', n), 'mons/' + n)
PY
cp "$root/docs/install/"INSTALL.*.md "$root/LICENSE" "$root/CREDITS.md" "$root/NOTICE-FAKEPOD.md" "$out/"
(cd "$out" && sha256sum * > SHA256SUMS)
ls -l "$out"
