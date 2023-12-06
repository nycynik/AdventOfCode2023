#ifndef __AOC_DAY_6__
#define __AOC_DAY_6__

#include "aoc_day.h"

class AocDay6 : public AocDay
{
private:
    vector<vector<long>> read_input(const string filename);
    template <typename T>
    std::vector<T> splitString(const std::string &input);
    vector<long> findWinningTimes(long time, long distance);

public:
    AocDay6();
    ~AocDay6();
    string part1(string filename, vector<string> extra_args);
    string part2(string filename, vector<string> extra_args);
};

#endif
