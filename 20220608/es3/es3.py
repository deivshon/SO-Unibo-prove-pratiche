import os

NAME = 0
VMSIZE = 1

procs = os.listdir("/proc/")
uid = str(os.getuid())

for p in procs:
    statusName = "/proc/" + p + "/status"
    uidFile = "/proc/" + p + "/loginuid"
    if(not os.path.isfile(statusName)): continue
    if(not os.path.isfile(uidFile)): continue
    with open(uidFile, "r") as f:
        pUid = f.read().strip()
    
    if pUid != uid: continue

    with open(statusName, "r") as f:
        currentData = list(filter(lambda s: "VmSize" in s or "Name" in s, f.read().splitlines()))
    print("{:<32}".format(currentData[NAME].split("\t")[1]), end = "")
    print(currentData[VMSIZE].split("\t")[1].replace(" ", ""))
