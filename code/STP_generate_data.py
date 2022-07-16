import random

class Switch:
    def __init__(self, ID):
        self.ID = ID
        self.priority = 4096 * random.randint(1, 8)
    
    def setRoot(self, target):
        self.rootID = target.ID
        self.RootPriority = target.priority
        if self.rootID == self.ID:
            self.Cost = 0
        else:
            self.Cost = random.sample([250, 100, 62, 39, 19, 14, 4, 2], k=1)[0]

    def __lt__(self, other):
        if self.priority > other.priority:
            return True
        if self.priority == other.priority and self.ID > other.ID:
            return True
        return False

switchCount = 1001
ID_range = (1, 65535)

IDList = random.sample([i for i in range(ID_range[0], ID_range[1])], k=switchCount)
switches = []
for ID in IDList:
    switches.append(Switch(ID))
switches.sort()

mySwitchIdx = random.randint(0, switchCount-1)
mySwitchID = switches[mySwitchIdx].ID
for idx in range(len(switches)):
    if idx == mySwitchIdx:
        continue
    else:
        tg = random.randint(idx, switchCount-1)
        while tg == mySwitchIdx:
            tg = random.randint(idx, switchCount-1)
        switches[idx].setRoot(switches[tg])

# for sw in switches:
#     if sw.ID != mySwitchID:
#         print(sw.ID, sw.priority, sw.rootID, sw.RootPriority, sw.Cost)
#     else:
#         print(sw.ID, sw.priority, sw.ID, sw.priority, 0)

f = open("STP_in_4.txt", "w")
f.write(str(mySwitchID))
f.write("\n" + str(switches[mySwitchIdx].priority))
f.write("\n" + str(switchCount - 1))

random.shuffle(switches)
for sw in switches:
    if sw.ID == mySwitchID:
        continue
    else:
        s = "\n" + str(sw.ID)
        s += "\n" + str(sw.priority)
        s += "\n" + str(sw.rootID)
        s += "\n" + str(sw.RootPriority)
        s += "\n" + str(sw.Cost)
        s += "\n" + str(random.sample([4, 10, 16, 45, 100, 155, 1000, 10000], k=1)[0])
        f.write(s)
f.close()