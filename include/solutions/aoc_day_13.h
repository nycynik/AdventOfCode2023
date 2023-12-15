#ifndef __AOC_DAY_13__
#define __AOC_DAY_13__

#include "aoc_day.h"

class AocDay13 : public AocDay
{
    private:
        vector<long> read_input(string filename);
    public:
        AocDay13();
        ~AocDay13();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
