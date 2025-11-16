#include "MyStruct.h"
#include <sstream>

MyStruct::MyStruct()
{
    data.fill(0);
}
void MyStruct::set(int index, int value)
{
    if (index < 0 || index >= M_FIELDS) return;
    lock_guard<shared_mutex> lock(m[index]);
    data[index] = value;
}

int MyStruct::get(int index)
{
    if (index < 0 || index >= M_FIELDS) return -1;
    shared_lock<shared_mutex> lock(m[index]);
    return data[index];
}

string MyStruct::to_string() const
{
    shared_lock<shared_mutex> lock0(m[0], defer_lock);
    shared_lock<shared_mutex> lock1(m[1], defer_lock);
    shared_lock<shared_mutex> lock2(m[2], defer_lock);
    lock(lock0, lock1, lock2);
    stringstream ss;
    ss << "[";
    ss << data[0] << ", " << data[1] << ", " << data[2];
    ss << "]";
    return ss.str();
}