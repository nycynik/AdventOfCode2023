#ifndef __AOC_DAY_5__
#define __AOC_DAY_5__

#include "aoc_day.h"

struct RangeMap
{
    long src;
    long dest;
    long range;
};

struct Alminac
{
    vector<long> seeds;
    vector<RangeMap> seed_soil;
    vector<RangeMap> soil_fertalizer;
    vector<RangeMap> fertalizer_water;
    vector<RangeMap> water_light;
    vector<RangeMap> light_temp;
    vector<RangeMap> temp_humidity;
    vector<RangeMap> humidity_location;
};

class AocDay5 : public AocDay
{
private:
    Alminac read_input(string filename);
    template <typename T>
    vector<T> splitString(const std::string &input);
    RangeMap read_range_map(const std::string &intut);
    long findMapping(long id, vector<RangeMap> &r);
    std::vector<std::pair<long, long>> convertToPairs(const std::vector<long> &input);

public:
    AocDay5();
    ~AocDay5();
    string part1(string filename, vector<string> extra_args);
    string part2(string filename, vector<string> extra_args);
};

#endif
