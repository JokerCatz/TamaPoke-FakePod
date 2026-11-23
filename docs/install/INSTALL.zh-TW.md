# TamaPoke（Fake Pod Nano Pro / ESP32-S31）寫入說明

> 這是個人、非商業的同人專案。寶可夢及相關名稱、角色的權利屬於 Nintendo / Game Freak / The Pokémon Company，本專案與他們無關。
> 請先閱讀 `NOTICE-FAKEPOD.md` 與 `LICENSE` 的授權條款。

## 你需要
- **Fake Pod Nano Pro**（**ESP32-S31** 版，460×460 AMOLED）。**不是**較早的「Fake Pod Nano」（ESP32-S3），這份韌體無法在它上面執行。
- USB-C 傳輸線，以及一台有 Python 3 的電腦。
- 一張 TF（microSD）卡，容量不限，格式 **FAT32 或 exFAT**，分割表必須是 **MBR**（GPT 讀不到）。遊戲**不會格式化**你的卡。
- 兩個 release 檔案：
  - `tamapoke-fakepod-版本-full.bin`：韌體（bootloader、分割表、程式合成一個檔）
  - `tamapoke-fakepod-版本-sprites.zip`：寵物圖片，放在 TF 卡

## 1. 把圖片放進 TF 卡
1. 解壓縮 `tamapoke-fakepod-版本-sprites.zip`，會得到一個名為 **`mons`** 的資料夾（303 個檔案，約 41 MB）。
2. 把整個 **`mons`** 資料夾複製到 TF 卡的**根目錄**（卡上會有 `/mons/p001.bin` 等檔案）。
3. 把卡插回 Fake Pod。卡上其他內容完全不會被動到。

## 2. 寫入韌體
1. 安裝 esptool（必須支援 ESP32-S31，版本 5.x 以上；ESP-IDF 6.1 內附的可用）：
   `python -m pip install --upgrade esptool`
2. 讓 Fake Pod 進入**下載模式**：**兩個側鍵同時按住，再接上 USB**（或按住兩鍵再開機）。電腦會出現 USB 裝置 `303a:1001`（Espressif USB JTAG/serial）。
3. 寫入（把 `PORT` 換成你的序列埠，例如 `/dev/ttyACM0`、`COM5`、`/dev/cu.usbmodem101`）：
   ```
   python -m esptool --chip esp32s31 --port PORT --baud 460800 --no-stub write-flash --flash-mode dio --flash-freq 80m --flash-size 16MB 0x0 tamapoke-fakepod-版本-full.bin
   ```
4. 拔掉 USB 再重新接上（這次不要按側鍵），遊戲就會啟動。

## 3. 第一次開機
1. 選擇語言：**English／繁體中文／简体中文**。
2. 會出現玩法說明（點一下翻頁）。之後隨時可以再看：往下滑開啟設定頁，點右上角的「說明」按鈕。
3. 選擇你的第一隻寶可夢。

## 注意事項
- **螢幕休眠：** 按任一側鍵可休眠或喚醒螢幕；閒置 2 分鐘也會自動休眠，碰一下螢幕即可喚醒。（長按**上鍵** 4 秒是電源晶片的硬體關機。）
- **裝置重置或開機時，不要按住下鍵**，否則會進入下載模式。
- **目前沒有聲音。** 遊戲本身有音效，但這個版本是靜音的（板子有耳機 DAC、沒有喇叭，尚未接上）。
- **清除存檔**（寵物、語言）：`python -m esptool --chip esp32s31 --port PORT --no-stub erase-region 0x9000 0x6000`
- **TF 卡讀不到？** 請確認是 FAT32／exFAT 且為 MBR 分割表。成功時 USB 序列埠（115200）會印出 `SD montada: … MB`。

## 之後更新
再寫入新的 `-full.bin` 即可。（整份映像會重寫整個 flash，若要保留存檔請看該版本的 release 說明；想重新開始再用上面的 `erase-region` 指令。）
