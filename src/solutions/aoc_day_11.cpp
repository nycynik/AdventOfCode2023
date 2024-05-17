#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <set>

#include "aoc_day_11.h"
#include "file_utils.h"

using namespace std;

AocDay11::AocDay11() : AocDay(11)
{
}

AocDay11::~AocDay11()
{
}

void AocDay11::fix_galaxies(Universe &universe)
{
    // first find 'expansions'
    set<long> full_rows;
    set<long> full_cols;
    for (const AOC_Point g : universe.galaxies)
    {
        full_rows.insert(g.getX());
        full_cols.insert(g.getY());
    }

    vector<long> offsetRow;
    vector<long> offsetCol;
    long rowIndex = 0;
    long colIndex = 0;
    for (int row = 0; row < universe.height; ++row)
    {
        if (full_rows.count(row) == 0)
        {
            // we have to expand this one
            rowIndex++;
        }
        offsetRow.push_back(rowIndex);
        rowIndex++;
    }
    for (int col = 0; col < universe.width; ++col)
    {
        if (full_cols.count(col) == 0)
        {
            // we have to expand this one
            colIndex++;
        }
        offsetCol.push_back(colIndex);
        colIndex++;
    }

    // fix positions
    for (long i = 0; i < universe.galaxies.size(); ++i)
    {
        universe.galaxies[i].setY(offsetCol[universe.galaxies[i].getY()]);
        universe.galaxies[i].setY(offsetCol[universe.galaxies[i].getY()]);
    }
}

Universe AocDay11::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    Universe data;

    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }

    long col = 0;
    long row = 0;
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string gal_map = *iter;

        // ...#......
        long start_position = 0;
        std::size_t found_pos;
        do
        {
            found_pos = gal_map.find("#", start_position);
            if (found_pos != std::string::npos)
            {
                col = found_pos;
                // std::cout << "found '#' found at: (" << row << ", " << col << ")\n";
                data.galaxies.push_back(AOC_Point(row, col));

                start_position = found_pos + 1;
            }
        } while (found_pos != std::string::npos);

        row++;
    }
    data.height = row;
    data.width = raw_lines[0].length();

    return data;
}

string AocDay11::part1(string filename, vector<string> extra_args)
{
    Universe universe = read_input(filename);
    fix_galaxies(universe);

    long sum = 0;
    int idx = 1;
    for (int first = 0; first < universe.galaxies.size(); ++first)
    {
        for (int second = first + 1; second < universe.galaxies.size(); ++second)
        {
            AOC_Point f = universe.galaxies[first];
            AOC_Point s = universe.galaxies[second];

            long shortest_path = f.manhattanDistanceTo(s);
            sum += shortest_path;
            cout << idx++ << " Between galaxy " << f.toString() << " and galaxy " << s.toString() << ": " << shortest_path << " sum " << sum << endl;
        }
    }
    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay11::part2(string filename, vector<string> extra_args)
{

    Universe data = read_input(filename);
    long sum = 0;

    ostringstream out;
    out << sum;
    return out.str();
}
