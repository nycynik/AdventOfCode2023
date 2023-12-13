#ifndef __AOC_DAY_7__
#define __AOC_DAY_7__

#include "aoc_day.h"

struct Hand
{
    string hand;
    long rank;
    long bid;
};

class AocDay7 : public AocDay
{
private:
    vector<Hand> read_input(string filename);
    long rank_hand(Hand h);

public:
    AocDay7();
    ~AocDay7();
    string part1(string filename, vector<string> extra_args);
    string part2(string filename, vector<string> extra_args);
};

#endif
