#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_1.h"
#include "file_utils.h"

using namespace std;

AocDay1::AocDay1() : AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

vector<string> AocDay1::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<string> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    return raw_lines;
}

string AocDay1::part1(string filename, vector<string> extra_args)
{
    vector<string> raw_data = read_input(filename);
    vector<long> data;
    for (vector<string>::iterator iter = raw_data.begin(); iter != raw_data.end(); ++iter)
    {
        long l;
        string to_convert = *iter;
        string numbers = "";

        for (char c : to_convert)
        {
            if (isdigit(c))
            {
                numbers += c;
            }
        }

        string thenumber = numbers.substr(0, 1) + numbers.substr(numbers.length() - 1, 1);
        l = strtol(thenumber.c_str(), NULL, 10);

        // cout << numbers << " " << thenumber << endl;
        data.push_back(l);
    }

    long sum = 0;
    for (vector<long>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        cout << *iter;
        sum += *iter;
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay1::part2(string filename, vector<string> extra_args)
{
    map<string, long> key_map;
    key_map = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
        {"0", 0},
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},
    };

    vector<string> raw_data = read_input(filename);
    vector<long> data;

    for (vector<string>::iterator iter = raw_data.begin(); iter != raw_data.end(); ++iter)
    {
        long l;
        string to_convert = *iter;
        string numbers = "";

        long lowest = to_convert.length();
        double highest_pos = -1;
        long lowest_value, highest_value = 0;
        for (auto const &keyvals : key_map)
        {
            size_t found = to_convert.find(keyvals.first);
            if (found != std::string::npos && found < lowest)
            {
                lowest = found;
                lowest_value = keyvals.second;
            }

            size_t rfound = to_convert.rfind(keyvals.first);
            if ((rfound != std::string::npos) && (rfound > highest_pos))
            {
                highest_pos = rfound;
                highest_value = keyvals.second;
            }
        }

        l = (lowest_value * 10) + highest_value;
        cout << "found " << l << " for: " << to_convert << endl;
        data.push_back(l);
    }

    long sum = 0;
    for (vector<long>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum += *iter;
    }
    ostringstream out;
    out << sum;
    return out.str();
}
