#include <iostream>
#include <fstream>

class CSide
{
public:
    CSide()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                small_cube_[i][j] = 0;
            }
        }
    }

    CSide(int small_cube[3][3])
    {
        memcpy(small_cube_, small_cube, sizeof(small_cube_));
    }

    ~CSide() {}

    friend std::ifstream &operator>>(std::ifstream &stream, CSide &side);
    friend std::ostream &operator<<(std::ostream &stream, const CSide &side);
    friend std::ofstream &operator<<(std::ofstream &stream, const CSide &side);

    int GetNumColor(int y, int x) const
    {
        return small_cube_[y][x];
    }

    char GetColor(int y, int x) const
    {
        switch (small_cube_[y][x])
        {
        case 0:
            return 'y';
            break;
        case 1:
            return 'o';
            break;
        case 2:
            return 'b';
            break;
        case 3:
            return 'r';
            break;
        case 4:
            return 'g';
            break;
        case 5:
            return 'w';
            break;
        }
    }

    void SetColor(int y, int x, int color)
    {
        small_cube_[y][x] = color;
    }

private:
    int small_cube_[3][3];
};

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
            case 'o':
                small_cube[i][j] = 1;
                break;
            case 'b':
                small_cube[i][j] = 2;
                break;
            case 'r':
                small_cube[i][j] = 3;
                break;
            case 'g':
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

std::ostream &operator<<(std::ostream &stream, const CSide &side)
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