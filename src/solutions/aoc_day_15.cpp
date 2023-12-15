#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#include "aoc_day_15.h"
#include "file_utils.h"

using namespace std;

AocDay15::AocDay15() : AocDay(15)
{
}

AocDay15::~AocDay15()
{
}

long AocDay15::hash(string input)
{
    /*
    1. Determine the ASCII code for the current character of the string.
    2. Increase the current value by the ASCII code you just determined.
    3. Set the current value to itself multiplied by 17.
    Set the current value to the remainder of dividing itself by 256.
    */

    long hash = 0;
    for (long x = 0; x < input.length(); ++x)
    {
        hash += int(input[x]);
        hash *= 17;
        hash = hash % 256;
    }
    return hash;
}

std::vector<std::string> AocDay15::read_input(std::string filename)
{
    FileUtils fileutils;
    std::vector<std::string> raw_lines;
    std::vector<std::string> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        std::string input = *iter;

        std::istringstream iss(input);
        std::string token;

        while (std::getline(iss, token, ','))
            data.push_back(token);
    }
    return data;
}

string AocDay15::part1(std::string filename, vector<string> extra_args)
{
    cout << hash("qp");

    vector<std::string> data = read_input(filename);
    long sum = 0;
    for (vector<string>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        std::string token = *iter;

        sum += hash(token);
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay15::part2(std::string filename, vector<std::string> extra_args)
{
    // rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7

    vector<std::string> data = read_input(filename);
    long sum = 0;
    map<int, vector<pair<string, int>>> hashmap;
    for (int x = 0; x < 255; ++x)
    {
        hashmap[x] = vector<pair<string, int>>();
    }
    for (vector<string>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        std::string token = *iter;

        char operation;
        int operation_value = 0;
        std::string label;

        if (token[token.length() - 2] == '=')
        {
            label = token.substr(0, token.length() - 2);
            operation = token[token.length() - 2];
            operation_value = (token[token.length() - 1]) - '0';
        }
        else
        {
            label = token.substr(0, token.length() - 1);
            operation = token[token.length() - 1];
        }

        // get the right box, if it exists.
        long box_label_hash = hash(label);
        std::vector<std::pair<std::string, int>> box = hashmap[box_label_hash];

        if (operation == '=')
        {
            // operation is add or change
            // cout << "add " << label << " to box " << box_label_hash << " with value " << operation_value << endl;

            auto found = std::find_if(
                hashmap[box_label_hash].begin(),
                hashmap[box_label_hash].end(),
                [label](const pair<string, int> &element)
                {
                    return element.first == label;
                });
            if (found != hashmap[box_label_hash].end())
            {
                // pair<string, int> f = found;
                // cout << "Found " << label << endl;
                found->second = operation_value;
            }
            else
            {
                hashmap[box_label_hash].push_back(pair<string, int>(label, operation_value));
            }
        }
        else
        {
            // operation is remove
            // cout << "remove " << label << endl;

            hashmap[box_label_hash].erase(
                std::remove_if(
                    hashmap[box_label_hash].begin(),
                    hashmap[box_label_hash].end(),
                    [label](const pair<string, int> &element)
                    {
                        // return true if element should be removed.
                        // cout << " " << element.first << " " << label << " " << (element.first == label) << endl;
                        return (element.first == label);
                    }),
                hashmap[box_label_hash].end());
        }

        sum += hash(token);

        // auto bx = hashmap[0];
        // cout << "Box 0 : ";
        // for (auto i : bx)
        // {
        //     cout << "[" << i.first << " " << i.second << "] ";
        // }
        // cout << endl;

        // bx = hashmap[3];
        // cout << "Box 3 : ";
        // for (auto i : bx)
        // {
        //     cout << "[" << i.first << " " << i.second << "] ";
        // }
        // cout << endl;
    }

    sum = 0;
    for (int x = 0; x < 255; ++x)
    {
        vector<pair<string, int>> box = hashmap[x];
        for (int slot = 0; slot < hashmap[x].size(); ++slot)
        {
            // sum == box * slot * focal
            sum += ((x + 1) * (slot + 1) * (hashmap[x][slot].second));
        }
    }

    ostringstream out;
    out << sum;
    return out.str();
}
