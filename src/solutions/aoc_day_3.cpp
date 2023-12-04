#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_3.h"
#include "file_utils.h"

using namespace std;

AocDay3::AocDay3() : AocDay(3)
{
}

AocDay3::~AocDay3()
{
}

AOC_Grid<char> AocDay3::read_input(string filename)
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

    // intGrid.printGrid();

    return intGrid;
}

string AocDay3::part1(string filename, vector<string> extra_args)
{
    AOC_Grid<char> data = read_input(filename);

    long sum = 0;
    long ctFound = 0;
    bool inNum = false;
    bool validNum = false;
    long foundNum = 0;
    for (int rows = 0; rows < data.getRows(); rows++)
    {
        for (int cols = 0; cols < data.getColumns(); cols++)
        {
            char curPos = data.at(rows, cols);
            if (isdigit(curPos))
            {
                foundNum = foundNum * 10 + (curPos - '0');
                if (data.at(rows, cols) == '5' || data.at(rows, cols) == '8')
                    cout << endl
                         << data.at(rows, cols) << " surronuded by ";

                vector<char> surround = data.getAdjacent(rows, cols);
                for (auto s : surround)
                {
                    if (data.at(rows, cols) == '5' || data.at(rows, cols) == '8')
                        std::cout << s;
                    if (s != '.' && !isdigit(s))
                    {
                        validNum = true;
                    }
                }
                // std::cout << std::endl;

                inNum = true;
            }
            else
            {
                if (inNum && validNum)
                {
                    // cout << "found " << foundNum << endl;
                    sum += foundNum;
                    ctFound++;
                }
                inNum = false;
                validNum = false;
                foundNum = 0;
            }
        }
        // end of row
        if (inNum && validNum) // if we are at the end of the row, and still in a num, count it
        {
            // cout << "found " << foundNum << endl;
            sum += foundNum;
            ctFound++;
        }
        inNum = false;
        validNum = false;
        foundNum = 0;
    }
    if (inNum && validNum) // one left over
    {
        sum += foundNum;
    }

    cout << "found " << ctFound;

    ostringstream out;
    out << sum;
    return out.str();
}

string AocDay3::part2(string filename, vector<string> extra_args)
{

    ostringstream out;
    out << 0;
    return out.str();
}
