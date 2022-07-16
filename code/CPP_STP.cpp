#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Switch {
public:
    map<int, int> bandwidth_to_cost_table = \
    { {4, 250}, {10, 100}, {16, 62}, {45, 39}, {100, 19}, {155, 14}, \
      {1000, 4}, {10000, 2} };
    
    int ID, Priority, RootID, RootPortTo, RootPriority, Cost;
    map<int, map<string, int>> Path;

    Switch(int ID, int Priority, int RootID, int RootPriority, int Cost) {
        this->ID = ID;
        this->Priority = Priority;
        this->RootID = RootID;
        this->RootPortTo = -1;
        this->RootPriority = RootPriority;
        this->Cost = Cost;
    }

    Switch(int ID, int Priority) {
        this->ID = ID;
        this->Priority = Priority;
        this->RootID = ID;
        this->RootPortTo = -1;
        this->RootPriority = Priority;
        this->Cost = 0;
    }

    bool rootPriorityIsLargerThan(Switch *target) {
        if (this->RootPriority > target->RootPriority)
            return true;
        if (this->RootPriority == target->RootPriority && this->RootID > target->RootID)
            return true;
        return false;
    }

    bool hasSameRootBridge(Switch *target) {
        if (this->RootID == target->RootID)
            return true;
        return false;
    }

    bool distanceIsLargetThan(Switch *target, int bandwidth) {
        return this->Cost > target->Cost + this->bandwidth_to_cost_table[bandwidth];
    }

    bool distanceIsEqualTo(Switch *target, int bandwidth) {
        return this->Cost == target->Cost + this->bandwidth_to_cost_table[bandwidth];
    }

    bool priorityIsLargerThan(Switch *target) {
        if (this->Priority > target->Priority)
            return true;
        if (this->RootPriority == target->RootPriority && this->RootID > target->RootID)
            return true;
        return false;
    }

    void modRoot(Switch *target, int bandwidth) {
        this->RootID = target->RootID;
        this->RootPriority = target->RootPriority;
        this->RootPortTo = target->ID;
        this->Cost = target->Cost + this->bandwidth_to_cost_table[bandwidth];
    }

    string getInfo() {
        string s = "==========";
        s += "\nID:" + to_string(this->ID);
        s += "\nPriority:" + to_string(this->Priority);
        s += "\nRootID:" + to_string(this->RootID);
        s += "\nRootPriority:" + to_string(this->RootPriority);
        s += "\nRootPortTo:" + to_string(this->RootPortTo);
        s += "\nCost:" + to_string(this->Cost);
        s += "\n==========";
        return s;
    }
};

int main() {
    ifstream infile;
    ofstream outfile;
    infile.open("STP_in_1.txt", ios::in);
    outfile.open("STP_out_1.txt", ios::out);
    int myID, myPriority, n;

    infile >> myID >> myPriority >> n;
    Switch mainSwitch(myID, myPriority);

    outfile << "Hello\n";
    while (n--) {
        int otherID, otherPriority, otherRoot, otherRootPriority, otherCost, bandwidth;
        infile >> otherID >> otherPriority >> otherRoot >> otherRootPriority\
               >> otherCost >> bandwidth;
        
        Switch newSwitch(otherID, otherPriority, otherRoot, otherRootPriority, otherCost);
        
        bool needUpdate = false;
        if (mainSwitch.hasSameRootBridge(&newSwitch)) {
            if (mainSwitch.distanceIsLargetThan(&newSwitch, bandwidth))
                needUpdate = true;
            else if (mainSwitch.distanceIsEqualTo(&newSwitch, bandwidth) && mainSwitch.priorityIsLargerThan(&newSwitch))
                needUpdate = true;
        }
        else if (mainSwitch.rootPriorityIsLargerThan(&newSwitch)) {
            needUpdate = true;
        }

        if (needUpdate) {
            mainSwitch.modRoot(&newSwitch, bandwidth);
            outfile << "NewCost:" << mainSwitch.Cost << ", Hello\n";
        }
        else {
            outfile << "Ignore\n";
        }
    }
    outfile << mainSwitch.getInfo();
    return 0;
}