#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_5.h"
#include "file_utils.h"

using namespace std;

AocDay5::AocDay5() : AocDay(5)
{
}

AocDay5::~AocDay5()
{
}

template <typename T>
std::vector<T> AocDay5::splitString(const std::string &input)
{
    std::vector<T> result;
    std::istringstream iss(input);
    T number;

    while (iss >> number)
    {
        result.push_back(number);
    }

    return result;
}

Alminac AocDay5::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    Alminac alminac;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return alminac;
    }
    int index = 0;
    int mode = 0;
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string line = *iter;
        cout << "line: " << line << endl;

        switch (mode)
        {
        case 0: // starting with seeds
            // skip 7 chars and read the rest
            alminac.seeds = splitString<long>(line.substr(7));
            mode++;
            break;
        }

        // long l;
        // string to_convert = *iter;
        // l = strtol(to_convert.c_str(), NULL, 10);
        // data.push_back(l);
    }
    return alminac;
}

string AocDay5::part1(string filename, vector<string> extra_args)
{
    Alminac data = read_input(filename);
    long sum = 0;

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay5::part2(string filename, vector<string> extra_args)
{
    long sum = 0;

    ostringstream out;
    out << sum;
    return out.str();
}
