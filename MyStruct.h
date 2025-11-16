#pragma once
#include <string>
#include <array>
#include <mutex>
#include <shared_mutex>

using namespace std;

const int M_FIELDS = 3;

class MyStruct
{
private:
    array<int, M_FIELDS> data;
    mutable array<shared_mutex, M_FIELDS> m;

public:
    MyStruct();

    void set(int index, int value);
    int get(int index);
    string to_string() const;
    operator string() const
    {
        return to_string();
    }

};