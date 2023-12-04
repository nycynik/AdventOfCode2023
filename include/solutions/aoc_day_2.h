#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

struct game_t
{
    int game_id;
    map<string, long> cubes;
};

class AocDay2 : public AocDay
{
private:
    vector<game_t> read_input(string filename);
    game_t parseGameData(const string &gameString);

public:
    AocDay2();
    ~AocDay2();
    string part1(string filename, vector<string> extra_args);
    string part2(string filename, vector<string> extra_args);
};

#endif
