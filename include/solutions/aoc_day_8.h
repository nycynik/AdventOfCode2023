#ifndef __AOC_DAY_8__
#define __AOC_DAY_8__

#include "aoc_day.h"
#include <map>
struct LR_data
{
    string lr;
    map<string, pair<string, string>> data;
};

class AocDay8 : public AocDay
{
    private:
        LR_data read_input(string filename);

    public:
        AocDay8();
        ~AocDay8();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
