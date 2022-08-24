import sys
import os
import subprocess

def pairFileOutput(path):
    fileCommand = subprocess.run(["file", "-b", path], capture_output = True)
    if fileCommand.stdout == None:
        print("Error executing the file command")
        return path
    return (path, fileCommand.stdout.decode().split(",")[0].strip())

def getLastPathName(path):
    return path[::-1][0:path[::-1].index("/")][::-1]

if len(sys.argv) < 2:
    sys.exit("No directory provided")

directory = sys.argv[1]
if not os.path.isdir(directory):
    sys.exit("Directory provided is invalid")
if directory[len(directory) - 1] != "/":
    directory += "/"

fileList = list(map(lambda name: directory + name, os.listdir(directory)))

pairs = list(map(lambda file: pairFileOutput(file), fileList))

pairs = sorted(pairs, key = lambda entry: entry[1])

result = {}

for entry in pairs:
    if(entry[1] not in result):
        result[entry[1]] = [entry[0]]
    else:
        result[entry[1]] += [entry[0]]

for type in result.keys():
    print(type + ": ", end = "")
    for f in result[type]:
        print(getLastPathName(f), end = " ")
    print()
