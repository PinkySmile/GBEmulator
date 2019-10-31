import re

f = lambda x: x.split(' ')[0].upper() + (' ' in x and f" {x.split(' ', 1)[1]}" or '')

with open('raw_html_bits') as fd:
    raw_html = fd.read()

al = re.findall(r"^<td axis=\".{6}\|\d+\|\d+/?\d*\|([^\"]+)\">([^<].+)</td>$", raw_html, re.MULTILINE)

#al.insert(0xCB, ("BITS", "BITS"))
#al.insert(0xDD, ("IX", "IX"))
#al.insert(0xED, ("EXTD", "EXTD"))
#al.insert(0xFD, ("IV", "IV"))


print('\n\n'.join(f"//! {i:02X}; {f(v[1])}: {v[0]}" for i, v in enumerate(al)))
