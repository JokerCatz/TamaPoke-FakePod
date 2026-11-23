#!/usr/bin/env python3
"""Width budget for the Traditional Chinese strings: at the same text size, a translation must not be wider than the widest one the layout already
has to hold (the Latin languages at 6 px per char, and JA/KO). Model, per text size 2 (the usual body size): Latin / ASCII 12 px per char;
CJK full-width 16 px, half-width ASCII 8 px (Unifont 16). %-specs count as 3 characters. Exit status 1 if any ZH string is over budget.   python3 tools/check_zh_width.py"""
import os, re, sys, unicodedata
HERE = os.path.dirname(os.path.abspath(__file__)); sys.path.insert(0, HERE)
import ast, test_i18n_formats as T
SPEC = T.SPEC_RE
def width(s, lang):
    s = SPEC.sub('000', s)
    cjk = lang in ('ZH', 'ZHS')
    w = 0
    for ch in s:
        full = unicodedata.east_asian_width(ch) in ('W', 'F')
        w += (16 if full else 8) if cjk else 12
    return w
def main():
    src = open(os.path.join(HERE, '..', 'i18n.cpp'), encoding='utf-8').read()
    hdr = open(os.path.join(HERE, '..', 'i18n.h'), encoding='utf-8').read()
    ids = re.findall(r'\bS_[A-Z0-9_]+\b', hdr[hdr.index('enum StrId'):hdr.index('STR_COUNT')])
    rows = [[ast.literal_eval(s) for s in r] for r in T.extract_table(src, 'STRINGS', len(T.LANGS))]
    bad = 0; tight = 0
    zi = T.LANGS.index('ZH')
    for k, sid in enumerate(ids):
        ws = {l: width(rows[i][k], l) for i, l in enumerate(T.LANGS)}
        budget = max(v for l, v in ws.items() if not l.startswith('ZH'))
        z = max(ws['ZH'], ws['ZHS'])
        if z > budget: bad += 1; print(f'OVER   {sid:18} zh={z}px > widest other={budget}px  {rows[zi][k]!r}')
        elif z > budget * 0.9: tight += 1
    print(f'{len(ids)} strings: {bad} over budget, {tight} within 10% of it')
    return 1 if bad else 0
if __name__ == '__main__': sys.exit(main())
