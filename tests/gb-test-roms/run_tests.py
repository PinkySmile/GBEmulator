import os
import sys
import socket
import subprocess
import select
import asyncio

base_port = 10800
S_IFMT = 0o170000
S_IFDIR = 0o40000

results = {}
tasks = []

def getEmuTestResult(sock):
	buffer = []
	timeSpent = 0
	while True:
		ready = select.select([sock.fileno()], [], [], 0.25)[0]
		if not ready and ("Passed" in "".join(buffer) or "Failed" in "".join(buffer)):
			return buffer
		if not ready:
			if len([r for r in "".join(buffer).split('\n') if r]) > 1:
				timeSpent += 0.25
				if timeSpent > 10:
					return buffer
			continue
		else:
			timeSpent = 0
		d = sock.recv(8)
		if not d:
			return buffer
		if d[0] == 104:
			buffer.append(chr(d[1]))
			sock.send(bytes([105, 0, 0x80, 0, 0, 0, 0, 0]))


async def executeTest(romPath, port):
	sock = socket.socket()
	sock.bind(("0.0.0.0", port))
	sock.listen()
	process = subprocess.Popen([emuPath, "-n", "-c", "localhost:" + str(port), romPath], 0, emuPath, subprocess.DEVNULL, subprocess.DEVNULL, subprocess.DEVNULL)
	newSock = sock.accept()[0]
	newSock.send(bytes([1, 1, 4, 0, 0, 0, 0, 0]))
	try:
		buffer = getEmuTestResult(newSock)
	except BrokenPipeError:
		buffer = "BrokenPipeError"
	newSock.close()
	sock.close()
	process.terminate()
	old = buffer
	buffer = []
	count = 0
	while count < len(old):
		if count + 1 < len(old) and old[count] == old[count + 1] and (old[count] == ' ' or old[count] == '\n'):
			while count + 1 < len(old) and old[count] == old[count + 1]:
				count += 1
			buffer.append('\n')
		else:
			buffer.append(old[count])
		count += 1
	print(buffer)
	results[romPath.replace("/", "_").replace(" ", "_")] = "".join(buffer)


def executeTestSuite(directory):
	global base_port
	for rom in os.listdir(directory):
		if rom[-3:].lower() == ".gb" or rom[-4:].lower() == ".gbc":
			task = loop.create_task(executeTest(directory + "/" + rom, base_port))
			tasks.append(task)
			base_port += 1


def testEmulator(path):
	expected = "Usage: " + path + " rom.gb [-dn] [-l <port>] [-c <ip:port>]"
	f = os.popen(path, "r")
	if f.read(len(expected)) != expected:
		print(path + ": GBEmulator didn't return the proper help message")
		exit(1)
	f.close()
	print(path + " seems ok")


if len(sys.argv) != 2:
	print("Usage:", sys.argv[0], "<GBEmulator executable>", sep=" ")
	exit(1)


emuPath = sys.argv[1]
testEmulator(emuPath)
loop = asyncio.new_event_loop()
for elem in os.listdir():
	if (os.stat(elem).st_mode & S_IFMT) == S_IFDIR:
		executeTestSuite(elem)


loop.run_forever()
passed = 0
failed = 0
for name, result in results.items():
	if "Passed" in result:
		passed += 1
		print(name + ": \033[32mPassed\033[0m")
	else:
		failed += 1
		print(name + ": \033[31mFailed\033[0m. Rom output:")
		print(result)

print("Total:", passed, "\033[32mPassed\033[0m,", failed, "\033[31mFailed\033[0m")