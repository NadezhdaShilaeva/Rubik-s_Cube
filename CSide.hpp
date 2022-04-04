#include <iostream>
#include <fstream>

class CSide
{
public:
    CSide()
    {
        small_cube_[3][3] = {0};
    }
    CSide(int **small_cube)
    {
        memcpy(small_cube_, small_cube, sizeof(small_cube_));
    }
    ~CSide() {}

    int GetNumColor(int x, int y) const
    {
        return small_cube_[x][y];
    }
    char GetColor(int x, int y) const
    {
        switch (small_cube_[x][y])
        {
        case 0:
            return 'y';
        case 1:
            return 'o';
        case 2:
            return 'b';
        case 3:
            return 'r';
        case 4:
            return 'g';
        case 5:
            return 'w';
        }
    }
    friend std::ostream &operator<<(std::ostream &stream, const CSide &side);
    friend std::fstream &operator<<(std::fstream &stream, const CSide &side);

private:
    int small_cube_[3][3];
};

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

std::fstream &operator<<(std::fstream &stream, const CSide &side)
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