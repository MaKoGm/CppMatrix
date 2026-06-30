#include "drop.hpp"
#include <random>
#include <vector>

// Constructor
Drop::Drop(int startX, int startY)
{
    x = startX;
    y = startY;
    length = (rand() % 15) + 5;
    speed = rand() % 2 + 1;

    for (int i = 0; i < length; i++)
    {
        secuencia[i] = static_cast<char>((rand() % 94) + 33);
    }
}

void Drop::update(const int &rows, const int &columns)
{
    y = y + speed;
    if (y - length > rows)
    {
        y = 0;
        x = rand() % columns;
    }
}

void Drop::draw(std::vector<std::vector<char>> &matrix)
{
    for (int i = 0; i < length; i++)
    {
        int current_y = y - i;

        if (current_y >= 0 && current_y < matrix.size() && x >= 0 && x < matrix[0].size())
        {
            matrix[current_y][x] = secuencia[i];
        }
    }
}