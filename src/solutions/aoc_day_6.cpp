#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_6.h"
#include "file_utils.h"

using namespace std;

AocDay6::AocDay6() : AocDay(6)
{
}

AocDay6::~AocDay6()
{
}

template <typename T>
std::vector<T> AocDay6::splitString(const std::string &input)
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

// Time:      7  15   30
// Distance:  9  40  200
vector<vector<long>> AocDay6::read_input(const string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<vector<long>> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    vector<long> times = splitString<long>(raw_lines[0].substr(10));
    vector<long> distance = splitString<long>(raw_lines[1].substr(10));

    for (long x = 0; x < times.size(); x++)
    {
        vector<long> race;
        race.push_back(times[x]);
        race.push_back(distance[x]);
        data.push_back(race);
    }

    return data;
}

vector<long> AocDay6::findWinningTimes(long time, long distance)
{
    vector<long> winners;
    long isLosing = 0;

    long middle = time / 2;

    long top = middle + 1;
    for (long bot = middle; bot > 0; bot--)
    {
        isLosing = 0;
        if (bot > 0)
        {
            long total_dist = (bot * (time - bot));
            if (total_dist > distance)
            {
                winners.push_back(time);
                // cout << "win " << bot << " " << total_dist << " " << distance << endl;
            }
            else
            {
                isLosing = 1;
            }
        }
        if (top < time && top != bot)
        {
            long total_dist = (top * (time - top));
            if (total_dist > distance)
            {
                winners.push_back(time);
                // cout << "win " << top << " " << total_dist << " " << distance << endl;
            }
            else
            {
                isLosing = 1;
            }
        }
        top++;

        if (isLosing > 1)
        {
            return winners;
        }
    }
    cout << endl;

    return winners;
}

string AocDay6::part1(string filename, vector<string> extra_args)
{

    vector<vector<long>> data = read_input(filename);
    long sum = 1;
    for (vector<vector<long>>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        vector<long> race = *iter;
        long time = race[0];
        long dist = race[1];

        vector<long> wins = findWinningTimes(time, dist);

        cout << race[0] << " " << race[1] << " sum: " << sum << endl;
        sum *= wins.size();
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay6::part2(string filename, vector<string> extra_args)
{
    vector<vector<long>> data = read_input(filename);
    long sum = 1;
    // long time = 71530;  // 62737565;
    // long dist = 940200; // 644102312401023;
    long time = 62737565;
    long dist = 644102312401023;
    vector<long> wins = findWinningTimes(time, dist);

    // cout << race[0] << " " << race[1] << " sum: " << sum << endl;
    sum = wins.size();

    ostringstream out;
    out << sum;
    return out.str();
}
