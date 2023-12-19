#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_17.h"
#include "file_utils.h"

using namespace std;

AocDay17::AocDay17():AocDay(17)
{
}

AocDay17::~AocDay17()
{
}

AOC_Grid<char> AocDay17::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<long> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        AOC_Grid<char> intGrid(1, 1);
        return intGrid;
    }
    int rows = raw_lines.size();
    int cols = raw_lines[0].size();
    AOC_Grid<char> intGrid(rows, cols);

    int cur_row = 0;
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        string grid_row = *iter;

        for (int cur_col = 0; cur_col < grid_row.length(); cur_col++)
        {
            intGrid.at(cur_row, cur_col) = grid_row[cur_col];
        }
        cur_row++;
    }

    intGrid.printGrid();

    return intGrid;
}

string AocDay17::part1(string filename, vector<string> extra_args)
{

    AOC_Grid<char> data = read_input(filename);
    data.setBlockValue('@');
    data.aStarSearch(AOC_Point(0, 0), AOC_Point(data.getRows(), data.getColumns()));
    long sum = 0;

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay17::part2(string filename, vector<string> extra_args)
{

    AOC_Grid<char> data = read_input(filename);
    long sum = 0;

    ostringstream out;
    out << sum;
    return out.str();
}
