import os
import sys
import subprocess

def elfSizeSum(directory):
	result = 0
	dirEntries = os.listdir(directory)
	for entry in dirEntries:
		currentEntry = directory + "/" + entry

		if(not os.path.isfile(currentEntry)): continue
		f = subprocess.run(["file", currentEntry], capture_output = True)
		fileCommandOutput = f.stdout.decode()
		if("ELF" in fileCommandOutput):
			result += os.path.getsize(currentEntry)

	return result

dirs = []

if len(sys.argv) < 2:
	dirs.append(".")
else:
	for i in range(1, len(sys.argv)):
		if(os.path.isdir(sys.argv[i]) and sys.argv[i] not in dirs):
			dirs.append(sys.argv[i])

result = 0
for d in dirs:
	result += elfSizeSum(d)

print(result)

