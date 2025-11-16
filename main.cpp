#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <thread>
#include <functional>
#include <fstream>

#include "Executor.h"
#include "MyStruct.h"
#include "Timer.h"

vector<string> load_file(const string& filename)
{
    vector<string> commands;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << format("ERROR: Could not open file {}.\n", filename);
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        commands.push_back(line);
    }
    return commands;
}

void process_commands(MyStruct& data, const vector<string>& commands)
{
    for (const auto& line : commands) {
        Executor::execute_line(data, line);
    }
}

double run_test(int num_threads, const vector<vector<string>>& all_command_vectors)
{
    MyStruct data;
    vector<thread> threads;
    Timer timer;

    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(process_commands, ref(data), cref(all_command_vectors[i]));
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return timer.elapsed_ms();
}

void run_specific_test(const string& test_name, const string& file_prefix)
{
    cout << format("\nRunning {}\n", test_name);

    string f1 = "file_" + file_prefix + "_1.txt";
    string f2 = "file_" + file_prefix + "_2.txt";
    string f3 = "file_" + file_prefix + "_3.txt";

    auto commands1 = load_file(f1);
    auto commands2 = load_file(f2);
    auto commands3 = load_file(f3);

    cout << "Running 1-thread test\n";
    double t1 = run_test(1, { commands1 });
    cout << format("1 Thread:  {:.2f} ms\n", t1);

    cout << "Running 2-thread test\n";
    double t2 = run_test(2, { commands1, commands2 });
    cout << format("2 Threads: {:.2f} ms\n", t2);

    cout << "Running 3-thread test\n";
    double t3 = run_test(3, { commands1, commands2, commands3 });
    cout << format("3 Threads: {:.2f} ms\n", t3);
}

int main()
{
    int choice;
    cout << "1: Run Test A (Variant)\n" << "2: Run Test B (Equal)\n" << "3: Run Test C (Custom)\n" << "Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        run_specific_test("Test A (Variant)", "a");
        break;
    case 2:
        run_specific_test("Test B (Equal)", "b");
        break;
    case 3:
        run_specific_test("Test C (Custom)", "c");
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
    return 0;
}