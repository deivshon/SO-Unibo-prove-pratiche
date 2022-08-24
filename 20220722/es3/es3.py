import sys
import os
import subprocess

def isExecutable(filepath):
    return os.path.isfile(filepath) and os.access(filepath, os.X_OK)

def notElf(filepath):
    if not os.path.isfile(filepath): return True

    fileOut = subprocess.run(["file", filepath], capture_output = True)
    return "ELF" not in fileOut.stdout.decode()

if len(sys.argv) < 2:
    path = "."
else:
    if os.path.isdir(sys.argv[1]): path = sys.argv[1]
    else: sys.exit("Invalid path!")

scripts = list(filter(lambda x: isExecutable(x) and notElf(x), map(lambda x: "./" + path + "/" + x, os.listdir(path))))

for s in scripts:
    subprocess.run([s])
