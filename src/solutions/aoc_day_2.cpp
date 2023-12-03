#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <regex>

#include "aoc_day_2.h"
#include "file_utils.h"

using namespace std;

auto aocGames = new vector<game_t>;

AocDay2::AocDay2() : AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

game_t AocDay2::parseGameData(const string &gameString)
{
    game_t game;

    // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    // Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue

    // Extract the game_id
    game.game_id = std::stoi(gameString.substr(4, gameString.find(';')));

    // Split the gameString using regex
    string parseString = gameString.substr(gameString.find(':') + 2);
    std::regex reg(";\\s*");
    std::sregex_token_iterator iter(parseString.begin(), parseString.end(), reg, -1);
    std::sregex_token_iterator end;

    while (iter != end)
    {
        std::string part = *iter++;

        // Process each part to count occurrences of each color
        std::istringstream iss(part);

        std::string color;
        long count;

        while (iss >> count >> color)
        {
            std::string key = color.substr(0, color.find(','));
            if (game.cubes.count(key))
                game.cubes[key] = max(count, game.cubes[key]);
            else // not found
                game.cubes[key] = count;
        }
    }

    return game;
}

vector<game_t> AocDay2::read_input(string filename)
{
    // Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<game_t> games;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return games;
    }

    // split the games, and create one game with all the color information
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string game_line = *iter;

        game_t game = parseGameData(game_line);
        games.push_back(game);
    }

    return games;
}

string AocDay2::part1(string filename, vector<string> extra_args)
{
    vector<game_t> games = read_input(filename);
    long possibleGameSum = 0;

    // Display which games are *possible* with
    // only 12 red cubes, 13 green cubes, and 14 blue cubes
    map<string, long> limits = {{"red", 12}, {"green", 13}, {"blue", 14}};
    for (const auto &game : games)
    {
        bool isPossible = true;

        std::cout << "Game ID: " << game.game_id << std::endl;
        for (const auto &entry : game.cubes)
        {
            if (limits[entry.first] < entry.second)
            {
                isPossible = false;
            }
            std::cout << "  Color: " << entry.first << ", Count: " << entry.second << std::endl;
        }

        if (isPossible)
            possibleGameSum += game.game_id;
    }

    ostringstream out;
    out << possibleGameSum;
    return out.str();
}

string AocDay2::part2(string filename, vector<string> extra_args)
{
    vector<game_t> games = read_input(filename);
    long powerCubeTotal = 0;

    // Calculate the powerCube!!
    for (const auto &game : games)
    {
        long powerCube = 1;

        std::cout << "Game ID: " << game.game_id << std::endl;
        for (const auto &entry : game.cubes)
        {
            powerCube *= entry.second;
            std::cout << "  Color: " << entry.first << ", Count: " << entry.second << std::endl;
        }

        powerCubeTotal += powerCube;
    }

    ostringstream out;
    out << powerCubeTotal;
    return out.str();
}
