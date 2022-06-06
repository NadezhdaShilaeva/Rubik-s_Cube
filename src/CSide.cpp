#include "CSide.hpp"

CSide::CSide()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            small_cube_[i][j] = 0;
        }
    }
}

CSide::CSide(int color)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            small_cube_[i][j] = color;
        }
    }
}

CSide::CSide(int small_cube[3][3])
{
    memcpy(small_cube_, small_cube, sizeof(small_cube_));
}

CSide::~CSide() {}

std::ifstream &operator>>(std::ifstream &stream, CSide &side)
{
    int small_cube[3][3];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            char color;
            stream >> color;
            switch (color)
            {
            case 'y':
                small_cube[i][j] = 0;
                break;
            case 'b':
                small_cube[i][j] = 1;
                break;
            case 'o':
                small_cube[i][j] = 2;
                break;
            case 'g':
                small_cube[i][j] = 3;
                break;
            case 'r':
                small_cube[i][j] = 4;
                break;
            case 'w':
                small_cube[i][j] = 5;
                break;

            default:
                std::cerr << "The description of cube is not correct!\n";
            }
        }
    }
    side = CSide(small_cube);
    return stream;
}

std::ofstream &operator<<(std::ofstream &stream, const CSide &side)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            stream << side.GetColor(i, j) << " ";
        }
        stream << std::endl;
    }
    return stream;
}

int CSide::GetNumColor(int y, int x) const
{
    return small_cube_[y][x];
}

char CSide::GetColor(int y, int x) const
{
    switch (small_cube_[y][x])
    {
    case 0:
        return 'y';
        break;
    case 1:
        return 'b';
        break;
    case 2:
        return 'o';
        break;
    case 3:
        return 'g';
        break;
    case 4:
        return 'r';
        break;
    case 5:
        return 'w';
        break;
    }
}

void CSide::SetColor(int y, int x, int color)
{
    small_cube_[y][x] = color;
}