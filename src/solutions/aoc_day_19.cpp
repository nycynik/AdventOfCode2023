#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <cstdlib>

#include "aoc_day_19.h"
#include "file_utils.h"

using namespace std;

AocDay19::AocDay19() : AocDay(19)
{
}

AocDay19::~AocDay19()
{
}

map<string, string> AocDay19::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    map<string, string> rules;
    vector<string> items;

    int mode = 0;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return rules;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string line = *iter;
        if (line.length() == 0)
        {
            mode++;
            continue;
        }
        if (mode == 0)
        {
            string key = line.substr(0, line.find('{'));
            string val = line.substr(line.find('{') + 1, line.length() - key.length() - 2);
            rules[key] = val;
            cout << key << "=" << val << endl;
        }
        else
        {
            items.push_back(line.substr(1, line.length() - 1));
            cout << "item " << line.substr(1, line.length() - 2) << endl;
        }
    }
    return rules;
}

string AocDay19::part1(string filename, vector<string> extra_args)
{
    map<string, string> data = read_input(filename);
    long sum = 0;

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay19::part2(string filename, vector<string> extra_args)
{
    long sum = 0;

    ostringstream out;
    out << sum;
    return out.str();
}
