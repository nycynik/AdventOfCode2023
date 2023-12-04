#ifndef __AOC_DAY_4__
#define __AOC_DAY_4__

#include "aoc_day.h"

struct Game;

class AocDay4 : public AocDay
{
    private:
        std::vector<Game> read_input(string filename);
        template <typename T>
        std::vector<T> splitString(const std::string &input);

    public:
        AocDay4();
        ~AocDay4();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};


#endif
