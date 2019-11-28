from sys import argv
import json

with open(argv[1], 'r') as fd:
    txt = fd.read()

b = 0 if len(argv) <= 2 else int(argv[2], 16)
ls = [[i + b, *[(int(j) if j.isdigit() else j) for j in v.split(' ')]] for i, v in enumerate(txt.split('\n')) if v]
print('[', *ls, sep='\n    ',)
print(']')