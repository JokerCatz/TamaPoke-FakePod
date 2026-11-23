#!/bin/bash
# Renders every screen in every language on the PC: tools/host/out/shots/<lang>_<screen>.png (+ a contact sheet per screen)
set -e
R="$(cd "$(dirname "$0")/../.." && pwd)"; D="$R/tools/host/out/shots"; mkdir -p "$D"
"$R/tools/host/build.sh" && "$R/tools/host/out/tamapoke_host" "$D"
python3 - "$D" <<'PY'
import sys, glob, os
from PIL import Image
d = sys.argv[1]
for f in glob.glob(d + '/*.ppm'):
    Image.open(f).save(f[:-4] + '.png'); os.remove(f)
print('pngs in', d)
PY
