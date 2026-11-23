# TamaPoke（Fake Pod Nano Pro / ESP32-S31）刷写说明

> 这是个人、非商业的同人项目。宝可梦及相关名称、角色的权利属于 Nintendo / Game Freak / The Pokémon Company，本项目与他们无关。
> 请先阅读 `NOTICE-FAKEPOD.md` 与 `LICENSE` 中的许可条款。

## 你需要
- **Fake Pod Nano Pro**（**ESP32-S31** 版，460×460 AMOLED）。**不是**较早的“Fake Pod Nano”（ESP32-S3），这份固件无法在它上面运行。
- USB-C 数据线，以及一台装有 Python 3 的电脑。
- 一张 TF（microSD）卡，容量不限，格式 **FAT32 或 exFAT**，分区表必须是 **MBR**（读不了 GPT）。游戏**不会格式化**你的卡。
- 两个 release 文件：
  - `tamapoke-fakepod-版本-full.bin`：固件（bootloader、分区表、程序合并为一个文件）
  - `tamapoke-fakepod-版本-sprites.zip`：宠物图片，放在 TF 卡里

> 关于 `-sprites.zip`：这些图片**不是本项目制作的**，是上游 TamaPoke 项目（`socquique/TamaPoke`，`tools/sdcard/mons`）附带的精灵图包，来源是 PMD SpriteCollab（CC BY-NC 4.0）。详见 `NOTICE-FAKEPOD.md` 与 `CREDITS.md`。

## 1. 把图片放进 TF 卡
1. 解压 `tamapoke-fakepod-版本-sprites.zip`，会得到一个名为 **`mons`** 的文件夹（303 个文件，约 41 MB）。
2. 把整个 **`mons`** 文件夹复制到 TF 卡的**根目录**（卡上会有 `/mons/p001.bin` 等文件）。
3. 把卡插回 Fake Pod。卡上的其他内容完全不会被改动。

## 2. 刷写固件
1. 安装 esptool（必须支持 ESP32-S31，版本 5.x 及以上；ESP-IDF 6.1 自带的可用）：
   `python -m pip install --upgrade esptool`
2. 让 Fake Pod 进入**下载模式**：**同时按住两个侧键，再接上 USB**（或按住两键再开机）。电脑会出现 USB 设备 `303a:1001`（Espressif USB JTAG/serial）。
3. 刷写（把 `PORT` 换成你的串口，例如 `/dev/ttyACM0`、`COM5`、`/dev/cu.usbmodem101`）：
   ```
   python -m esptool --chip esp32s31 --port PORT --baud 460800 --no-stub write-flash --flash-mode dio --flash-freq 80m --flash-size 16MB 0x0 tamapoke-fakepod-版本-full.bin
   ```
4. 拔掉 USB 再重新接上（这次不要按侧键），游戏就会启动。

## 3. 第一次开机
1. 选择语言：**English／繁體中文／简体中文**。
2. 会出现玩法说明（点一下翻页）。之后随时可以再看：向下滑打开设置页，点右上角的“说明”按钮。
3. 选择你的第一只宝可梦。

## 注意事项
- **屏幕休眠：** 按任一侧键可休眠或唤醒屏幕；闲置 2 分钟也会自动休眠，碰一下屏幕即可唤醒。（长按**上键** 4 秒是电源芯片的硬件关机。）
- **设备复位或开机时，不要按住下键**，否则会进入下载模式。
- **目前没有声音。** 游戏本身有音效，但这个版本是静音的（板子有耳机 DAC、没有喇叭，尚未接上）。
- **清除存档**（宠物、语言）：`python -m esptool --chip esp32s31 --port PORT --no-stub erase-region 0x9000 0x6000`
- **TF 卡读不到？** 请确认是 FAT32／exFAT 且为 MBR 分区表。成功时 USB 串口（115200）会打印 `SD montada: … MB`。

## 之后更新
再刷写新的 `-full.bin` 即可。（整份镜像会重写整个 flash，若要保留存档请看该版本的 release 说明；想重新开始再用上面的 `erase-region` 命令。）
