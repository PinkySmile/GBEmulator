def generateLine(name):
	needArgs = True
	if "**" in name:
		name = name.replace("**", '" + std::to_string(cpu.read(address) | (cpu.read(address + 1) << 1U)) + "')
	elif "*" in name:
		name = name.replace("*", '" + std::to_string(cpu.read(address)) + "')
	else:
		needArgs = False
	return "[](CPU &" + ("cpu" if needArgs else "") + ", unsigned short" + (" address" if needArgs else "") + ') { return "' + name + '"; },'
	
