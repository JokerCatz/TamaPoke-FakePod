#!/bin/bash
# Host (PC) build of the TamaPoke app against the compat layer + fake hardware, for layout tests. Output: tools/host/out/tamapoke_host
set -e
R="$(cd "$(dirname "$0")/../.." && pwd)"; O="$R/tools/host/out"; mkdir -p "$O"
C="$R/idf/components"
SRCS="$R/idf/main/tamapoke_app.cpp $R/pet.cpp $R/i18n.cpp $R/sdmon.cpp $R/trainingtouch.cpp $R/screenlock.cpp $R/bootbutton.cpp
 $C/arduino_compat/src/arduino_compat.cpp $C/arduino_compat/src/prefs.cpp $C/arduino_compat/src/sd_card.cpp $C/gfx_compat/src/gfx.cpp
 $R/tools/host/fp_display_host.cpp $R/tools/host/touch_host.cpp $R/tools/host/rtcbat_host.cpp $R/tools/host/audio_stub.cpp ${HOST_MAIN:-$R/tools/host/main_host.cpp}"
g++ -std=gnu++17 -O1 -g -w -DBOARD_FAKEPOD_NANO_PRO=1 -DHOST_BUILD=1 -fpermissive \
  -I "$R/tools/host/stub" -I "$R/idf/main" -I "$R" -I "$C/arduino_compat/include" -I "$C/gfx_compat/include" -I "$C/gfx_compat/src" \
  -I "$C/fakepod_bsp/include" $SRCS -o "$O/tamapoke_host" "$@"
