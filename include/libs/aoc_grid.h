#ifndef __AOC_GRID__
#define __AOC_GRID__

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

template <typename T>
class AOC_Grid
{
private:
    int rows;
    int columns;
    std::vector<T> data;

public:
    // Constructor to initialize the grid with rows and columns
    AOC_Grid(int rows, int columns) : rows(rows), columns(columns), data(rows * columns)
    {
    }

    ~AOC_Grid()
    {
    }

    // Get the element at the specified row and column
    T &at(int row, int col)
    {
        return data[row * columns + col];
    }

    // Get the number of rows in the grid
    int getRows() const
    {
        return rows;
    }

    // Get the number of columns in the grid
    int getColumns() const
    {
        return columns;
    }

    // Print the grid
    void printGrid()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                std::cout << at(i, j) << ' ';
            }
            std::cout << std::endl;
        }
    }

    // Get adjacent items given a specific row and column position
    std::vector<T> getAdjacent(int row, int col)
    {
        std::vector<T> result;

        for (int i = std::max(0, row - 1); i <= std::min(rows - 1, row + 1); ++i)
        {
            for (int j = std::max(0, col - 1); j <= std::min(columns - 1, col + 1); ++j)
            {
                if (i == col && j == row)
                    break;

                result.push_back(at(i, j));
            }
        }

        return result;
    }
};
#endif
