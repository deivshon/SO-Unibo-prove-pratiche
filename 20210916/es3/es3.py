import os
import sys


def listFilesRec(dir, files = {}):
    dirlist = os.listdir(dir)
    for entry in dirlist:
        realEntry = dir + "/" + entry
        if os.path.isfile(realEntry):
            if entry not in files.keys():
                files[entry] = [dir]
            elif dir not in files[entry]:
                files[entry].append(dir)
        elif os.path.isdir(realEntry):
            files = listFilesRec(dir + "/" + entry, files)
    return files

if len(sys.argv) < 2 or not os.path.isdir(sys.argv[1]):
    sys.exit("Provide a valid directory path")

directory = sys.argv[1]
if directory[len(directory) - 1] == "/" and directory != "/":
    directory = directory[0:len(directory) - 1]

result = listFilesRec(directory)

files = sorted(result.keys())
for entry in files:
    print(entry + ": ", end = "")
    for d in result[entry]:
        print(d, end = " ")
    print()
