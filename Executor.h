#pragma once
#include <string>
#include "MyStruct.h"

class Executor {
public:
    static void execute_line(MyStruct& myStruct, const string& line);
};