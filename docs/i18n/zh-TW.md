# 繁體中文對照表（台灣用語）

由 `tools/gen_i18n_table.py` 從 `i18n.cpp` 產生，**請勿手改**；要改譯文請改 `i18n.cpp` 後重新執行。

- 寶可夢名稱：全部取自 PokéAPI 的 `zh-Hant` 欄位（台灣官方譯名），由 `tools/gen_names.py` 抓取，共 151 隻。
- 介面字串：人工翻譯，格式占位符（`%u`、`%s` 等）與英文完全一致，由 `tools/test_i18n_formats.py` 檢查。
- 顯示字型：依文字大小對應——大小 1 用 Cubic 11（OFL）11 px、大小 2 用 Unifont 子集 16 px（與拉丁字同高）、大小 3 用 Cubic 11 放大兩倍 22 px。
## 介面字串

| # | ID | English | 繁體中文 | 简体中文 | 備註 |
|---|---|---|---|---|---|
| 0 | `S_EVOLVING` | Evolving! | 進化中！ | 进化中！ |  |
| 1 | `S_EATING` | Yum yum! | 好好吃！ | 好好吃！ |  |
| 2 | `S_LIKES` | It likes it! | 牠很喜歡！ | 它很喜欢！ |  |
| 3 | `S_HUNGRY` | It's hungry! | 牠肚子餓了！ | 它肚子饿了！ |  |
| 4 | `S_NEEDS_BATH` | Needs a bath! | 該洗澡了！ | 该洗澡了！ |  |
| 5 | `S_EXHAUSTED` | Worn out... | 累壞了…… | 累坏了…… |  |
| 6 | `S_SAD` | Feeling sad... | 牠很難過…… | 它很难过…… |  |
| 7 | `S_CHUBBY` | A bit chubby... | 有點胖胖的…… | 有点胖乎乎的…… |  |
| 8 | `S_IS_SHINY` | It's SHINY!! | 是異色寶可夢！！ | 是闪光宝可梦！！ | 台灣官方稱閃光寶可夢為「異色」 |
| 9 | `S_HAPPY` | It's happy | 牠很開心 | 它很开心 |  |
| 10 | `S_FAREWELL` | THANKS! Farewell | 謝謝你！再見了 | 谢谢你！再见了 |  |
| 11 | `S_RUNAWAY` | It ran away... | 牠跑走了…… | 它跑掉了…… |  |
| 12 | `S_GOODBYE` | Bye! Waving goodbye... | 再見！揮手道別…… | 再见！挥手告别…… |  |
| 13 | `S_EGG_HDR` | EGG | 蛋 | 蛋 |  |
| 14 | `S_EGG_LEGEND` | Legendary egg!? | 傳說的蛋！？ | 传说中的蛋！？ |  |
| 15 | `S_EGG_RARE` | Rare egg! | 稀有的蛋！ | 稀有的蛋！ |  |
| 16 | `S_EGG_TOUCH` | Tap the egg... | 點一下蛋…… | 点一下蛋…… |  |
| 17 | `S_EGG_MOVES` | It moves! | 動了！ | 动了！ |  |
| 18 | `S_EGG_ALMOST` | Almost there! | 快孵化了！ | 快孵化了！ |  |
| 19 | `S_POKEDEX_FMT` | POKEDEX %u/151 | 圖鑑 %u/151 | 图鉴 %u/151 | 官方全名「寶可夢圖鑑」，版面窄所以縮成「圖鑑」 |
| 20 | `S_NAME_FMT` | %s%s Lv.%u | %s%s Lv.%u | %s%s Lv.%u |  |
| 21 | `S_RELEASE_FMT` | Release %s? | 要放生%s嗎？ | 要放生%s吗？ | 「放生」為台灣官方「放走寶可夢」用語 |
| 22 | `S_YES` | YES | 是 | 是 |  |
| 23 | `S_NO` | NO | 否 | 否 |  |
| 24 | `S_HITS_FMT` | %u HITS | 擊中 %u 次 | 击中 %u 次 |  |
| 25 | `S_STR_GAIN_FMT` | STR +%u | 力量 +%u | 力量 +%u |  |
| 26 | `S_NEW_RECORD` | NEW RECORD! | 新紀錄！ | 新纪录！ |  |
| 27 | `S_RECORD_FMT` | BEST: %u | 最佳：%u | 最佳：%u |  |
| 28 | `S_HIT_FAST` | HIT FAST! | 快打！ | 快打！ |  |
| 29 | `S_SCORE_FMT` | SCORE: %u | 得分：%u | 得分：%u |  |
| 30 | `S_GREAT_JOY` | So much fun! | 好開心！ | 好开心！ |  |
| 31 | `S_PLUS_JOY` | +happiness | +心情 | +心情 |  |
| 32 | `S_SET_TIME` | SET TIME | 設定時間 | 设置时间 |  |
| 33 | `S_HOUR` | HOUR | 時 | 时 |  |
| 34 | `S_MIN` | MIN | 分 | 分 |  |
| 35 | `S_CLOCK_CANCEL` | swipe up: cancel | 上滑：取消 | 上滑：取消 |  |
| 36 | `S_LANG_LABEL` | Lang | 語言 | 语言 |  |
| 37 | `S_MEDAL_BANNER` | MEDAL! | 獲得勳章！ | 获得勋章！ | 「徽章」在台灣官方是道館徽章，故這裡的成就用「勳章」避免混淆 |
| 38 | `S_GREAT` | AWESOME! | 太棒了！ | 太棒了！ |  |
| 39 | `S_STREAK_DAYS_FMT` | %u DAY STREAK! | 連續 %u 天！ | 连续 %u 天！ | 日數放在句中，方便中文語序 |
| 40 | `S_STREAK_FMT` | STREAK %u  best %u | 連續 %u 天　最高 %u | 连续 %u 天　最高 %u |  |
| 41 | `S_VIN` | BOND | 親密 | 亲密 | 原文 BOND（羈絆），遊戲內名為「親密度」，簡稱「親密」 |
| 42 | `S_BERRY_UNK` | BERRY ??? | 樹果 ??? | 树果 ??? | 台灣官方用「樹果」（不是「漿果」） |
| 43 | `S_BERRY_RED` | RED BERRY | 紅色樹果 | 红色树果 |  |
| 44 | `S_BERRY_BLUE` | BLUE BERRY | 藍色樹果 | 蓝色树果 |  |
| 45 | `S_BERRY_GREEN` | GREEN BERRY | 綠色樹果 | 绿色树果 |  |
| 46 | `S_INFO_FMT` | %s   AGE %lud | %s　年齡 %lu 天 | %s　年龄 %lu 天 |  |
| 47 | `S_RENAME_HINT` | tap name: rename | 點名字：改名 | 点名字：改名 |  |
| 48 | `S_BATTLE` | BATTLE | 對戰 | 对战 |  |
| 49 | `S_STAT_ATK` | ATK | 攻擊 | 攻击 |  |
| 50 | `S_STAT_DEF` | DEF | 防禦 | 防御 |  |
| 51 | `S_STAT_SPE` | SPD | 速度 | 速度 |  |
| 52 | `S_STAT_WGT` | WGT | 體重 | 体重 |  |
| 53 | `S_TRAIN_STR` | TRAIN STRENGTH | 訓練力量 | 训练力量 |  |
| 54 | `S_MEDALS_FMT` | MEDALS %d/%d | 勳章 %d/%d | 勋章 %d/%d | 同上，用「勳章」 |
| 55 | `S_BACK` | tap: back | 點一下：返回 | 点一下：返回 |  |
| 56 | `S_NAME` | NAME: | 名字： | 名字： |  |
| 57 | `S_DETAIL_BACK` | tap to go back | 點一下返回 | 点一下返回 |  |
| 58 | `S_BAR_FOOD` | FOOD | 飽食 | 饱食 |  |
| 59 | `S_BAR_JOY` | JOY | 心情 | 心情 |  |
| 60 | `S_BAR_ENE` | ENE | 體力 | 体力 |  |
| 61 | `S_BAR_HYG` | HYG | 清潔 | 清洁 |  |
| 62 | `S_REC_FMT` | BEST %u | 最佳 %u | 最佳 %u |  |
| 63 | `S_PROGRESS` | PROGRESS | 成長 | 成长 |  |
| 64 | `S_LVL_FMT` | Lv.%u | Lv.%u | Lv.%u |  |
| 65 | `S_NEXT_LVL_FMT` | %u min to Lv.%u | %u 分後 Lv.%u | %u 分钟后 Lv.%u |  |
| 66 | `S_EVO_LABEL` | EVOLUTION | 進化 | 进化 |  |
| 67 | `S_FINAL_FORM` | Final form | 最終型態 | 最终形态 |  |
| 68 | `S_EVO_READY` | Ready to evolve! | 可以進化了！ | 可以进化了！ |  |
| 69 | `S_EVO_BLOCKED` | All needs >=40 to evolve | 全部需求 40 以上才能進化 | 全部需求 40 以上才能进化 | 避免使用「≥」：Cubic 11 字型沒有此字 |
| 70 | `S_EVO_IN_FMT` | Evolves in %u lv. | 再 %u 級進化 | 再 %u 级进化 |  |
| 71 | `S_MISTAKES_FMT` | Slip-ups: %u | 失誤：%u | 失误：%u |  |
| 72 | `S_SND_ON` | SND ON | 音效 開 | 音效 开 |  |
| 73 | `S_SND_OFF` | SND OFF | 音效 關 | 音效 关 |  |
| 74 | `S_EVO_TAP` | EVOLVE! | 進化！ | 进化！ |  |
| 75 | `S_FAREWELL_BTN` | %s wants to tell you... | %s有話想對你說…… | %s有话想对你说…… | %s 是寵物名字，緊接在後不加空格（中文不需要） |
| 76 | `S_RUNAWAY_BTN` | %s feels abandoned... | %s覺得被拋棄了…… | %s觉得被抛弃了…… | 同上 |
| 77 | `S_EVO_Q` | Evolve? | 要進化嗎？ | 要进化吗？ |  |
| 78 | `S_EVO_KEEP` | Keep form | 維持型態 | 保持形态 |  |
| 79 | `S_FAR_Q` | Say goodbye? | 要道別嗎？ | 要告别吗？ |  |
| 80 | `S_FAR_GO` | Goodbye | 道別 | 告别 |  |
| 81 | `S_FAR_STAY` | Stay together | 繼續相伴 | 继续相伴 |  |
| 82 | `S_CHOOSE_STARTER` | Choose your starter | 選擇你的夥伴 | 选择你的伙伴 |  |
| 83 | `S_NO_SPRITES` | No sprites | 沒有精靈圖 | 没有精灵图 | 「精靈」是這個專案裡動畫圖檔的稱呼 |
| 84 | `S_LOAD_SPRITES` | Load them onto the SD | 請放進 SD 卡 | 请放进 SD 卡 | 精簡成「請放進 SD 卡」以符合欄寬 |
| 85 | `S_HOLD_EXIT` | Hold to exit | 長按離開 | 长按退出 |  |

## 勳章

| # | English（名稱 / 標籤 / 說明） | 繁體中文 | 简体中文 | 備註 |
|---|---|---|---|---|
| 0 | Lv.10 / Lv10 / LEVEL 10 | Lv.10 / Lv10 / 等級 10 | Lv.10 / Lv10 / 等级 10 |  |
| 1 | Lv.25 / Lv25 / LEVEL 25 | Lv.25 / Lv25 / 等級 25 | Lv.25 / Lv25 / 等级 25 |  |
| 2 | Lv.50 / Lv50 / LEVEL 50 | Lv.50 / Lv50 / 等級 50 | Lv.50 / Lv50 / 等级 50 |  |
| 3 | BERRY / BERRY / BERRY FOUND | 樹果 / 樹果 / 找到樹果 | 树果 / 树果 / 找到树果 |  |
| 4 | 7 STREAK / 7DAYS / 7 DAY STREAK | 連續7天 / 7天 / 連續 7 天 | 连续7天 / 7天 / 连续 7 天 |  |
| 5 | BOND / BOND / MAX BOND | 親密 / 親密 / 親密度最高 | 亲密 / 亲密 / 亲密度最高 |  |
| 6 | TOP FORM / TOP / FINAL FORM | 最終型態 / 最終 / 最終型態 | 最终形态 / 最终 / 最终形态 |  |
| 7 | IN SHAPE / FIT / IN SHAPE | 健康 / 健康 / 身體健康 | 健康 / 健康 / 身体健康 |  |

## 寶可夢名稱（第一代 151 隻）

| # | English | 繁體中文 | 简体中文 |
|---|---|---|---|
| 1 | BULBASAUR | 妙蛙種子 | 妙蛙种子 |
| 2 | IVYSAUR | 妙蛙草 | 妙蛙草 |
| 3 | VENUSAUR | 妙蛙花 | 妙蛙花 |
| 4 | CHARMANDER | 小火龍 | 小火龙 |
| 5 | CHARMELEON | 火恐龍 | 火恐龙 |
| 6 | CHARIZARD | 噴火龍 | 喷火龙 |
| 7 | SQUIRTLE | 傑尼龜 | 杰尼龟 |
| 8 | WARTORTLE | 卡咪龜 | 卡咪龟 |
| 9 | BLASTOISE | 水箭龜 | 水箭龟 |
| 10 | CATERPIE | 綠毛蟲 | 绿毛虫 |
| 11 | METAPOD | 鐵甲蛹 | 铁甲蛹 |
| 12 | BUTTERFREE | 巴大蝶 | 巴大蝶 |
| 13 | WEEDLE | 獨角蟲 | 独角虫 |
| 14 | KAKUNA | 鐵殼蛹 | 铁壳蛹 |
| 15 | BEEDRILL | 大針蜂 | 大针蜂 |
| 16 | PIDGEY | 波波 | 波波 |
| 17 | PIDGEOTTO | 比比鳥 | 比比鸟 |
| 18 | PIDGEOT | 大比鳥 | 大比鸟 |
| 19 | RATTATA | 小拉達 | 小拉达 |
| 20 | RATICATE | 拉達 | 拉达 |
| 21 | SPEAROW | 烈雀 | 烈雀 |
| 22 | FEAROW | 大嘴雀 | 大嘴雀 |
| 23 | EKANS | 阿柏蛇 | 阿柏蛇 |
| 24 | ARBOK | 阿柏怪 | 阿柏怪 |
| 25 | PIKACHU | 皮卡丘 | 皮卡丘 |
| 26 | RAICHU | 雷丘 | 雷丘 |
| 27 | SANDSHREW | 穿山鼠 | 穿山鼠 |
| 28 | SANDSLASH | 穿山王 | 穿山王 |
| 29 | NIDORAN H | 尼多蘭 | 尼多兰 |
| 30 | NIDORINA | 尼多娜 | 尼多娜 |
| 31 | NIDOQUEEN | 尼多后 | 尼多后 |
| 32 | NIDORAN M | 尼多朗 | 尼多朗 |
| 33 | NIDORINO | 尼多力諾 | 尼多力诺 |
| 34 | NIDOKING | 尼多王 | 尼多王 |
| 35 | CLEFAIRY | 皮皮 | 皮皮 |
| 36 | CLEFABLE | 皮可西 | 皮可西 |
| 37 | VULPIX | 六尾 | 六尾 |
| 38 | NINETALES | 九尾 | 九尾 |
| 39 | JIGGLYPUFF | 胖丁 | 胖丁 |
| 40 | WIGGLYTUFF | 胖可丁 | 胖可丁 |
| 41 | ZUBAT | 超音蝠 | 超音蝠 |
| 42 | GOLBAT | 大嘴蝠 | 大嘴蝠 |
| 43 | ODDISH | 走路草 | 走路草 |
| 44 | GLOOM | 臭臭花 | 臭臭花 |
| 45 | VILEPLUME | 霸王花 | 霸王花 |
| 46 | PARAS | 派拉斯 | 派拉斯 |
| 47 | PARASECT | 派拉斯特 | 派拉斯特 |
| 48 | VENONAT | 毛球 | 毛球 |
| 49 | VENOMOTH | 摩魯蛾 | 摩鲁蛾 |
| 50 | DIGLETT | 地鼠 | 地鼠 |
| 51 | DUGTRIO | 三地鼠 | 三地鼠 |
| 52 | MEOWTH | 喵喵 | 喵喵 |
| 53 | PERSIAN | 貓老大 | 猫老大 |
| 54 | PSYDUCK | 可達鴨 | 可达鸭 |
| 55 | GOLDUCK | 哥達鴨 | 哥达鸭 |
| 56 | MANKEY | 猴怪 | 猴怪 |
| 57 | PRIMEAPE | 火爆猴 | 火暴猴 |
| 58 | GROWLITHE | 卡蒂狗 | 卡蒂狗 |
| 59 | ARCANINE | 風速狗 | 风速狗 |
| 60 | POLIWAG | 蚊香蝌蚪 | 蚊香蝌蚪 |
| 61 | POLIWHIRL | 蚊香君 | 蚊香君 |
| 62 | POLIWRATH | 蚊香泳士 | 蚊香泳士 |
| 63 | ABRA | 凱西 | 凯西 |
| 64 | KADABRA | 勇基拉 | 勇基拉 |
| 65 | ALAKAZAM | 胡地 | 胡地 |
| 66 | MACHOP | 腕力 | 腕力 |
| 67 | MACHOKE | 豪力 | 豪力 |
| 68 | MACHAMP | 怪力 | 怪力 |
| 69 | BELLSPROUT | 喇叭芽 | 喇叭芽 |
| 70 | WEEPINBELL | 口呆花 | 口呆花 |
| 71 | VICTREEBEL | 大食花 | 大食花 |
| 72 | TENTACOOL | 瑪瑙水母 | 玛瑙水母 |
| 73 | TENTACRUEL | 毒刺水母 | 毒刺水母 |
| 74 | GEODUDE | 小拳石 | 小拳石 |
| 75 | GRAVELER | 隆隆石 | 隆隆石 |
| 76 | GOLEM | 隆隆岩 | 隆隆岩 |
| 77 | PONYTA | 小火馬 | 小火马 |
| 78 | RAPIDASH | 烈焰馬 | 烈焰马 |
| 79 | SLOWPOKE | 呆呆獸 | 呆呆兽 |
| 80 | SLOWBRO | 呆殼獸 | 呆壳兽 |
| 81 | MAGNEMITE | 小磁怪 | 小磁怪 |
| 82 | MAGNETON | 三合一磁怪 | 三合一磁怪 |
| 83 | FARFETCHD | 大蔥鴨 | 大葱鸭 |
| 84 | DODUO | 嘟嘟 | 嘟嘟 |
| 85 | DODRIO | 嘟嘟利 | 嘟嘟利 |
| 86 | SEEL | 小海獅 | 小海狮 |
| 87 | DEWGONG | 白海獅 | 白海狮 |
| 88 | GRIMER | 臭泥 | 臭泥 |
| 89 | MUK | 臭臭泥 | 臭臭泥 |
| 90 | SHELLDER | 大舌貝 | 大舌贝 |
| 91 | CLOYSTER | 刺甲貝 | 刺甲贝 |
| 92 | GASTLY | 鬼斯 | 鬼斯 |
| 93 | HAUNTER | 鬼斯通 | 鬼斯通 |
| 94 | GENGAR | 耿鬼 | 耿鬼 |
| 95 | ONIX | 大岩蛇 | 大岩蛇 |
| 96 | DROWZEE | 催眠貘 | 催眠貘 |
| 97 | HYPNO | 引夢貘人 | 引梦貘人 |
| 98 | KRABBY | 大鉗蟹 | 大钳蟹 |
| 99 | KINGLER | 巨鉗蟹 | 巨钳蟹 |
| 100 | VOLTORB | 霹靂電球 | 霹雳电球 |
| 101 | ELECTRODE | 頑皮雷彈 | 顽皮雷弹 |
| 102 | EXEGGCUTE | 蛋蛋 | 蛋蛋 |
| 103 | EXEGGUTOR | 椰蛋樹 | 椰蛋树 |
| 104 | CUBONE | 卡拉卡拉 | 卡拉卡拉 |
| 105 | MAROWAK | 嘎啦嘎啦 | 嘎啦嘎啦 |
| 106 | HITMONLEE | 飛腿郎 | 飞腿郎 |
| 107 | HITMONCHAN | 快拳郎 | 快拳郎 |
| 108 | LICKITUNG | 大舌頭 | 大舌头 |
| 109 | KOFFING | 瓦斯彈 | 瓦斯弹 |
| 110 | WEEZING | 雙彈瓦斯 | 双弹瓦斯 |
| 111 | RHYHORN | 獨角犀牛 | 独角犀牛 |
| 112 | RHYDON | 鑽角犀獸 | 钻角犀兽 |
| 113 | CHANSEY | 吉利蛋 | 吉利蛋 |
| 114 | TANGELA | 蔓藤怪 | 蔓藤怪 |
| 115 | KANGASKHAN | 袋獸 | 袋兽 |
| 116 | HORSEA | 墨海馬 | 墨海马 |
| 117 | SEADRA | 海刺龍 | 海刺龙 |
| 118 | GOLDEEN | 角金魚 | 角金鱼 |
| 119 | SEAKING | 金魚王 | 金鱼王 |
| 120 | STARYU | 海星星 | 海星星 |
| 121 | STARMIE | 寶石海星 | 宝石海星 |
| 122 | MR. MIME | 魔牆人偶 | 魔墙人偶 |
| 123 | SCYTHER | 飛天螳螂 | 飞天螳螂 |
| 124 | JYNX | 迷唇姐 | 迷唇姐 |
| 125 | ELECTABUZZ | 電擊獸 | 电击兽 |
| 126 | MAGMAR | 鴨嘴火獸 | 鸭嘴火兽 |
| 127 | PINSIR | 凱羅斯 | 凯罗斯 |
| 128 | TAUROS | 肯泰羅 | 肯泰罗 |
| 129 | MAGIKARP | 鯉魚王 | 鲤鱼王 |
| 130 | GYARADOS | 暴鯉龍 | 暴鲤龙 |
| 131 | LAPRAS | 拉普拉斯 | 拉普拉斯 |
| 132 | DITTO | 百變怪 | 百变怪 |
| 133 | EEVEE | 伊布 | 伊布 |
| 134 | VAPOREON | 水伊布 | 水伊布 |
| 135 | JOLTEON | 雷伊布 | 雷伊布 |
| 136 | FLAREON | 火伊布 | 火伊布 |
| 137 | PORYGON | 多邊獸 | 多边兽 |
| 138 | OMANYTE | 菊石獸 | 菊石兽 |
| 139 | OMASTAR | 多刺菊石獸 | 多刺菊石兽 |
| 140 | KABUTO | 化石盔 | 化石盔 |
| 141 | KABUTOPS | 鐮刀盔 | 镰刀盔 |
| 142 | AERODACTYL | 化石翼龍 | 化石翼龙 |
| 143 | SNORLAX | 卡比獸 | 卡比兽 |
| 144 | ARTICUNO | 急凍鳥 | 急冻鸟 |
| 145 | ZAPDOS | 閃電鳥 | 闪电鸟 |
| 146 | MOLTRES | 火焰鳥 | 火焰鸟 |
| 147 | DRATINI | 迷你龍 | 迷你龙 |
| 148 | DRAGONAIR | 哈克龍 | 哈克龙 |
| 149 | DRAGONITE | 快龍 | 快龙 |
| 150 | MEWTWO | 超夢 | 超梦 |
| 151 | MEW | 夢幻 | 梦幻 |
