#include <string>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>

#include "aoc_day_4.h"
#include "file_utils.h"

using namespace std;

struct Game
{
    int gameNumber;
    vector<int> winning;
    vector<int> ours;
};

AocDay4::AocDay4() : AocDay(4)
{
}

AocDay4::~AocDay4()
{
}

template <typename T>
std::vector<T> AocDay4::splitString(const std::string &input)
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

vector<Game> AocDay4::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<Game> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        long l;
        string to_convert = *iter;

        int firstSplitPos = to_convert.find(':');
        int secondSplitPos = to_convert.find('|');

        Game g;
        g.gameNumber = stoi(to_convert.substr(4, firstSplitPos));
        g.winning = splitString<int>(to_convert.substr(firstSplitPos + 2, secondSplitPos - firstSplitPos));
        g.ours = splitString<int>(to_convert.substr(secondSplitPos + 2));

        std::sort(g.winning.begin(), g.winning.end());
        std::sort(g.ours.begin(), g.ours.end());

        data.push_back(g);
    }
    return data;
}

string AocDay4::part1(string filename, vector<string> extra_args)
{
    vector<Game> data = read_input(filename);
    long sum = 0;
    for (vector<Game>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        Game g = *iter;

        // determine num winning numbers.
        std::vector<int> winningNumbers;

        std::set_intersection(
            g.winning.begin(), g.winning.end(),
            g.ours.begin(), g.ours.end(),
            std::back_inserter(winningNumbers));

        int score = winningNumbers.size() > 0 ? pow(2, ((winningNumbers.size()) - 1)) : 0;
        std::cout << "Game " << g.gameNumber << ": " << score << " with " << winningNumbers.size() << " matches." << std::endl;

        sum += score;
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay4::part2(string filename, vector<string> extra_args)
{

    vector<Game> data = read_input(filename);
    map<int, int> gameResults;
    deque<int> gameQueue;

    for (vector<Game>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        Game g = *iter;

        // determine num winning numbers.
        std::vector<int> winningNumbers;

        std::set_intersection(
            g.winning.begin(), g.winning.end(),
            g.ours.begin(), g.ours.end(),
            std::back_inserter(winningNumbers));

        int score = winningNumbers.size();
        // std::cout << "Game " << g.gameNumber << ": " << score << " with " << winningNumbers.size() << " matches." << std::endl;

        gameResults[g.gameNumber] = score;
        gameQueue.push_back(g.gameNumber);
    }

    // now sum it up!
    long totalCards = 0;
    while (gameQueue.size() > 0)
    {
        totalCards++;
        int gameID = gameQueue.front();

        int gameScore = gameResults.at(gameID);

        for (int x = 0; x < gameScore; x++)
        {
            gameQueue.push_back(gameID + 1 + x);
        }

        gameQueue.pop_front();
    }

    ostringstream out;
    out << totalCards;
    return out.str();
}
