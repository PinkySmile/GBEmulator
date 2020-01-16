import re
LAMBDA_REGEX = re.compile(r"//! ([\dA-F]{2}); ([^\n]*)\n\[]\(CPU &\S*, CPU::Registers &\S*\)\s*{\s*([^\n]+)\s*},?", re.MULTILINE)

with open("raw_data/lambda") as fd:
    txt = fd.read()
    print(re.sub(LAMBDA_REGEX, r"//! \1; \2\ncase 0x\1:\n\t\3", txt))