import sys
import os

def getMaxMinTime(d, currentMin = None, currentMax = None, currentMinPath = None, currentMaxPath = None):
    localMin, localMax = currentMin, currentMax
    localMinPath, localMaxPath = currentMinPath, currentMaxPath
    dirList = os.listdir(d)
    for entry in dirList:
        currentPath = d + "/" + entry
        if os.path.isfile(currentPath):
            mtime = os.path.getmtime(currentPath)
            if localMin == None:
                localMin = mtime
                localMinPath = currentPath
            if localMax == None:
                localMax = mtime
                localMaxPath = currentPath
            if mtime < localMin:
                localMin = mtime
                localMinPath = currentPath
            if mtime > localMax:
                localMax = mtime
                localMaxPath = currentPath
        elif os.path.isdir(currentPath) and not os.path.islink(currentPath):
            localMin, localMax, localMinPath, localMaxPath = getMaxMinTime(currentPath, localMin, localMax, localMinPath, localMaxPath)
    return localMin, localMax, localMinPath, localMaxPath

if len(sys.argv) < 2 or not os.path.isdir(sys.argv[1]):
    sys.exit("Provide a directory")

minTime, maxTime, minPath, maxPath = getMaxMinTime(sys.argv[1])
print("Min:", minPath, "->", minTime)
print("Max:", maxPath, "->", maxTime)
