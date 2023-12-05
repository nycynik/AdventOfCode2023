#ifndef __AOC_DAY_5__
#define __AOC_DAY_5__

#include "aoc_day.h"

struct rangeMap
{
    std::string type;
    int src;
    int dest;
    int range;
};

struct Alminac
{
    vector<long> seeds;
    vector<rangeMap> seed_soil;
    vector<rangeMap> soil_fertalizer;
    vector<rangeMap> fertalizer_water;
    vector<rangeMap> water_light;
    vector<rangeMap> light_temp;
    vector<rangeMap> temp_humidity;
    vector<rangeMap> humidity_location;
};

class AocDay5 : public AocDay
{
private:
    Alminac read_input(string filename);
    template <typename T>
    vector<T> splitString(const std::string &input);

public:
    AocDay5();
    ~AocDay5();
    string part1(string filename, vector<string> extra_args);
    string part2(string filename, vector<string> extra_args);
};

#endif
