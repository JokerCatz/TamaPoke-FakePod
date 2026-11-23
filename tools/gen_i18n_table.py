#!/usr/bin/env python3
"""Writes docs/i18n/zh-TW.md: a side-by-side table (source language ↔ Traditional Chinese) generated from i18n.cpp, i18n.h and tools/dex_names.py,
so the table cannot drift from what the firmware actually shows.   python3 tools/gen_i18n_table.py"""
import ast, os, re, sys
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.join(HERE, '..')
sys.path.insert(0, HERE)
import test_i18n_formats as T

# Notes on terminology choices (Taiwan usage), keyed by StrId / medal index / species number
NOTES = {
    'S_IS_SHINY': '台灣官方稱閃光寶可夢為「異色」',
    'S_BERRY_UNK': '台灣官方用「樹果」（不是「漿果」）',
    'S_POKEDEX_FMT': '官方全名「寶可夢圖鑑」，版面窄所以縮成「圖鑑」',
    'S_MEDAL_BANNER': '「徽章」在台灣官方是道館徽章，故這裡的成就用「勳章」避免混淆',
    'S_MEDALS_FMT': '同上，用「勳章」',
    'S_STREAK_DAYS_FMT': '日數放在句中，方便中文語序',
    'S_RELEASE_FMT': '「放生」為台灣官方「放走寶可夢」用語',
    'S_VIN': '原文 BOND（羈絆），遊戲內名為「親密度」，簡稱「親密」',
    'S_EVO_BLOCKED': '避免使用「≥」：Cubic 11 字型沒有此字',
    'S_FAREWELL_BTN': '%s 是寵物名字，緊接在後不加空格（中文不需要）',
    'S_RUNAWAY_BTN': '同上',
    'S_NO_SPRITES': '「精靈」是這個專案裡動畫圖檔的稱呼',
    'S_LOAD_SPRITES': '精簡成「請放進 SD 卡」以符合欄寬',
}

def table(src, name):
    """[language][index] -> the decoded C string (octal escapes such as \\240 become the CP437 byte value as a code point)."""
    return [[ast.literal_eval(s) for s in row] for row in T.extract_table(src, name, len(T.LANGS))]

def main():
    src = open(os.path.join(ROOT, 'i18n.cpp'), encoding='utf-8').read()
    hdr = open(os.path.join(ROOT, 'i18n.h'), encoding='utf-8').read()
    ids = re.findall(r'\bS_[A-Z0-9_]+\b', hdr[hdr.index('enum StrId'):hdr.index('STR_COUNT')])
    S = table(src, 'STRINGS')
    EN, ZH, ZHS = S[T.LANGS.index('EN')], S[T.LANGS.index('ZH')], S[T.LANGS.index('ZHS')]
    assert len(EN) == len(ZH) == len(ZHS) == len(ids), (len(EN), len(ZH), len(ids))
    def esc(s): return s.replace('|', '\\|')
    out = ['# 繁體中文對照表（台灣用語）', '',
           '由 `tools/gen_i18n_table.py` 從 `i18n.cpp` 產生，**請勿手改**；要改譯文請改 `i18n.cpp` 後重新執行。', '',
           '- 寶可夢名稱：全部取自 PokéAPI 的 `zh-Hant` 欄位（台灣官方譯名），由 `tools/gen_names.py` 抓取，共 151 隻。',
           '- 介面字串：人工翻譯，格式占位符（`%u`、`%s` 等）與英文完全一致，由 `tools/test_i18n_formats.py` 檢查。',
           "- 顯示字型：依文字大小對應——大小 1 用 Cubic 11（OFL）11 px、大小 2 用 Unifont 子集 16 px（與拉丁字同高）、大小 3 用 Cubic 11 放大兩倍 22 px。",
           '## 介面字串', '', '| # | ID | English | 繁體中文 | 简体中文 | 備註 |', '|---|---|---|---|---|---|']
    for k, sid in enumerate(ids):
        out.append(f'| {k} | `{sid}` | {esc(EN[k])} | {esc(ZH[k])} | {esc(ZHS[k])} | {NOTES.get(sid, "")} |')
    out += ['', '## 勳章', '', '| # | English（名稱 / 標籤 / 說明） | 繁體中文 | 简体中文 | 備註 |', '|---|---|---|---|---|']
    M = {nm: table(src, nm) for nm in ('MED_NAME', 'MED_LBL', 'MED_DSC')}
    for k in range(8):
        en = ' / '.join(M[nm][T.LANGS.index('EN')][k] for nm in M)
        zh = ' / '.join(M[nm][T.LANGS.index('ZH')][k] for nm in M)
        zhs = ' / '.join(M[nm][T.LANGS.index('ZHS')][k] for nm in M)
        out.append(f'| {k} | {esc(en)} | {esc(zh)} | {esc(zhs)} | {NOTES.get("MED"+str(k), "")} |')
    ns = {}; exec(open(os.path.join(HERE, 'dex_names.py'), encoding='utf-8').read(), ns)
    names = ns['LOCAL_NAMES']
    dex = open(os.path.join(ROOT, 'dex.h'), encoding='utf-8').read()
    en_names = re.findall(r'\{ "([^"]+)", \d+, \d+, R_\w+, 0x[0-9A-F]+, [^}]*\},\s*// (\d+) ', dex)
    en_by = {int(num): nm for nm, num in en_names}
    out += ['', '## 寶可夢名稱（第一代 151 隻）', '', '| # | English | 繁體中文 | 简体中文 |', '|---|---|---|---|']
    for num in range(1, 152):
        d = names.get(num, {})
        out.append(f'| {num} | {en_by.get(num, "?")} | {d.get("zh", "")} | {d.get("zh_hans", "")} |')
    path = os.path.join(ROOT, 'docs', 'i18n', 'zh-TW.md')
    open(path, 'w', encoding='utf-8').write('\n'.join(out) + '\n')
    print('wrote', os.path.normpath(path), f'({len(ids)} strings, 8 medals, 151 species)')

if __name__ == '__main__':
    main()
