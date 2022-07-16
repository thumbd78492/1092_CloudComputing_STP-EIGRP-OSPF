#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

class Switch {
public:
    int ID;
    map<int, map<string, int>> Path;

    Switch(int ID) {
        this->ID = ID;
    }

    void addPath(int targetID, int nextHop, int cost) {
        map<string, int> tmp;
        tmp["nextHop"] = nextHop;
        tmp["cost"] = cost;
        this->Path[targetID] = tmp;
    }

    string getInfo() {
        string s = "Switch ID:" + to_string(this->ID);
        s += "\npaths:";
        map<int, map<string, int>>::iterator iter;

        for (iter = this->Path.begin(); iter != this->Path.end(); iter++)
            s += "\nID:" + to_string(iter->first) +\
                 ", next hop:" + to_string(iter->second["nextHop"]) +\
                 ", cost:" + to_string(iter->second["cost"]);
        return s;
    }
};

int main() {
    ifstream infile;
    ofstream outfile;
    infile.open("EIGRP_in_5.txt", ios::in);
    outfile.open("EIGRP_out_5.txt", ios::out);
    int myID, n;

    infile >> myID >> n;
    Switch mainSwitch(myID);
    mainSwitch.addPath(myID, myID, 0);
    while (n--) {
        int target, cost;
        infile >> target >> cost;
        mainSwitch.addPath(target, target, cost);
    }
    outfile << "Hello\n";

    int m;
    infile >> m;
    while (m--) {
        int recv_from_ID, s;
        infile >> recv_from_ID >> s;
        unordered_set<int> targetDestinations;
        bool needUpdate = false, needHello = false;

        while (s--) {
            int destinationID, distance;
            infile >> destinationID >> distance;
            distance += mainSwitch.Path[recv_from_ID]["cost"];
            if (mainSwitch.Path.find(destinationID) == mainSwitch.Path.end()) {
                mainSwitch.addPath(destinationID, recv_from_ID, distance);
                needHello = true;
            }
            else if (mainSwitch.Path[destinationID]["cost"] > distance) {
                mainSwitch.Path[destinationID]["nextHop"] = recv_from_ID;
                mainSwitch.Path[destinationID]["cost"] = distance;
                needHello = true;
            }
            else if (mainSwitch.Path[destinationID]["cost"] <= distance) {
                ;
            }
            else {
                needUpdate = true;
            }
        }

        map<int, map<string, int>>::iterator iter;
        for (iter = mainSwitch.Path.begin(); iter != mainSwitch.Path.end(); iter++) {
            int myDest = iter->first;
            if (targetDestinations.find(myDest) == targetDestinations.end()) {
                needUpdate = true;
            }
        }
        
        if (needUpdate && needHello)
            outfile << "Update Hello\n";
        else if (needUpdate)
            outfile << "Update\n";
        else if (needHello)
            outfile << "Hello\n";
        else
            outfile << "Ignore\n";
    }
    outfile << mainSwitch.getInfo();
    return 0;
}