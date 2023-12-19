
#include <cmath> // Include cmath for square root and pow functions
#include <string>

class AOC_Point
{
private:
    long x, y;

public:
    AOC_Point() : x(0), y(0) {}
    AOC_Point(long x, long y) : x(x), y(y) {}

    long getX() const { return x; }; // Accessor for x coordinate
    long getY() const { return y; }; // Accessor for y coordinate
    void setX(long X) { x = X; };    // Mutator for x coordinate
    void setY(long Y) { y = Y; };    // Mutator for y coordinate

    std::string toString() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ")"; }

    bool operator==(const AOC_Point p) const
    {
        return ((p.getX() == x) && (p.getY() == y));
    }

    long distanceTo(const AOC_Point &other) const
    {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }; // Method to calculate distance to another point

    long manhattanDistanceTo(const AOC_Point &other) const
    {
        return abs(x - other.x) + abs(y - other.y);
    }
};
