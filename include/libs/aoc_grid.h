#ifndef __AOC_GRID__
#define __AOC_GRID__

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cfloat>
#include <set>
#include "aoc_point.h"

using namespace std;

// A structure to hold the necessary parameters
struct cell
{
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<long, long>> pPair;

template <typename T>
class AOC_Grid
{
private:
    int rows;
    int columns;
    std::vector<T> data;
    T blockValue;

public:
    // Constructor to initialize the grid with rows and columns
    AOC_Grid(int rows, int columns) : rows(rows), columns(columns), data(rows * columns)
    {
    }

    ~AOC_Grid()
    {
    }

    void setBlockValue(T block)
    {
        blockValue = block;
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

    bool isValid(AOC_Point p)
    {
        return isValid(p.getY(), p.getX());
    }

    bool isValid(long row, long col)
    {
        // Returns true if row number and column number is in range
        return (row >= 0) && (row < rows) && (col >= 0) && (col < columns);
    }

    bool isUnBlocked(AOC_Point p)
    {
        return isUnBlocked(p.getY(), p.getX());
    }

    // A Utility Function to check whether the given cell is
    // blocked or not
    bool isUnBlocked(int row, int col)
    {
        // Returns true if the cell is not blocked else false
        if (data[row * columns + col] == blockValue)
            return (true);
        else
            return (false);
    }

    // A Utility Function to calculate the 'h' heuristics.
    double calculateHValue(long row, long col, AOC_Point dest)
    {
        // Return using the distance formula
        return ((double)sqrt(
            (row - dest.getY()) * (row - dest.getX()) + (col - dest.getY()) * (col - dest.getX())));
    }

    // A Utility Function to trace the path from the source
    // to destination
    void tracePath(cell cellDetails[][COL], AOC_Point dest)
    {
        printf("\nThe Path is ");
        int row = dest.getY();
        int col = dest.getX();

        stack<Pair> Path;

        while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
        {
            Path.push(make_pair(row, col));
            int temp_row = cellDetails[row][col].parent_i;
            int temp_col = cellDetails[row][col].parent_j;
            row = temp_row;
            col = temp_col;
        }

        Path.push(make_pair(row, col));
        while (!Path.empty())
        {
            pair<int, int> p = Path.top();
            Path.pop();
            printf("-> (%d,%d) ", p.first, p.second);
        }

        return;
    }

    // A Function to find the shortest path between a given source cell
    // and a destination cell using A* Search
    // https://www.geeksforgeeks.org/a-search-algorithm/ with modifications
    void aStarSearch(AOC_Point src, AOC_Point dest)
    {
        // If the source is out of range
        if (isValid(src.getY(), src.getX()) == false)
        {
            printf("Source is invalid\n");
            return;
        }

        // If the destination is out of range
        if (isValid(dest) == false)
        {
            printf("Destination is invalid\n");
            return;
        }

        // Either the source or the destination is blocked
        if (isUnBlocked(src) == false || isUnBlocked(dest) == false)
        {
            printf("Source or the destination is blocked\n");
            return;
        }

        // If the destination cell is the same as source cell
        if (src == dest)
        {
            printf("We are already at the destination\n");
            return;
        }

        // Create a closed list and initialise it to false which
        // means that no cell has been included yet This closed
        // list is implemented as a boolean 2D array
        bool closedList[rows][columns];
        memset(closedList, false, sizeof(closedList));

        // Declare a 2D array of structure to hold the details
        // of that cell
        cell cellDetails[rows][columns];

        int i, j;

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < columns; j++)
            {
                cellDetails[i][j].f = std::numeric_limits<float>::max();
                cellDetails[i][j].g = std::numeric_limits<float>::max();
                cellDetails[i][j].h = std::numeric_limits<float>::max();
                cellDetails[i][j].parent_i = -1;
                cellDetails[i][j].parent_j = -1;
            }
        }

        // Initialising the parameters of the starting node
        i = src.getY(), j = src.getX();
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j;

        /*
         Create an open list having information as-
         <f, <i, j>>
         where f = g + h,
         and i, j are the row and column index of that cell
         Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
         This open list is implemented as a set of pair of
         pair.*/
        set<pPair> openList;

        // Put the starting cell on the open list and set its
        // 'f' as 0
        openList.insert(make_pair(0.0, make_pair(i, j)));

        // We set this boolean value as false as initially
        // the destination is not reached.
        bool foundDest = false;

        while (!openList.empty())
        {
            pPair p = *openList.begin();

            // Remove this vertex from the open list
            openList.erase(openList.begin());

            // Add this vertex to the closed list
            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            /*
             Generating all the 8 successor of this cell

                 N.W   N   N.E
                   \   |   /
                    \  |  /
                 W----Cell----E
                      / | \
                    /   |  \
                 S.W    S   S.E

             Cell-->Popped Cell (i, j)
             N -->  North       (i-1, j)
             S -->  South       (i+1, j)
             E -->  East        (i, j+1)
             W -->  West           (i, j-1)
             N.E--> North-East  (i-1, j+1)
             N.W--> North-West  (i-1, j-1)
             S.E--> South-East  (i+1, j+1)
             S.W--> South-West  (i+1, j-1)*/

            // To store the 'g', 'h' and 'f' of the 8 successors
            double gNew, hNew, fNew;

            //----------- 1st Successor (North) ------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i - 1, j) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i - 1][j] == false && isUnBlocked(i - 1, j) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i - 1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i - 1][j].f == std::numeric_limits<float>::max() || cellDetails[i - 1][j].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j)));

                        // Update the details of this cell
                        cellDetails[i - 1][j].f = fNew;
                        cellDetails[i - 1][j].g = gNew;
                        cellDetails[i - 1][j].h = hNew;
                        cellDetails[i - 1][j].parent_i = i;
                        cellDetails[i - 1][j].parent_j = j;
                    }
                }
            }

            //----------- 2nd Successor (South) ------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i + 1, j) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }
                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i + 1][j] == false && isUnBlocked(i + 1, j) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i + 1, j, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i + 1][j].f == std::numeric_limits<float>::max() || cellDetails[i + 1][j].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j)));
                        // Update the details of this cell
                        cellDetails[i + 1][j].f = fNew;
                        cellDetails[i + 1][j].g = gNew;
                        cellDetails[i + 1][j].h = hNew;
                        cellDetails[i + 1][j].parent_i = i;
                        cellDetails[i + 1][j].parent_j = j;
                    }
                }
            }

            //----------- 3rd Successor (East) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j + 1) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i, j + 1) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i][j + 1] == false && isUnBlocked(i, j + 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j + 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i][j + 1].f == std::numeric_limits<float>::max() || cellDetails[i][j + 1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j + 1)));

                        // Update the details of this cell
                        cellDetails[i][j + 1].f = fNew;
                        cellDetails[i][j + 1].g = gNew;
                        cellDetails[i][j + 1].h = hNew;
                        cellDetails[i][j + 1].parent_i = i;
                        cellDetails[i][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 4th Successor (West) ------------

            // Only process this cell if this is a valid one
            if (isValid(i, j - 1) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i, j - 1) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i][j - 1] == false && isUnBlocked(i, j - 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j - 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i][j - 1].f == std::numeric_limits<float>::max() || cellDetails[i][j - 1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i, j - 1)));

                        // Update the details of this cell
                        cellDetails[i][j - 1].f = fNew;
                        cellDetails[i][j - 1].g = gNew;
                        cellDetails[i][j - 1].h = hNew;
                        cellDetails[i][j - 1].parent_i = i;
                        cellDetails[i][j - 1].parent_j = j;
                    }
                }
            }

            //----------- 5th Successor (North-East)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j + 1) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i - 1, j + 1) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i - 1][j + 1] == false && isUnBlocked(i - 1, j + 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j + 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i - 1][j + 1].f == std::numeric_limits<float>::max() || cellDetails[i - 1][j + 1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j + 1)));

                        // Update the details of this cell
                        cellDetails[i - 1][j + 1].f = fNew;
                        cellDetails[i - 1][j + 1].g = gNew;
                        cellDetails[i - 1][j + 1].h = hNew;
                        cellDetails[i - 1][j + 1].parent_i = i;
                        cellDetails[i - 1][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 6th Successor (North-West)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i - 1, j - 1) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i - 1, j - 1) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i - 1][j - 1] == false && isUnBlocked(i - 1, j - 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j - 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i - 1][j - 1].f == std::numeric_limits<float>::max() || cellDetails[i - 1][j - 1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i - 1, j - 1)));
                        // Update the details of this cell
                        cellDetails[i - 1][j - 1].f = fNew;
                        cellDetails[i - 1][j - 1].g = gNew;
                        cellDetails[i - 1][j - 1].h = hNew;
                        cellDetails[i - 1][j - 1].parent_i = i;
                        cellDetails[i - 1][j - 1].parent_j = j;
                    }
                }
            }

            //----------- 7th Successor (South-East)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j + 1) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i + 1, j + 1) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i + 1][j + 1] == false && isUnBlocked(i + 1, j + 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j + 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i + 1][j + 1].f == std::numeric_limits<float>::max() || cellDetails[i + 1][j + 1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j + 1)));

                        // Update the details of this cell
                        cellDetails[i + 1][j + 1].f = fNew;
                        cellDetails[i + 1][j + 1].g = gNew;
                        cellDetails[i + 1][j + 1].h = hNew;
                        cellDetails[i + 1][j + 1].parent_i = i;
                        cellDetails[i + 1][j + 1].parent_j = j;
                    }
                }
            }

            //----------- 8th Successor (South-West)
            //------------

            // Only process this cell if this is a valid one
            if (isValid(i + 1, j - 1) == true)
            {
                // If the destination cell is the same as the
                // current successor
                if (AOC_Point(i + 1, j - 1) == dest)
                {
                    // Set the Parent of the destination cell
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }

                // If the successor is already on the closed
                // list or if it is blocked, then ignore it.
                // Else do the following
                else if (closedList[i + 1][j - 1] == false && isUnBlocked(i + 1, j - 1) == true)
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j - 1, dest);
                    fNew = gNew + hNew;

                    // If it isn’t on the open list, add it to
                    // the open list. Make the current square
                    // the parent of this square. Record the
                    // f, g, and h costs of the square cell
                    //                OR
                    // If it is on the open list already, check
                    // to see if this path to that square is
                    // better, using 'f' cost as the measure.
                    if (cellDetails[i + 1][j - 1].f == std::numeric_limits<float>::max() || cellDetails[i + 1][j - 1].f > fNew)
                    {
                        openList.insert(make_pair(
                            fNew, make_pair(i + 1, j - 1)));

                        // Update the details of this cell
                        cellDetails[i + 1][j - 1].f = fNew;
                        cellDetails[i + 1][j - 1].g = gNew;
                        cellDetails[i + 1][j - 1].h = hNew;
                        cellDetails[i + 1][j - 1].parent_i = i;
                        cellDetails[i + 1][j - 1].parent_j = j;
                    }
                }
            }
        }

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destination cell. This may happen when the
        // there is no way to destination cell (due to
        // blockages)
        if (foundDest == false)
            printf("Failed to find the Destination Cell\n");

        return;
    }
};
#endif
