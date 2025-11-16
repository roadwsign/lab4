#include "Executor.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Executor::execute_line(MyStruct& myStruct, const string& line) {
    istringstream ss(line);
    string cmd;
    ss >> cmd;

    if (cmd == "write") {
        int index, value;
        ss >> index >> value;
        myStruct.set(index, value);
    }
    else if (cmd == "read") {
        int index;
        ss >> index;
        int val = myStruct.get(index);
    }
    else if (cmd == "string") {
        string s = myStruct.to_string();
    }
}