#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_5.h"
#include "file_utils.h"

using namespace std;

AocDay5::AocDay5() : AocDay(5)
{
}

AocDay5::~AocDay5()
{
}

std::vector<std::pair<long, long>> AocDay5::convertToPairs(const std::vector<long> &input)
{
    std::vector<std::pair<long, long>> result;

    // Ensure the input vector has an even number of elements
    if (input.size() % 2 != 0)
    {
        std::cerr << "Error: Input vector must have an even number of elements." << std::endl;
        return result;
    }

    // Iterate through the input vector and create pairs
    for (size_t i = 0; i < input.size(); i += 2)
    {
        result.emplace_back(input[i], input[i + 1]);
    }

    return result;
}

template <typename T>
std::vector<T> AocDay5::splitString(const std::string &input)
{
    std::vector<T> result;
    std::istringstream iss(input);
    T number;

    while (iss >> number)
    {
        result.push_back(number);
    }

    return result;
}

RangeMap AocDay5::read_range_map(const std::string &intut)
{
    RangeMap r;
    if (intut.length() > 0)
    {
        vector<long> s = splitString<long>(intut);
        if (s.size() != 3)
        {
            cout << "  ERROR: oh no!";
        }
        r.dest = s[0];
        r.src = s[1];
        r.range = s[2];
    }
    return r;
}

long AocDay5::findMapping(long id, vector<RangeMap> &ranges)
{
    long foundID = id;

    for (auto it = ranges.begin(); it != ranges.end(); ++it)
    {
        RangeMap rn = *it;
        if (foundID >= rn.src && foundID < (rn.src + rn.range))
        {
            return (foundID - rn.src) + rn.dest;
        }
    }

    return id;
}

Alminac AocDay5::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    Alminac alminac;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return alminac;
    }
    int index = 0;
    int mode = 0;
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string line = *iter;
        // cout << "line: " << line << endl;

        if (line.length() == 0)
        {
            mode++;
        }
        else
        {
            switch (mode)
            {
            case 0: // starting with seeds
                // skip 7 chars and read the rest
                alminac.seeds = splitString<long>(line.substr(7));
                break;

            case 1: // seeds to soil
                if (line.substr(0, 2) != "se")
                {
                    RangeMap r = read_range_map(line);
                    alminac.seed_soil.push_back(read_range_map(line));
                }
                break;
            case 2: // soil to fert
                if (line.substr(0, 2) != "so")
                {
                    alminac.soil_fertalizer.push_back(read_range_map(line));
                }
                break;
            case 3: // soil to fert
                if (line.substr(0, 2) != "fe")
                    alminac.fertalizer_water.push_back(read_range_map(line));
                break;
            case 4: // water-to-light map
                if (line.substr(0, 2) != "wa")
                    alminac.water_light.push_back(read_range_map(line));
                break;
            case 5: // light-to-temperature map
                if (line.substr(0, 2) != "li")
                    alminac.light_temp.push_back(read_range_map(line));
                break;
            case 6: // temperature-to-humidity map
                if (line.substr(0, 2) != "te")
                    alminac.temp_humidity.push_back(read_range_map(line));
                break;
            case 7: // humidity-to-location map
                if (line.substr(0, 2) != "hu")
                    alminac.humidity_location.push_back(read_range_map(line));
                break;
            }
        }
    }
    return alminac;
}

string AocDay5::part1(string filename, vector<string> extra_args)
{
    Alminac data = read_input(filename);
    long lowestLocation = LLONG_MAX;

    for (long seed : data.seeds)
    {
        long soil = findMapping(seed, data.seed_soil);
        long ferilizer = findMapping(soil, data.soil_fertalizer);
        long water = findMapping(ferilizer, data.fertalizer_water);
        long light = findMapping(water, data.water_light);
        long temp = findMapping(light, data.light_temp);
        long humidity = findMapping(temp, data.temp_humidity);
        long location = findMapping(humidity, data.humidity_location);

        cout << "Seed " << seed << ", soil " << soil << ", fertilizer " << ferilizer << ", water " << water
             << ", light " << light << ", temperature " << temp << ", humidity "
             << humidity << ", location " << location << "." << endl;

        lowestLocation = min(lowestLocation, location);
    }
    ostringstream out;
    out << lowestLocation;
    return out.str();
}

string AocDay5::part2(string filename, vector<string> extra_args)
{
    Alminac data = read_input(filename);
    long lowestLocation = LLONG_MAX;

    std::vector<std::pair<long, long>> seedPairs = convertToPairs(data.seeds);

    for (const auto &pair : seedPairs)
    {
        cout << "Seeds: " << pair.first << " - " << pair.second;
        for (long pairIndex = pair.first; pairIndex < (pair.second + pair.first); pairIndex++)
        {
            long soil = findMapping(pairIndex, data.seed_soil);
            long ferilizer = findMapping(soil, data.soil_fertalizer);
            long water = findMapping(ferilizer, data.fertalizer_water);
            long light = findMapping(water, data.water_light);
            long temp = findMapping(light, data.light_temp);
            long humidity = findMapping(temp, data.temp_humidity);
            long location = findMapping(humidity, data.humidity_location);

            lowestLocation = min(lowestLocation, location);
        }
        cout << " - lowest seed so far " << lowestLocation << endl;
        std::flush(std::cout);
    }
    ostringstream out;
    out << lowestLocation;
    return out.str();
}
