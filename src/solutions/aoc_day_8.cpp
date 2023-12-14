#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_8.h"
#include "file_utils.h"

using namespace std;

AocDay8::AocDay8():AocDay(8)
{
}

AocDay8::~AocDay8()
{
}

LR_data AocDay8::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    LR_data data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    int mode = 0;
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string data_line = *iter;

        if (data_line.empty())
        {
            mode++;
        }
        else
        {
            switch (mode)
            {
            case 0: // reading header line
                data.lr = data_line;
                break;
            case 1: // all other lines
                map<string, pair<string, string>> l;
                string key = data_line.substr(0, 3);
                string left = data_line.substr(data_line.find('(') + 1, 3);
                string right = data_line.substr(data_line.find(", ") + 2, 3);
                data.data[key] = pair<string, string>(left, right);
                cout << key << ": -" << left << "- -" << right << "- " << data.data.size() << endl;
                break;
            }
        }
    }
    return data;
}

string AocDay8::part1(string filename, vector<string> extra_args)
{
    LR_data data = read_input(filename);

    long sum = 0;
    string current_position = "AAA";
    bool found = false;
    long steps = 1;

    while (!found)
    {
        for (int x = 0; x < data.lr.length(); x++)
        {
            pair<string, string> current_node = data.data[current_position];
            cout << "Moving ";
            if (data.lr[x] == 'L')
            {
                cout << "left ";
                current_position = current_node.first;
            }
            else
            {
                cout << "right ";
                current_position = current_node.second;
            }
            cout << "to node " << current_position << endl;
            if (current_position == "ZZZ")
            {
                found = true;
                break;
            }
            steps++;
        }
    }

    // for (LR_data.data::iterator iter = data.begin(); iter != data.end(); ++iter)
    // {
    //     sum+=*iter;
    // }
    ostringstream out;
    out << steps;
    return out.str();
}

string AocDay8::part2(string filename, vector<string> extra_args)
{

    LR_data data = read_input(filename);

    long sum = 0;
    // vector<string> current_positions = FindStartPositins(data.data);
    cout << "Step 0: You are at ";
    vector<string> current_positions;
    for (auto const &[key, value] : data.data)
    {
        if (key[2] == 'A')
        {
            current_positions.push_back(key);
            cout << key << " ";
        }
    }
    cout << "." << endl;

    long found = 0;
    long goal = current_positions.size();

    long steps = 0;

    while (found != goal)
    {
        for (int x = 0; x < data.lr.length(); x++)
        {
            steps++;
            // cout << "Step " << steps << ": You choose all of the " << data.lr[x] << " paths, leading you to ";
            found = 0;
            for (int posIdx = 0; posIdx < current_positions.size(); posIdx++) // current_position : current_positions)
            {
                string current_position = current_positions[posIdx];

                string next_position = "";
                pair<string, string> current_node = data.data[current_position];
                if (data.lr[x] == 'L')
                {
                    next_position = current_node.first;
                }
                else
                {
                    next_position = current_node.second;
                }
                // cout << next_position << " ";
                if (next_position[2] == 'Z')
                {
                    // cout << "* ";
                    found++;
                }
                current_positions[posIdx] = next_position;
            }
            // cout << endl;
            if (found > 1)
                cout << "Step " << steps << ": found " << found << endl;
        }
    }

    // for (LR_data.data::iterator iter = data.begin(); iter != data.end(); ++iter)
    // {
    //     sum+=*iter;
    // }
    ostringstream out;
    out << steps;
    return out.str();
}
