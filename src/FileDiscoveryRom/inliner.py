import sys

with open(sys.argv[1], "rb") as fd:
	b = fd.read()
while b[-1] == 0:
	b = b[:-1]
with open(sys.argv[2], "w") as fd:
	fd.write("const unsigned char romData[] = {\n")
	for i, v in enumerate(b):
		if i:
			fd.write(",\n")
		fd.write("\t0x{:02X}".format(v))
	fd.write("\n};")
