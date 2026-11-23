# TamaPoke for Fake Pod Nano Pro (ESP32-S31) — install guide

> A personal, non-commercial fan project. Pokémon and all related names and characters are © Nintendo / Game Freak / The Pokémon Company. Not affiliated with them.
> Read the licenses in `NOTICE-FAKEPOD.md` and `LICENSE` first.

## What you need
- A **Fake Pod Nano Pro** (the **ESP32-S31** board, 460×460 AMOLED). **Not** the older "Fake Pod Nano" (ESP32-S3): this firmware does not run on it.
- A USB-C cable and a computer with Python 3.
- A TF (microSD) card. Any size; **FAT32 or exFAT**, with an **MBR** partition table (a card with a GPT table is not read). The game never formats your card.
- The two release files:
  - `tamapoke-fakepod-VERSION-full.bin` — the firmware (bootloader + partition table + app in one file)
  - `tamapoke-fakepod-VERSION-sprites.zip` — the pet pictures, for the TF card

> About `-sprites.zip`: these pictures are **not made by this project**. They are the sprite pack from the upstream TamaPoke repository (`socquique/TamaPoke`, `tools/sdcard/mons`), built from PMD SpriteCollab (CC BY-NC 4.0). See `NOTICE-FAKEPOD.md` and `CREDITS.md`.

## 1. Put the pictures on the TF card
1. Unzip `tamapoke-fakepod-VERSION-sprites.zip`. You get a folder named **`mons`** (303 files, about 41 MB).
2. Copy the whole **`mons`** folder to the **root** of the TF card (so the card has `/mons/p001.bin` …).
3. Put the card in the Fake Pod. Nothing else on the card is touched.

## 2. Flash the firmware
1. Install esptool (it must support the ESP32-S31: version 5.x or newer, the one bundled with ESP-IDF 6.1 works):
   `python -m pip install --upgrade esptool`
2. Put the Fake Pod in **download mode**: **hold both side keys, then connect USB** (or power it on while holding them). The computer should show a USB device `303a:1001` (Espressif USB JTAG/serial).
3. Flash (replace `PORT` with your serial port, e.g. `/dev/ttyACM0`, `COM5`, `/dev/cu.usbmodem101`):
   ```
   python -m esptool --chip esp32s31 --port PORT --baud 460800 --no-stub write-flash --flash-mode dio --flash-freq 80m --flash-size 16MB 0x0 tamapoke-fakepod-VERSION-full.bin
   ```
4. Unplug and reconnect USB (without holding the keys). The game starts.

## 3. First start
1. Choose the language: **English / 繁體中文 / 简体中文**.
2. The how-to-play pages appear (tap to go on). You can open them again any time: swipe down for settings, then tap the **HELP** button at the top right.
3. Choose your first Pokémon.

## Things to know
- **Screen sleep:** press either side key to sleep or wake the screen; it also sleeps by itself after 2 minutes. Touching the screen wakes it. (Holding the **top** key for 4 seconds powers the device off — that is the power chip's own function.)
- **Do not hold the bottom key while the device resets or powers on** unless you want the download mode.
- **No sound yet.** The game has sound effects, but this build is silent (the board has a headphone DAC and no speaker; it is not wired up yet).
- **Erase the saved game** (the pet, the language): `python -m esptool --chip esp32s31 --port PORT --no-stub erase-region 0x9000 0x6000`
- **The TF card is not recognised?** Check that it is FAT32/exFAT with an MBR partition table. The log (115200 baud on the USB port) says `SD montada: … MB` when it works.

## Update later
Flash the new `-full.bin` again. Your saved game is kept unless the new file says otherwise in its release notes (a full image rewrites the whole flash: use the `erase-region` command only if you want a fresh start).
