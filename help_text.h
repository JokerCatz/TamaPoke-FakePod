// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// In-game help pages (Fake Pod build). English, Traditional Chinese (Taiwan) and Simplified Chinese; every other language falls back to English.
// Lines are wrapped by hand for the 460 px panel: <= 32 Latin characters, <= 24 full-width characters per line. The Chinese glyphs in this file are included in the
// font subset by tools/gen_zh_font.py, so keep every Chinese character of the help text in this file.
#pragma once
#include <stdint.h>
#include "i18n.h"

#define HELP_MAX_LINES 11
struct HelpPage { const char *title; const char *lines[HELP_MAX_LINES]; };
struct HelpSet { const char *label, *next, *close; uint8_t pages; const HelpPage *page; };

static const HelpPage HELP_EN[] = {
  { "HOW TO PLAY", {
      "1 real minute = 1 game minute.",
      "Your pet gains 1 level an hour.",
      "",
      "Keep the 4 bars up: FOOD, JOY,",
      "ENE (energy) and HYG (clean).",
      "They fall over time. Under 10",
      "is a slip-up and delays your",
      "pet's evolution by 1 level." } },
  { "BUTTONS", {
      "Bottom row, left to right:",
      "",
      "Berry: feed (find its favorite)",
      "Ball: play, trains SPEED",
      "Moon: sleep / wake up",
      "Bubbles: bath, cleans the poop",
      "",
      "Tap your pet: pet it",
      "Long press your pet: release it" } },
  { "GESTURES", {
      "Swipe up: pet card",
      "  (swipe sideways: 4 pages)",
      "Swipe down: settings, help",
      "Swipe sideways: Pokedex",
      "",
      "Side key: screen sleep / wake",
      "(it also sleeps after 2 minutes)" } },
  { "EVOLVE & GOODBYE", {
      "Level 16 or higher and every bar",
      "at 40 or more: an EVOLVE! button",
      "appears. Tap it to evolve.",
      "",
      "A final form that lived 3 days",
      "can say goodbye (good ending).",
      "All bars at 0 for 1 hour: it",
      "runs away (sad ending).",
      "A new egg follows: tap it 3x." } },
  { "TIPS", {
      "Poop drains hygiene fast: bathe.",
      "Every pet has a favorite berry.",
      "A daily streak and a high bond",
      "raise the odds of rare and",
      "shiny Pokemon.",
      "",
      "Goal: collect all 151!" } },
};

static const HelpPage HELP_ZH[] = {
  { "玩法簡介", {
      "現實 1 分鐘 = 遊戲 1 分鐘。",
      "寵物每過 1 小時升 1 級。",
      "",
      "照顧好四條狀態列：飽食、",
      "心情、體力、清潔。",
      "它們會隨時間下降，低於 10",
      "算一次失誤，會讓進化延後",
      "1 級。" } },
  { "按鈕", {
      "下方一排，由左到右：",
      "",
      "樹果：餵食（找出最愛的口味）",
      "球：玩耍，訓練速度",
      "月亮：睡覺／起床",
      "泡泡：洗澡，清除便便",
      "",
      "點寵物：摸摸它",
      "長按寵物：放生" } },
  { "手勢", {
      "往上滑：寵物資料卡",
      "（資料卡內左右滑可換頁）",
      "往下滑：設定、說明",
      "左右滑：圖鑑",
      "",
      "側鍵：螢幕休眠／喚醒",
      "（閒置 2 分鐘也會自動休眠）" } },
  { "進化與道別", {
      "等級 16 以上，而且四條狀態",
      "列都在 40 以上，就會出現",
      "「進化！」按鈕，點它進化。",
      "",
      "最終型態活滿 3 天可以道別",
      "（好結局）。四條全為 0 滿",
      "1 小時，寵物會跑走（壞結局）。",
      "之後會有新的蛋，點 3 下孵化。" } },
  { "小提示", {
      "便便會讓清潔快速下降，",
      "記得洗澡。",
      "每隻寵物都有最愛的樹果。",
      "每天照顧的連續天數和親密度",
      "越高，越容易出現稀有和",
      "異色寶可夢。",
      "",
      "目標：收集全部 151 隻！" } },
};

static const HelpPage HELP_ZHS[] = {
  { "玩法简介", {
      "现实 1 分钟 = 游戏 1 分钟。",
      "宠物每过 1 小时升 1 级。",
      "",
      "照顾好四条状态栏：饱食、",
      "心情、体力、清洁。",
      "它们会随时间下降，低于 10",
      "算一次失误，会让进化延后",
      "1 级。" } },
  { "按钮", {
      "下方一排，从左到右：",
      "",
      "树果：喂食（找出最爱的口味）",
      "球：玩耍，训练速度",
      "月亮：睡觉／起床",
      "泡泡：洗澡，清除便便",
      "",
      "点宠物：摸摸它",
      "长按宠物：放生" } },
  { "手势", {
      "向上滑：宠物资料卡",
      "（资料卡内左右滑可翻页）",
      "向下滑：设置、说明",
      "左右滑：图鉴",
      "",
      "侧键：屏幕休眠／唤醒",
      "（闲置 2 分钟也会自动休眠）" } },
  { "进化与告别", {
      "等级 16 以上，而且四条状态",
      "栏都在 40 以上，就会出现",
      "“进化！”按钮，点它进化。",
      "",
      "最终形态活满 3 天可以告别",
      "（好结局）。四条全为 0 满",
      "1 小时，宠物会跑掉（坏结局）。",
      "之后会有新的蛋，点 3 下孵化。" } },
  { "小提示", {
      "便便会让清洁快速下降，",
      "记得洗澡。",
      "每只宠物都有最爱的树果。",
      "每天照顾的连续天数和亲密度",
      "越高，越容易出现稀有和",
      "闪光宝可梦。",
      "",
      "目标：收集全部 151 只！" } },
};

static const HelpSet HELP_SETS[] = {
  { "HELP", "tap: next", "tap: close", sizeof(HELP_EN) / sizeof(HELP_EN[0]), HELP_EN },
  { "說明", "點一下：下一頁", "點一下：關閉", sizeof(HELP_ZH) / sizeof(HELP_ZH[0]), HELP_ZH },
  { "说明", "点一下：下一页", "点一下：关闭", sizeof(HELP_ZHS) / sizeof(HELP_ZHS[0]), HELP_ZHS },
};

static inline const HelpSet &helpFor(Lang l) { return HELP_SETS[l == LANG_ZH ? 1 : l == LANG_ZHS ? 2 : 0]; }
