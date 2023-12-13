#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#include "aoc_day_7.h"
#include "file_utils.h"

using namespace std;

AocDay7::AocDay7() : AocDay(7)
{
}

AocDay7::~AocDay7()
{
}

long AocDay7::rank_hand(Hand h)
{
    // count matches
    long ret = 1;
    map<char, long> handValue;
    for (int x = 0; x < h.hand.length(); x++)
    {
        handValue[h.hand.at(x)] += 1;
    }

    // for (auto it1 = handValue.begin(); it1 != handValue.end(); ++it1)
    //     cout << it1->first << "->" << it1->second << endl;

    // 7: 5 of a kind, 6: 4 kind, 5: full house, 4: 3 kind, 3: 2 pair, 2: 1 pair, 1: no pair
    switch (handValue.size())
    {
    case 1: // all same
        ret = 7;
        break;
    case 2:
        // could be 4 of a kind, or full house
        if ((handValue[h.hand.at(0)] == 4) || (handValue[h.hand.at(1)] == 4))
            ret = 6;
        else
            ret = 5;
        break;
    case 3:
        // 3 and 1 1, 2,2,1 - 2 pair 3 of a kind
        if ((handValue[h.hand.at(0)] == 3) || (handValue[h.hand.at(1)] == 3) || (handValue[h.hand.at(1)] == 4))
            ret = 4;
        else
            ret = 3;
        break;
    case 4:
        // one pair
        ret = 2;
        break;
    }
    return ret;
}

vector<Hand> AocDay7::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<Hand> data;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string to_convert = *iter;
        Hand h;

        h.hand = to_convert.substr(0, to_convert.find(' '));
        replace(h.hand.begin(), h.hand.end(), 'A', '>');
        replace(h.hand.begin(), h.hand.end(), 'K', '=');
        replace(h.hand.begin(), h.hand.end(), 'Q', '<');
        replace(h.hand.begin(), h.hand.end(), 'J', ';');
        replace(h.hand.begin(), h.hand.end(), 'T', ':');

        h.bid = strtol(to_convert.substr(to_convert.find(' ')).c_str(), NULL, 10);
        h.rank = rank_hand(h);

        data.push_back(h);
    }
    return data;
}

string AocDay7::part1(string filename, vector<string> extra_args)
{
    vector<Hand> data = read_input(filename);
    long sum = 0;

    std::sort(data.begin(), data.end(), [](const Hand &a, const Hand &b)
              { return (a.rank != b.rank) ? (a.rank < b.rank) : (a.hand < b.hand); });

    long otherRank = 1;
    for (vector<Hand>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        Hand h = *iter;
        long thisValue = (otherRank * h.bid);
        sum += thisValue;
        cout << otherRank << ": " << h.hand << " " << h.bid << " " << h.rank << " " << thisValue << " " << sum << endl;
        otherRank++;
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay7::part2(string filename, vector<string> extra_args)
{
    if (extra_args.size() > 0)
    {
        cout << "There are " << extra_args.size() << " extra arguments given:" << endl;
        for (vector<string>::iterator iter = extra_args.begin(); iter != extra_args.end(); ++iter)
        {
            cout << "[" << *iter << "]" << endl;
        }
    }

    vector<Hand> data = read_input(filename);
    long sum = 0;
    for (vector<Hand>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        // sum -= *iter;
    }
    ostringstream out;
    out << sum;
    return out.str();
}
