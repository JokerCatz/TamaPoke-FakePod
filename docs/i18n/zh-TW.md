# 繁體中文對照表（台灣用語）

由 `tools/gen_i18n_table.py` 從 `i18n.cpp` 產生，**請勿手改**；要改譯文請改 `i18n.cpp` 後重新執行。

- 寶可夢名稱：全部取自 PokéAPI 的 `zh-Hant` 欄位（台灣官方譯名），由 `tools/gen_names.py` 抓取，共 151 隻。
- 介面字串：人工翻譯，格式占位符（`%u`、`%s` 等）與英文完全一致，由 `tools/test_i18n_formats.py` 檢查。
- 顯示字型：依文字大小對應——大小 1 用 Cubic 11（OFL）11 px、大小 2 用 Unifont 子集 16 px（與拉丁字同高）、大小 3 用 Cubic 11 放大兩倍 22 px。
## 介面字串

| # | ID | English | 繁體中文 | 備註 |
|---|---|---|---|---|
| 0 | `S_EVOLVING` | Evolving! | 進化中！ |  |
| 1 | `S_EATING` | Yum yum! | 好好吃！ |  |
| 2 | `S_LIKES` | It likes it! | 牠很喜歡！ |  |
| 3 | `S_HUNGRY` | It's hungry! | 牠肚子餓了！ |  |
| 4 | `S_NEEDS_BATH` | Needs a bath! | 該洗澡了！ |  |
| 5 | `S_EXHAUSTED` | Worn out... | 累壞了…… |  |
| 6 | `S_SAD` | Feeling sad... | 牠很難過…… |  |
| 7 | `S_CHUBBY` | A bit chubby... | 有點胖胖的…… |  |
| 8 | `S_IS_SHINY` | It's SHINY!! | 是異色寶可夢！！ | 台灣官方稱閃光寶可夢為「異色」 |
| 9 | `S_HAPPY` | It's happy | 牠很開心 |  |
| 10 | `S_FAREWELL` | THANKS! Farewell | 謝謝你！再見了 |  |
| 11 | `S_RUNAWAY` | It ran away... | 牠跑走了…… |  |
| 12 | `S_GOODBYE` | Bye! Waving goodbye... | 再見！揮手道別…… |  |
| 13 | `S_EGG_HDR` | EGG | 蛋 |  |
| 14 | `S_EGG_LEGEND` | Legendary egg!? | 傳說的蛋！？ |  |
| 15 | `S_EGG_RARE` | Rare egg! | 稀有的蛋！ |  |
| 16 | `S_EGG_TOUCH` | Tap the egg... | 點一下蛋…… |  |
| 17 | `S_EGG_MOVES` | It moves! | 動了！ |  |
| 18 | `S_EGG_ALMOST` | Almost there! | 快孵化了！ |  |
| 19 | `S_POKEDEX_FMT` | POKEDEX %u/151 | 圖鑑 %u/151 | 官方全名「寶可夢圖鑑」，版面窄所以縮成「圖鑑」 |
| 20 | `S_NAME_FMT` | %s%s Lv.%u | %s%s Lv.%u |  |
| 21 | `S_RELEASE_FMT` | Release %s? | 要放生%s嗎？ | 「放生」為台灣官方「放走寶可夢」用語 |
| 22 | `S_YES` | YES | 是 |  |
| 23 | `S_NO` | NO | 否 |  |
| 24 | `S_HITS_FMT` | %u HITS | 擊中 %u 次 |  |
| 25 | `S_STR_GAIN_FMT` | STR +%u | 力量 +%u |  |
| 26 | `S_NEW_RECORD` | NEW RECORD! | 新紀錄！ |  |
| 27 | `S_RECORD_FMT` | BEST: %u | 最佳：%u |  |
| 28 | `S_HIT_FAST` | HIT FAST! | 快打！ |  |
| 29 | `S_SCORE_FMT` | SCORE: %u | 得分：%u |  |
| 30 | `S_GREAT_JOY` | So much fun! | 好開心！ |  |
| 31 | `S_PLUS_JOY` | +happiness | +心情 |  |
| 32 | `S_SET_TIME` | SET TIME | 設定時間 |  |
| 33 | `S_HOUR` | HOUR | 時 |  |
| 34 | `S_MIN` | MIN | 分 |  |
| 35 | `S_CLOCK_CANCEL` | swipe up: cancel | 上滑：取消 |  |
| 36 | `S_LANG_LABEL` | Lang | 語言 |  |
| 37 | `S_MEDAL_BANNER` | MEDAL! | 獲得勳章！ | 「徽章」在台灣官方是道館徽章，故這裡的成就用「勳章」避免混淆 |
| 38 | `S_GREAT` | AWESOME! | 太棒了！ |  |
| 39 | `S_STREAK_DAYS_FMT` | %u DAY STREAK! | 連續 %u 天！ | 日數放在句中，方便中文語序 |
| 40 | `S_STREAK_FMT` | STREAK %u  best %u | 連續 %u 天　最高 %u |  |
| 41 | `S_VIN` | BOND | 親密 | 原文 BOND（羈絆），遊戲內名為「親密度」，簡稱「親密」 |
| 42 | `S_BERRY_UNK` | BERRY ??? | 樹果 ??? | 台灣官方用「樹果」（不是「漿果」） |
| 43 | `S_BERRY_RED` | RED BERRY | 紅色樹果 |  |
| 44 | `S_BERRY_BLUE` | BLUE BERRY | 藍色樹果 |  |
| 45 | `S_BERRY_GREEN` | GREEN BERRY | 綠色樹果 |  |
| 46 | `S_INFO_FMT` | %s   AGE %lud | %s　年齡 %lu 天 |  |
| 47 | `S_RENAME_HINT` | tap name: rename | 點名字：改名 |  |
| 48 | `S_BATTLE` | BATTLE | 對戰 |  |
| 49 | `S_STAT_ATK` | ATK | 攻擊 |  |
| 50 | `S_STAT_DEF` | DEF | 防禦 |  |
| 51 | `S_STAT_SPE` | SPD | 速度 |  |
| 52 | `S_STAT_WGT` | WGT | 體重 |  |
| 53 | `S_TRAIN_STR` | TRAIN STRENGTH | 訓練力量 |  |
| 54 | `S_MEDALS_FMT` | MEDALS %d/%d | 勳章 %d/%d | 同上，用「勳章」 |
| 55 | `S_BACK` | tap: back | 點一下：返回 |  |
| 56 | `S_NAME` | NAME: | 名字： |  |
| 57 | `S_DETAIL_BACK` | tap to go back | 點一下返回 |  |
| 58 | `S_BAR_FOOD` | FOOD | 飽食 |  |
| 59 | `S_BAR_JOY` | JOY | 心情 |  |
| 60 | `S_BAR_ENE` | ENE | 體力 |  |
| 61 | `S_BAR_HYG` | HYG | 清潔 |  |
| 62 | `S_REC_FMT` | BEST %u | 最佳 %u |  |
| 63 | `S_PROGRESS` | PROGRESS | 成長 |  |
| 64 | `S_LVL_FMT` | Lv.%u | Lv.%u |  |
| 65 | `S_NEXT_LVL_FMT` | %u min to Lv.%u | %u 分後 Lv.%u |  |
| 66 | `S_EVO_LABEL` | EVOLUTION | 進化 |  |
| 67 | `S_FINAL_FORM` | Final form | 最終型態 |  |
| 68 | `S_EVO_READY` | Ready to evolve! | 可以進化了！ |  |
| 69 | `S_EVO_BLOCKED` | All needs >=40 to evolve | 全部需求 40 以上才能進化 | 避免使用「≥」：Cubic 11 字型沒有此字 |
| 70 | `S_EVO_IN_FMT` | Evolves in %u lv. | 再 %u 級進化 |  |
| 71 | `S_MISTAKES_FMT` | Slip-ups: %u | 失誤：%u |  |
| 72 | `S_SND_ON` | SND ON | 音效 開 |  |
| 73 | `S_SND_OFF` | SND OFF | 音效 關 |  |
| 74 | `S_EVO_TAP` | EVOLVE! | 進化！ |  |
| 75 | `S_FAREWELL_BTN` | %s wants to tell you... | %s有話想對你說…… | %s 是寵物名字，緊接在後不加空格（中文不需要） |
| 76 | `S_RUNAWAY_BTN` | %s feels abandoned... | %s覺得被拋棄了…… | 同上 |
| 77 | `S_EVO_Q` | Evolve? | 要進化嗎？ |  |
| 78 | `S_EVO_KEEP` | Keep form | 維持型態 |  |
| 79 | `S_FAR_Q` | Say goodbye? | 要道別嗎？ |  |
| 80 | `S_FAR_GO` | Goodbye | 道別 |  |
| 81 | `S_FAR_STAY` | Stay together | 繼續相伴 |  |
| 82 | `S_CHOOSE_STARTER` | Choose your starter | 選擇你的夥伴 |  |
| 83 | `S_NO_SPRITES` | No sprites | 沒有精靈圖 | 「精靈」是這個專案裡動畫圖檔的稱呼 |
| 84 | `S_LOAD_SPRITES` | Load them onto the SD | 請放進 SD 卡 | 精簡成「請放進 SD 卡」以符合欄寬 |
| 85 | `S_HOLD_EXIT` | Hold to exit | 長按離開 |  |

## 勳章

| # | English（名稱 / 標籤 / 說明） | 繁體中文（名稱 / 標籤 / 說明） | 備註 |
|---|---|---|---|
| 0 | Lv.10 / Lv10 / LEVEL 10 | Lv.10 / Lv10 / 等級 10 |  |
| 1 | Lv.25 / Lv25 / LEVEL 25 | Lv.25 / Lv25 / 等級 25 |  |
| 2 | Lv.50 / Lv50 / LEVEL 50 | Lv.50 / Lv50 / 等級 50 |  |
| 3 | BERRY / BERRY / BERRY FOUND | 樹果 / 樹果 / 找到樹果 |  |
| 4 | 7 STREAK / 7DAYS / 7 DAY STREAK | 連續7天 / 7天 / 連續 7 天 |  |
| 5 | BOND / BOND / MAX BOND | 親密 / 親密 / 親密度最高 |  |
| 6 | TOP FORM / TOP / FINAL FORM | 最終型態 / 最終 / 最終型態 |  |
| 7 | IN SHAPE / FIT / IN SHAPE | 健康 / 健康 / 身體健康 |  |

## 寶可夢名稱（第一代 151 隻）

| # | English | 日本語 | 繁體中文 |
|---|---|---|---|
| 1 | BULBASAUR | フシギダネ | 妙蛙種子 |
| 2 | IVYSAUR | フシギソウ | 妙蛙草 |
| 3 | VENUSAUR | フシギバナ | 妙蛙花 |
| 4 | CHARMANDER | ヒトカゲ | 小火龍 |
| 5 | CHARMELEON | リザード | 火恐龍 |
| 6 | CHARIZARD | リザードン | 噴火龍 |
| 7 | SQUIRTLE | ゼニガメ | 傑尼龜 |
| 8 | WARTORTLE | カメール | 卡咪龜 |
| 9 | BLASTOISE | カメックス | 水箭龜 |
| 10 | CATERPIE | キャタピー | 綠毛蟲 |
| 11 | METAPOD | トランセル | 鐵甲蛹 |
| 12 | BUTTERFREE | バタフリー | 巴大蝶 |
| 13 | WEEDLE | ビードル | 獨角蟲 |
| 14 | KAKUNA | コクーン | 鐵殼蛹 |
| 15 | BEEDRILL | スピアー | 大針蜂 |
| 16 | PIDGEY | ポッポ | 波波 |
| 17 | PIDGEOTTO | ピジョン | 比比鳥 |
| 18 | PIDGEOT | ピジョット | 大比鳥 |
| 19 | RATTATA | コラッタ | 小拉達 |
| 20 | RATICATE | ラッタ | 拉達 |
| 21 | SPEAROW | オニスズメ | 烈雀 |
| 22 | FEAROW | オニドリル | 大嘴雀 |
| 23 | EKANS | アーボ | 阿柏蛇 |
| 24 | ARBOK | アーボック | 阿柏怪 |
| 25 | PIKACHU | ピカチュウ | 皮卡丘 |
| 26 | RAICHU | ライチュウ | 雷丘 |
| 27 | SANDSHREW | サンド | 穿山鼠 |
| 28 | SANDSLASH | サンドパン | 穿山王 |
| 29 | NIDORAN H | ニドランF | 尼多蘭 |
| 30 | NIDORINA | ニドリーナ | 尼多娜 |
| 31 | NIDOQUEEN | ニドクイン | 尼多后 |
| 32 | NIDORAN M | ニドランM | 尼多朗 |
| 33 | NIDORINO | ニドリーノ | 尼多力諾 |
| 34 | NIDOKING | ニドキング | 尼多王 |
| 35 | CLEFAIRY | ピッピ | 皮皮 |
| 36 | CLEFABLE | ピクシー | 皮可西 |
| 37 | VULPIX | ロコン | 六尾 |
| 38 | NINETALES | キュウコン | 九尾 |
| 39 | JIGGLYPUFF | プリン | 胖丁 |
| 40 | WIGGLYTUFF | プクリン | 胖可丁 |
| 41 | ZUBAT | ズバット | 超音蝠 |
| 42 | GOLBAT | ゴルバット | 大嘴蝠 |
| 43 | ODDISH | ナゾノクサ | 走路草 |
| 44 | GLOOM | クサイハナ | 臭臭花 |
| 45 | VILEPLUME | ラフレシア | 霸王花 |
| 46 | PARAS | パラス | 派拉斯 |
| 47 | PARASECT | パラセクト | 派拉斯特 |
| 48 | VENONAT | コンパン | 毛球 |
| 49 | VENOMOTH | モルフォン | 摩魯蛾 |
| 50 | DIGLETT | ディグダ | 地鼠 |
| 51 | DUGTRIO | ダグトリオ | 三地鼠 |
| 52 | MEOWTH | ニャース | 喵喵 |
| 53 | PERSIAN | ペルシアン | 貓老大 |
| 54 | PSYDUCK | コダック | 可達鴨 |
| 55 | GOLDUCK | ゴルダック | 哥達鴨 |
| 56 | MANKEY | マンキー | 猴怪 |
| 57 | PRIMEAPE | オコリザル | 火爆猴 |
| 58 | GROWLITHE | ガーディ | 卡蒂狗 |
| 59 | ARCANINE | ウインディ | 風速狗 |
| 60 | POLIWAG | ニョロモ | 蚊香蝌蚪 |
| 61 | POLIWHIRL | ニョロゾ | 蚊香君 |
| 62 | POLIWRATH | ニョロボン | 蚊香泳士 |
| 63 | ABRA | ケーシィ | 凱西 |
| 64 | KADABRA | ユンゲラー | 勇基拉 |
| 65 | ALAKAZAM | フーディン | 胡地 |
| 66 | MACHOP | ワンリキー | 腕力 |
| 67 | MACHOKE | ゴーリキー | 豪力 |
| 68 | MACHAMP | カイリキー | 怪力 |
| 69 | BELLSPROUT | マダツボミ | 喇叭芽 |
| 70 | WEEPINBELL | ウツドン | 口呆花 |
| 71 | VICTREEBEL | ウツボット | 大食花 |
| 72 | TENTACOOL | メノクラゲ | 瑪瑙水母 |
| 73 | TENTACRUEL | ドククラゲ | 毒刺水母 |
| 74 | GEODUDE | イシツブテ | 小拳石 |
| 75 | GRAVELER | ゴローン | 隆隆石 |
| 76 | GOLEM | ゴローニャ | 隆隆岩 |
| 77 | PONYTA | ポニータ | 小火馬 |
| 78 | RAPIDASH | ギャロップ | 烈焰馬 |
| 79 | SLOWPOKE | ヤドン | 呆呆獸 |
| 80 | SLOWBRO | ヤドラン | 呆殼獸 |
| 81 | MAGNEMITE | コイル | 小磁怪 |
| 82 | MAGNETON | レアコイル | 三合一磁怪 |
| 83 | FARFETCHD | カモネギ | 大蔥鴨 |
| 84 | DODUO | ドードー | 嘟嘟 |
| 85 | DODRIO | ドードリオ | 嘟嘟利 |
| 86 | SEEL | パウワウ | 小海獅 |
| 87 | DEWGONG | ジュゴン | 白海獅 |
| 88 | GRIMER | ベトベター | 臭泥 |
| 89 | MUK | ベトベトン | 臭臭泥 |
| 90 | SHELLDER | シェルダー | 大舌貝 |
| 91 | CLOYSTER | パルシェン | 刺甲貝 |
| 92 | GASTLY | ゴース | 鬼斯 |
| 93 | HAUNTER | ゴースト | 鬼斯通 |
| 94 | GENGAR | ゲンガー | 耿鬼 |
| 95 | ONIX | イワーク | 大岩蛇 |
| 96 | DROWZEE | スリープ | 催眠貘 |
| 97 | HYPNO | スリーパー | 引夢貘人 |
| 98 | KRABBY | クラブ | 大鉗蟹 |
| 99 | KINGLER | キングラー | 巨鉗蟹 |
| 100 | VOLTORB | ビリリダマ | 霹靂電球 |
| 101 | ELECTRODE | マルマイン | 頑皮雷彈 |
| 102 | EXEGGCUTE | タマタマ | 蛋蛋 |
| 103 | EXEGGUTOR | ナッシー | 椰蛋樹 |
| 104 | CUBONE | カラカラ | 卡拉卡拉 |
| 105 | MAROWAK | ガラガラ | 嘎啦嘎啦 |
| 106 | HITMONLEE | サワムラー | 飛腿郎 |
| 107 | HITMONCHAN | エビワラー | 快拳郎 |
| 108 | LICKITUNG | ベロリンガ | 大舌頭 |
| 109 | KOFFING | ドガース | 瓦斯彈 |
| 110 | WEEZING | マタドガス | 雙彈瓦斯 |
| 111 | RHYHORN | サイホーン | 獨角犀牛 |
| 112 | RHYDON | サイドン | 鑽角犀獸 |
| 113 | CHANSEY | ラッキー | 吉利蛋 |
| 114 | TANGELA | モンジャラ | 蔓藤怪 |
| 115 | KANGASKHAN | ガルーラ | 袋獸 |
| 116 | HORSEA | タッツー | 墨海馬 |
| 117 | SEADRA | シードラ | 海刺龍 |
| 118 | GOLDEEN | トサキント | 角金魚 |
| 119 | SEAKING | アズマオウ | 金魚王 |
| 120 | STARYU | ヒトデマン | 海星星 |
| 121 | STARMIE | スターミー | 寶石海星 |
| 122 | MR. MIME | バリヤード | 魔牆人偶 |
| 123 | SCYTHER | ストライク | 飛天螳螂 |
| 124 | JYNX | ルージュラ | 迷唇姐 |
| 125 | ELECTABUZZ | エレブー | 電擊獸 |
| 126 | MAGMAR | ブーバー | 鴨嘴火獸 |
| 127 | PINSIR | カイロス | 凱羅斯 |
| 128 | TAUROS | ケンタロス | 肯泰羅 |
| 129 | MAGIKARP | コイキング | 鯉魚王 |
| 130 | GYARADOS | ギャラドス | 暴鯉龍 |
| 131 | LAPRAS | ラプラス | 拉普拉斯 |
| 132 | DITTO | メタモン | 百變怪 |
| 133 | EEVEE | イーブイ | 伊布 |
| 134 | VAPOREON | シャワーズ | 水伊布 |
| 135 | JOLTEON | サンダース | 雷伊布 |
| 136 | FLAREON | ブースター | 火伊布 |
| 137 | PORYGON | ポリゴン | 多邊獸 |
| 138 | OMANYTE | オムナイト | 菊石獸 |
| 139 | OMASTAR | オムスター | 多刺菊石獸 |
| 140 | KABUTO | カブト | 化石盔 |
| 141 | KABUTOPS | カブトプス | 鐮刀盔 |
| 142 | AERODACTYL | プテラ | 化石翼龍 |
| 143 | SNORLAX | カビゴン | 卡比獸 |
| 144 | ARTICUNO | フリーザー | 急凍鳥 |
| 145 | ZAPDOS | サンダー | 閃電鳥 |
| 146 | MOLTRES | ファイヤー | 火焰鳥 |
| 147 | DRATINI | ミニリュウ | 迷你龍 |
| 148 | DRAGONAIR | ハクリュー | 哈克龍 |
| 149 | DRAGONITE | カイリュー | 快龍 |
| 150 | MEWTWO | ミュウツー | 超夢 |
| 151 | MEW | ミュウ | 夢幻 |
