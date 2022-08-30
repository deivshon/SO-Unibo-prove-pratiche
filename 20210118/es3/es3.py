import sys
import os

def getPatternList(directory, pattern):
    results = []

    entries = os.listdir(directory)
    for file in entries:
        realFilePath = directory + "/" + file
        if os.path.isfile(realFilePath) and pattern in file:
            results.append((os.path.abspath(realFilePath), os.path.getmtime(realFilePath)))

    return results            

if len(sys.argv) < 2:
    sys.exit("Provide a pattern!")
elif len(sys.argv) == 2:
    pattern = sys.argv[1]
    path = "."
elif len(sys.argv) > 2:
    pattern = sys.argv[1]
    path = sys.argv[2]
    if not os.path.isdir(path): sys.exit("Provide a valid directory")

matchingFiles = getPatternList(path, pattern)
matchingFiles = sorted(matchingFiles, key = lambda e: e[1], reverse = True)

for f in matchingFiles:
    print("{:<18}".format(f[1]), f[0])
