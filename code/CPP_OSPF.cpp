#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main() {
    ifstream infile;
    ofstream outfile;
    infile.open("OSPF_in_5.txt", ios::in);
    outfile.open("OSPF_out_5.txt", ios::out);

    unordered_map<int, unordered_map<int, int>> edges;
    int n;
    infile >> n;

    for (int i=0; i<n; i++) {
        int ID, m;
        infile >> ID >> m;
        unordered_map<int, int> ID_edge;
        while (m--) {
            int target, cost;
            infile >> target >> cost;
            ID_edge[target] = cost;
        }
        edges[ID] = ID_edge;        
    }

    int targetSwitch;
    infile >> targetSwitch;

    map<int, int> dis;
    unordered_map<int, int> nextHop;
    unordered_set<int> visited, connected;
    dis[targetSwitch] = 0;
    nextHop[targetSwitch] = targetSwitch;
    visited.insert(targetSwitch);
    connected.insert(targetSwitch);

    unordered_map<int, int>::iterator iter;
    for (iter = edges[targetSwitch].begin(); iter != edges[targetSwitch].end(); iter++) {
        int ID = iter->first;
        dis[ID] = edges[targetSwitch][ID];
        nextHop[ID] = ID;
        connected.insert(ID);
    }
    
    for (int i=1; i<n; i++) {
        int minDis = INT_MAX, u = -1;
        map<int, int>::iterator dis_iter;
        for (dis_iter = dis.begin(); dis_iter != dis.end(); dis_iter++) {
            int j = dis_iter->first;
            if (visited.find(j) == visited.end() && dis[j] < minDis) {
                minDis = dis_iter->second;
                u = j;
            }
        }
        // cout << "nowFind" << u << endl;
        if (u == -1)
            break;
        visited.insert(u);

        for (iter = edges[u].begin(); iter != edges[u].end(); iter++) {
            int v = iter->first;
            if ((dis.find(v) != dis.end() && dis[v] > dis[u] + edges[u][v]) ||\
                dis.find(v) == dis.end()) {
                dis[v] = dis[u] + edges[u][v];
                nextHop[v] = u;
            }
        }
    }

    for (map<int, int>::iterator dis_iter = dis.begin(); dis_iter != dis.end(); dis_iter++) {
        int ID = dis_iter->first;
        int NH = nextHop[ID];
        while (NH != nextHop[NH]) {
            NH = nextHop[NH];
        }
        outfile << "ID:" << ID << ", next hop:" << NH << ", cost:" << dis[ID] << endl;
    }

    return 0;
}