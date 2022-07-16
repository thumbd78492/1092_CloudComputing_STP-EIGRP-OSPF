import random

switchCount = 1250
connectedSwitchCount = 25
ID_range = (1, 65535)

IDList = random.sample([i for i in range(ID_range[0], ID_range[1])], k=switchCount)
random.shuffle(IDList)

length = {}

f = open("EIGRP_in_5.txt", "w")
f.write(str(IDList[0]))
f.write("\n" + str(connectedSwitchCount))
for i in range(1, connectedSwitchCount+1):
    l = random.randint(1, 12) * 25
    length[IDList[i]] = l
    f.write("\n" + str(IDList[i]) + " " + str(l))
    
f.write("\n" + str(connectedSwitchCount))
for i in range(1, connectedSwitchCount+1):
    f.write("\n" + str(IDList[i]))
    m = random.randint(0, switchCount-1)
    newSwitchConnected = random.sample(IDList[1:], m)
    for j in range(len(newSwitchConnected)):
        if newSwitchConnected[j] == IDList[i]:
            newSwitchConnected.pop(j)
            m -= 1
            break
    newSwitchConnected.append(IDList[0])
    m += 1
    f.write("\n" + str(m))
    for sw in newSwitchConnected:
        if sw == IDList[0]:
            f.write("\n" + str(sw) + " " + str(length[IDList[i]]))
        else:
            f.write("\n" + str(sw) + " " + str(random.randint(1, 16) * 25))

f.close()