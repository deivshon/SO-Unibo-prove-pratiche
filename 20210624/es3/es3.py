import sys
import os
import subprocess

def isSourceFile(path):
    return path[path.rfind("."):len(path)] == ".c"

if len(sys.argv) < 2:
    d = "." 
elif not os.path.isdir(sys.argv[1]):
    sys.exit("Provide a valid directory")
else:
    d = sys.argv[1]


entries = os.listdir(d)
for name in entries:
    currentName = d + "/" + name
    if isSourceFile(currentName):
        subprocess.run(["indent", "-o", currentName, currentName])
