#ifndef __AOC_DAY_3__
#define __AOC_DAY_3__

#include "aoc_day.h"
#include "aoc_grid.h"

class AocDay3 : public AocDay
{
private:
    AOC_Grid<char> read_input(string filename);

public:
    AocDay3();
    ~AocDay3();
    string part1(string filename, vector<string> extra_args);
    string part2(string filename, vector<string> extra_args);
};

#endif
