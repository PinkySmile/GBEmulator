import os
import sys
from asyncio import subprocess
from typing import Tuple, List
import asyncio


base_port = 15800

async def getEmuTestResult(reader: asyncio.StreamReader, writer: asyncio.StreamWriter) -> bytearray:
	buffer = bytearray()
	timeSpent = 0
	timeSpent2 = 0
	while True:
		try:
			b = await asyncio.wait_for(reader.readexactly(8), 0.25)
			timeSpent = 0
			timeSpent2 = 0
		except asyncio.exceptions.TimeoutError:
			if b"Passed" in buffer or b"Failed" in buffer:
				return buffer
			timeSpent2 += 0.25
			if buffer.count(10) > 2:
				timeSpent += 0.25
				if timeSpent > 10:
					print("Time !", buffer.count(10))
					return buffer
			if timeSpent2 >= 40:
				buffer += b"\nTimed out after 10 seconds\n"
				return buffer
			continue
		if not b:
			return buffer
		if b[0] == 104:
			buffer.append(b[1])
			writer.write(bytes([105, 0, 0x80, 0, 0, 0, 0, 0]))
			await writer.drain()


async def executeTest(emuPath: str, romPath: str, port: int) -> Tuple[str, str]:
	args = ["--no-error", "--no-bootrom", "--no-display", "--no-audio", "--max-speed", "--listen", str(port), romPath]
	#args = ["-nrabml", str(port), romPath]
	print(f"Running {romPath} in {emuPath} on port {port}")
	process = await subprocess.create_subprocess_exec(emuPath, *args)
	try:
		reader, writer = await asyncio.wait_for(asyncio.open_connection(host="localhost", port=port), 3)
	except asyncio.TimeoutError as e:
		print("Cannot connect to emulator......", e)
		return romPath.replace("/", "_").replace(" ", "_"), "Cannot connect to emulator\n"
	writer.write(bytes([1, 1, 4, 0, 0, 0, 0, 0]))
	await writer.drain()

	buffer = await getEmuTestResult(reader, writer)
	process.terminate()
	old = buffer.decode("ASCII")
	result = []
	count = 0
	while count < len(old):
		if count + 1 < len(old) and old[count] == old[count + 1] and (old[count] == ' ' or old[count] == '\n'):
			while count + 1 < len(old) and old[count] == old[count + 1]:
				count += 1
			result.append('\n')
		else:
			result.append(old[count])
		count += 1
	print(f"Finished {romPath}")
	return romPath.replace("/", "_").replace(" ", "_"), "".join(result)


async def executeTestSuite(emuPath: str, directory: str, port: int) -> Tuple[int, List[Tuple[str, str]]]:
	longest = 0
	tasks = []
	for i, rom in enumerate(sorted(os.listdir(directory))):
		if rom.lower().endswith(".gb") or rom.lower().endswith(".gbc"):
			longest = max(longest, len(directory + "/" + rom))
			tasks.append(executeTest(emuPath, directory + "/" + rom, port + i))
	return longest, dict(await asyncio.gather(*tasks))


async def testEmulator(path: str) -> None:
	expected = bytes("Usage: " + path + " rom.gb [-dnrmba] [-l <port>] [-c <ip:port>] [-g auto|dmg|gbc]", "ASCII")
	process = await asyncio.create_subprocess_exec(path, "--help", stdout=subprocess.PIPE)
	if (read := await process.stdout.read(len(expected))) != expected:
		print(path + ": GBEmulator didn't return the proper help message")
		print(read)
		exit(1)
	try:
		await asyncio.wait_for(process.wait(), 1)
	except asyncio.TimeoutError as e:
		print(e)
		exit(1)
	print(path + " seems ok")


async def main():
	longestName = 0

	if len(sys.argv) != 2:
		print("Usage:", sys.argv[0], "<GBEmulator executable>")
		exit(1)

	emuPath = sys.argv[1]
	await testEmulator(emuPath)

	tasks = [executeTestSuite(emuPath, suite, base_port + i * 100) for i, suite in enumerate(sorted(os.listdir("."))) if os.path.isdir(suite)]
	results = await asyncio.gather(*tasks)

	result = {}
	for length, r in results:
		longestName = max(longestName, length)
		result.update(r)

	passed = 0
	failed = 0
	for name, result in sorted(result.items(), key=lambda a: a[0]):
		if "Passed" in result:
			passed += 1
			print(f"{{:<{longestName}}}: \033[32mPassed\033[0m".format(name))
		else:
			failed += 1
			print(f"{{:<{longestName}}}: \033[31mFailed\033[0m. Rom output:".format(name))
			print(result)
	print("Total:", passed, "\033[32mPassed\033[0m,", failed, "\033[31mFailed\033[0m")

asyncio.run(main())
