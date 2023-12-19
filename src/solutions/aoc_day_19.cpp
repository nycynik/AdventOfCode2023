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

std::vector<std::string>
AocDay19::split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

std::string AocDay19::play_rule(map<string, long> item, string rule)
{
    // cout << "playing " << rule << endl;
    string next = "";
    vector<string> ruleParts = split(rule, ',');

    for (auto rulePart : ruleParts)
    {
        string ruleKey = rulePart.substr(0, 1);

        if (rulePart.find(':') != string::npos)
        {
            // if then
            if (item.count(ruleKey) > 0)
            {
                // test rule, it matches!
                long ruleValue = atol(rulePart.substr(2).c_str());
                string followRule = rulePart.substr(rulePart.find(":") + 1);
                // string ruleFollow =
                bool shouldFollow = false;
                if (rulePart[1] == '>')
                {
                    shouldFollow = item[ruleKey] > ruleValue;
                }
                else if (rulePart[1] == '<')
                {
                    shouldFollow = item[ruleKey] < ruleValue;
                }
                // cout << "testing " << item[ruleKey] << rulePart[1] << ruleValue << " " << followRule << " should " << shouldFollow << endl;
                if (shouldFollow)
                    return (followRule);
            }
        }
        else
        {
            // no then, just go
            // cout << "going to " << rulePart << endl
            //      << endl;
            return (rulePart);
        }
    }

    return next;
}

Day19Data AocDay19::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    Day19Data data;
    vector<string> items;

    int mode = 0;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
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
            data.rules[key] = val;
            // cout << key << "=" << val << endl;
        }
        else
        {
            string thisItem = line.substr(1, line.length() - 2);
            // cout << "item " << thisItem << endl;

            vector<string> itemParts = split(thisItem, ',');
            map<string, long> attribs;
            for (auto i : itemParts)
            {
                attribs[i.substr(0, 1)] = atol(i.substr(2).c_str());
                // cout << i.substr(0, 1) << ": " << atol(i.substr(2).c_str()) << endl;
            }
            data.itemAttributes.push_back(attribs);
        }
    }

    return data;
}

string AocDay19::part1(string filename, vector<string> extra_args)
{
    Day19Data data = read_input(filename);
    long sum = 0;

    for (long itemIndex = 0; itemIndex < data.itemAttributes.size(); ++itemIndex)
    {
        string following_rule = "in";
        while (following_rule != "R" && following_rule != "A")
        {
            // cout << "item" << itemIndex << ": next rule " << following_rule << endl;
            following_rule = play_rule(data.itemAttributes[itemIndex], data.rules[following_rule]);
        }

        if (following_rule == "R")
        {
            // item rejected
        }
        if (following_rule == "A")
        {
            // accepted sum up item
            for (auto i : data.itemAttributes[itemIndex])
            {
                sum += i.second;
            }
        }
    }

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay19::part2(string filename, vector<string> extra_args)
{
    Day19Data data = read_input(filename);
    long sum = 0;

    vector<map<string, long>> itemsToTest;

    for (long x = 1; x < 4001; x++)
    {
        cout << x << " " << sum << endl;
        for (long m = 1; m < 4001; m++)
            for (long a = 1; a < 4001; a++)
                for (long s = 1; s < 4001; s++)
                {
                    string following_rule = "in";
                    map<string, long> itemToTest = {{"x", x}, {"m", m}, {"a", a}, {"s", s}};

                    while (following_rule != "R" && following_rule != "A")
                    {
                        // cout << "item" << itemIndex << ": next rule " << following_rule << endl;
                        following_rule = play_rule(itemToTest, data.rules[following_rule]);
                    }

                    if (following_rule == "R")
                    {
                        // item rejected
                    }
                    if (following_rule == "A")
                    {
                        // accepted sum up item
                        sum += 1;
                    }
                }
    }

    ostringstream out;
    out << sum;
    return out.str();
}
