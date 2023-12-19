#include <map>
#include <vector>

#ifndef __AOC_DAY_19__
#define __AOC_DAY_19__

#include "aoc_day.h"

struct Day19Data
{
    map<std::string, std::string> rules;
    vector<map<string, long>> itemAttributes;
};

class AocDay19 : public AocDay
{
private:
    Day19Data read_input(std::string filename);
    std::string play_rule(map<std::string, long> item, string rule);
    std::vector<std::string> split(const std::string &s, char delim);

public:
    AocDay19();

    ~AocDay19();
    std::string part1(std::string filename, vector<string> extra_args);
    std::string part2(std::string filename, vector<string> extra_args);
};

#endif
