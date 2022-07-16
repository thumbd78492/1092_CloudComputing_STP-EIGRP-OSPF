import random

switchCount = 250
ID_range = (1, 65535)

def generateRandomConnectedGraph(V):
    initialSet = set()
    visitedSet = set()
    vertices = set()
    edges = dict()
    #generate the set of names for the vertices
    for i in range(V):
        initialSet.add(i)
        vertices.add(i)
    #set the intial vertex to be connected
    curVertex = random.sample(initialSet, 1).pop()
    initialSet.remove(curVertex)
    visitedSet.add(curVertex)
    #loop through all the vertices, connecting them randomly
    while initialSet:
        adjVertex = random.sample(initialSet, 1).pop()
        length = random.randint(1,12) * 25
        
        if not curVertex in edges:
            edges[curVertex] = {}
        edges[curVertex][adjVertex] = length
        if not adjVertex in edges:
            edges[adjVertex] = {}
        edges[adjVertex][curVertex] = length

        initialSet.remove(adjVertex)
        visitedSet.add(adjVertex)
        curVertex = adjVertex
    return vertices, edges

def generateCombination(n):
    com = []
    for i in range(n):
        for j in range(i+1, n):
            com.append([i,j])
            # com.append([j,i])
    return com

IDList = random.sample([i for i in range(ID_range[0], ID_range[1])], k=switchCount)
v, e = generateRandomConnectedGraph(switchCount)

# print(v)
# print(e)

com = generateCombination(switchCount)
newEdges = random.sample(com, k = random.randint(1, len(com)))
for edge in newEdges:
    a, b = edge[0], edge[1]
    if a in e and b in e[a]:
        continue
    else:
        length = random.randint(1,12) * 25
        if not a in e:
            e[a] = {}
        e[a][b] = length
        if not b in e:
            e[b] = {}
        e[b][a] = length

# print(v)
# print(e)

f = open("OSPF_in_5.txt", "w")
f.write(str(len(v)) + "\n")
for a in e:
    f.write(str(IDList[a]) + "\n")
    f.write(str(len(e[a])) + "\n")
    for b in e[a]:
        f.write(str(IDList[b]) + " " + str(e[a][b]) + "\n")
f.write(str(random.choice(IDList)))