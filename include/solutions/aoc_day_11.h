#ifndef __AOC_DAY_11__
#define __AOC_DAY_11__

#include "aoc_day.h"
#include "aoc_point.h"

struct Universe
{
public:
    long width;
    long height;
    vector<AOC_Point> galaxies;
};
class AocDay11 : public AocDay
{
    private:
        Universe read_input(string filename);
        void fix_galaxies(Universe &universe);

    public:
        AocDay11();
        ~AocDay11();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
