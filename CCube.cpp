#include "CCube.hpp"
#include <set>

CCube::CCube() {}

CCube::CCube(CSide sides[6])
{
    memcpy(sides_, sides, sizeof(sides_));
}

CCube::~CCube() {}

const CSide &CCube::GetSide(int i) const
{
    return sides_[i];
}

bool CCube::IsCorrectCube() const
{
    if (sides_[0].GetNumColor(1, 1) != 0 || sides_[1].GetNumColor(1, 1) != 1 ||
        sides_[2].GetNumColor(1, 1) != 2 || sides_[3].GetNumColor(1, 1) != 3 ||
        sides_[4].GetNumColor(1, 1) != 4 || sides_[5].GetNumColor(1, 1) != 5)
    {
        return false;
    }

    int count_0 = 0, count_1 = 0, count_2 = 0, count_3 = 0, count_4 = 0, count_5 = 0;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                switch (sides_[i].GetNumColor(i, j))
                {
                case 0:
                    ++count_0;
                    break;
                case 1:
                    ++count_1;
                    break;
                case 2:
                    ++count_2;
                    break;
                case 3:
                    ++count_3;
                    break;
                case 4:
                    ++count_4;
                    break;
                case 5:
                    ++count_5;
                    break;
                }
            }
        }
    }
    if (count_0 != 9 || count_1 != 9 || count_2 != 9 || count_3 != 9 || count_4 != 9 || count_5 != 9)
    {
        return false;
    }

    int corner_012 = 0, corner_023 = 0, corner_034 = 0, corner_013 = 0,
        corner_512 = 0, corner_523 = 0, corner_534 = 0, corner_513 = 0;
    std::set<int> cor_012 = {0, 1, 2}, cor_023 = {0, 2, 3}, cor_034 = {0, 3, 4}, cor_013 = {0, 1, 3},
                  cor_512 = {5, 1, 2}, cor_523 = {5, 2, 3}, cor_534 = {5, 3, 4}, cor_513 = {5, 1, 3};
    int color_0[4][2] = {{2, 0}, {0, 0}, {0, 2}, {2, 2}};
    int color_5[4][2] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    for (int i = 1; i < 5; ++i)
    {
        std::set<int> corner_1, corner_2;
        corner_1.emplace(sides_[i].GetNumColor(0, 0));
        corner_1.emplace(sides_[(i + 1) % 4].GetNumColor(0, 2));
        corner_1.emplace(sides_[0].GetNumColor(color_0[i - 1][0], color_0[i - 1][1]));
        corner_2.emplace(sides_[i].GetNumColor(2, 0));
        corner_2.emplace(sides_[(i + 1) % 4].GetNumColor(2, 2));
        corner_2.emplace(sides_[5].GetNumColor(color_5[i - 1][0], color_5[i - 1][1]));
        if (corner_1 == cor_012 || corner_2 == cor_012)
        {
            ++corner_012;
        }
        else if(corner_1 == cor_013 || corner_2 == cor_013)
        {
            ++corner_013;
        }
    }
}

std::ifstream &operator>>(std::ifstream &stream, CCube &cube)
{
    CSide sides[6];
    for (int i = 0; i < 6; ++i)
    {
        stream >> sides[i];
        stream.get();
    }
    cube = CCube(sides);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const CCube &cube)
{
    for (int i = 0; i < 6; ++i)
    {
        stream << cube.GetSide(i) << std::endl;
    }
    return stream;
}

std::ofstream &operator<<(std::ofstream &stream, const CCube &cube)
{
    for (int i = 0; i < 6; ++i)
    {
        stream << cube.GetSide(i) << std::endl;
    }
    return stream;
}