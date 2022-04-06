#include "CCube.hpp"
#include <set>
#include <random>

CCube::CCube()
{
    for (int i = 0; i < 6; ++i)
    {
        sides_[i] = CSide(i);
    }
}

CCube::CCube(CSide sides[6])
{
    memcpy(sides_, sides, sizeof(sides_));
    if (!IsCorrectCube())
    {
        std::cerr << "Cube is not correct!\n";
    }
}

CCube::~CCube() {}

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

    bool corner_012 = 0, corner_023 = 0, corner_034 = 0, corner_014 = 0,
         corner_512 = 0, corner_523 = 0, corner_534 = 0, corner_514 = 0;
    std::set<int> cor_012 = {0, 1, 2}, cor_023 = {0, 2, 3}, cor_034 = {0, 3, 4}, cor_014 = {0, 1, 4},
                  cor_512 = {5, 1, 2}, cor_523 = {5, 2, 3}, cor_534 = {5, 3, 4}, cor_514 = {5, 1, 4};
    int color_cor_0[4][2] = {{2, 0}, {0, 0}, {0, 2}, {2, 2}};
    int color_cor_5[4][2] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    for (int i = 1; i < 5; ++i)
    {
        std::set<int> corner_1, corner_2;
        corner_1.emplace(sides_[i].GetNumColor(0, 0));
        corner_1.emplace(sides_[(i + 1) % 4].GetNumColor(0, 2));
        corner_1.emplace(sides_[0].GetNumColor(color_cor_0[i - 1][0], color_cor_0[i - 1][1]));
        corner_2.emplace(sides_[i].GetNumColor(2, 0));
        corner_2.emplace(sides_[(i + 1) % 4].GetNumColor(2, 2));
        corner_2.emplace(sides_[5].GetNumColor(color_cor_5[i - 1][0], color_cor_5[i - 1][1]));
        if (corner_1 == cor_012 || corner_2 == cor_012)
        {
            corner_012 = true;
        }
        else if (corner_1 == cor_023 || corner_2 == cor_023)
        {
            corner_023 = true;
        }
        else if (corner_1 == cor_034 || corner_2 == cor_034)
        {
            corner_034 = true;
        }
        else if (corner_1 == cor_014 || corner_2 == cor_014)
        {
            corner_014 = true;
        }
        else if (corner_1 == cor_512 || corner_2 == cor_512)
        {
            corner_512 = true;
        }
        else if (corner_1 == cor_523 || corner_2 == cor_523)
        {
            corner_523 = true;
        }
        else if (corner_1 == cor_534 || corner_2 == cor_534)
        {
            corner_534 = true;
        }
        else if (corner_1 == cor_514 || corner_2 == cor_514)
        {
            corner_514 = true;
        }
    }
    if (!corner_012 || !corner_023 || !corner_034 || !corner_014 ||
        !corner_512 || !corner_523 || !corner_534 || !corner_514)
    {
        return false;
    }

    bool edge_01 = 0, edge_02 = 0, edge_03 = 0, edge_04 = 0,
         edge_51 = 0, edge_52 = 0, edge_53 = 0, edge_54 = 0,
         edge_12 = 0, edge_23 = 0, edge_34 = 0, edge_14 = 0;
    int color_edg_0[4][2] = {{2, 1}, {1, 0}, {0, 1}, {1, 2}};
    int color_edg_5[4][2] = {{0, 1}, {1, 0}, {2, 1}, {1, 2}};
    for (int i = 1; i < 5; ++i)
    {
        int edge_left_1 = sides_[i].GetNumColor(1, 0), edge_left_2 = sides_[(i + 1) % 4].GetNumColor(1, 2),
            edge_up_1 = sides_[i].GetNumColor(0, 1), edge_up_2 = sides_[0].GetNumColor(color_edg_0[i - 1][0], color_edg_0[i - 1][1]),
            edge_down_1 = sides_[i].GetNumColor(2, 1), edge_down_2 = sides_[5].GetNumColor(color_edg_5[i - 1][0], color_edg_5[i - 1][1]);
        if (edge_left_1 == 0 && edge_left_2 == 1 || edge_left_1 == 1 && edge_left_2 == 0 ||
            edge_up_1 == 0 && edge_up_2 == 1 || edge_up_1 == 1 && edge_up_2 == 0 ||
            edge_down_1 == 0 && edge_down_2 == 1 || edge_down_1 == 1 && edge_down_2 == 0)
        {
            edge_01 = true;
        }
        else if (edge_left_1 == 0 && edge_left_2 == 2 || edge_left_1 == 2 && edge_left_2 == 0 ||
                 edge_up_1 == 0 && edge_up_2 == 2 || edge_up_1 == 2 && edge_up_2 == 0 ||
                 edge_down_1 == 0 && edge_down_2 == 2 || edge_down_1 == 2 && edge_down_2 == 0)
        {
            edge_02 = true;
        }
        else if (edge_left_1 == 0 && edge_left_2 == 3 || edge_left_1 == 3 && edge_left_2 == 0 ||
                 edge_up_1 == 0 && edge_up_2 == 3 || edge_up_1 == 3 && edge_up_2 == 0 ||
                 edge_down_1 == 0 && edge_down_2 == 3 || edge_down_1 == 3 && edge_down_2 == 0)
        {
            edge_03 = true;
        }
        else if (edge_left_1 == 0 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 0 ||
                 edge_up_1 == 0 && edge_up_2 == 4 || edge_up_1 == 4 && edge_up_2 == 0 ||
                 edge_down_1 == 0 && edge_down_2 == 4 || edge_down_1 == 4 && edge_down_2 == 0)
        {
            edge_04 = true;
        }
        else if (edge_left_1 == 5 && edge_left_2 == 1 || edge_left_1 == 1 && edge_left_2 == 5 ||
                 edge_up_1 == 5 && edge_up_2 == 1 || edge_up_1 == 1 && edge_up_2 == 5 ||
                 edge_down_1 == 5 && edge_down_2 == 1 || edge_down_1 == 1 && edge_down_2 == 5)
        {
            edge_51 = true;
        }
        else if (edge_left_1 == 5 && edge_left_2 == 2 || edge_left_1 == 2 && edge_left_2 == 5 ||
                 edge_up_1 == 5 && edge_up_2 == 2 || edge_up_1 == 2 && edge_up_2 == 5 ||
                 edge_down_1 == 5 && edge_down_2 == 2 || edge_down_1 == 2 && edge_down_2 == 5)
        {
            edge_52 = true;
        }
        else if (edge_left_1 == 5 && edge_left_2 == 3 || edge_left_1 == 3 && edge_left_2 == 5 ||
                 edge_up_1 == 5 && edge_up_2 == 3 || edge_up_1 == 3 && edge_up_2 == 5 ||
                 edge_down_1 == 5 && edge_down_2 == 3 || edge_down_1 == 3 && edge_down_2 == 5)
        {
            edge_53 = true;
        }
        else if (edge_left_1 == 5 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 5 ||
                 edge_up_1 == 5 && edge_up_2 == 4 || edge_up_1 == 4 && edge_up_2 == 5 ||
                 edge_down_1 == 5 && edge_down_2 == 4 || edge_down_1 == 4 && edge_down_2 == 5)
        {
            edge_54 = true;
        }
        else if (edge_left_1 == 1 && edge_left_2 == 2 || edge_left_1 == 2 && edge_left_2 == 1 ||
                 edge_up_1 == 1 && edge_up_2 == 2 || edge_up_1 == 2 && edge_up_2 == 1 ||
                 edge_down_1 == 1 && edge_down_2 == 2 || edge_down_1 == 2 && edge_down_2 == 1)
        {
            edge_12 = true;
        }
        else if (edge_left_1 == 2 && edge_left_2 == 3 || edge_left_1 == 3 && edge_left_2 == 2 ||
                 edge_up_1 == 2 && edge_up_2 == 3 || edge_up_1 == 3 && edge_up_2 == 2 ||
                 edge_down_1 == 2 && edge_down_2 == 3 || edge_down_1 == 3 && edge_down_2 == 2)
        {
            edge_23 = true;
        }
        else if (edge_left_1 == 3 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 3 ||
                 edge_up_1 == 3 && edge_up_2 == 4 || edge_up_1 == 4 && edge_up_2 == 3 ||
                 edge_down_1 == 3 && edge_down_2 == 4 || edge_down_1 == 4 && edge_down_2 == 3)
        {
            edge_34 = true;
        }
        else if (edge_left_1 == 1 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 1 ||
                 edge_up_1 == 1 && edge_up_2 == 4 || edge_up_1 == 4 && edge_up_2 == 1 ||
                 edge_down_1 == 1 && edge_down_2 == 4 || edge_down_1 == 4 && edge_down_2 == 1)
        {
            edge_14 = true;
        }
    }
    if (!edge_01 || !edge_02 || !edge_03 || !edge_04 ||
        !edge_51 || !edge_52 || !edge_53 || !edge_54 ||
        !edge_12 || !edge_23 || !edge_34 || !edge_14)
    {
        return false;
    }

    return true;
}

bool CCube::IsSolvedCube() const
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (sides_[i].GetNumColor(j, k) != i)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void CCube::ClockwiseRotationSide(int face, int up, int down, int left, int right)
{
    int tmp_small_cube = sides_[face].GetNumColor(0, 1);
    sides_[face].SetColor(0, 1, sides_[face].GetNumColor(1, 0));
    sides_[face].SetColor(1, 0, sides_[face].GetNumColor(2, 1));
    sides_[face].SetColor(2, 1, sides_[face].GetNumColor(1, 2));
    sides_[face].SetColor(1, 2, tmp_small_cube);

    tmp_small_cube = sides_[face].GetNumColor(0, 0);
    sides_[face].SetColor(0, 0, sides_[face].GetNumColor(2, 0));
    sides_[face].SetColor(2, 0, sides_[face].GetNumColor(2, 2));
    sides_[face].SetColor(2, 2, sides_[face].GetNumColor(0, 2));
    sides_[face].SetColor(0, 2, tmp_small_cube);

    int tmp_edge[3] = {sides_[up].GetNumColor(2, 0), sides_[up].GetNumColor(2, 1), sides_[up].GetNumColor(2, 2)};
    sides_[up].SetColor(2, 0, sides_[left].GetNumColor(2, 2));
    sides_[up].SetColor(2, 1, sides_[left].GetNumColor(1, 2));
    sides_[up].SetColor(2, 2, sides_[left].GetNumColor(0, 2));
    sides_[left].SetColor(2, 2, sides_[down].GetNumColor(0, 2));
    sides_[left].SetColor(1, 2, sides_[down].GetNumColor(0, 1));
    sides_[left].SetColor(0, 2, sides_[down].GetNumColor(0, 0));
    sides_[down].SetColor(0, 2, sides_[right].GetNumColor(0, 0));
    sides_[down].SetColor(0, 1, sides_[right].GetNumColor(1, 0));
    sides_[down].SetColor(0, 0, sides_[right].GetNumColor(2, 0));
    sides_[right].SetColor(0, 0, tmp_edge[0]);
    sides_[right].SetColor(1, 0, tmp_edge[1]);
    sides_[right].SetColor(2, 0, tmp_edge[2]);
}

void CCube::CounterclockwiseRotationSide(int face, int up, int down, int left, int right)
{
    int tmp_small_cube = sides_[face].GetNumColor(0, 1);
    sides_[face].SetColor(0, 1, sides_[face].GetNumColor(1, 2));
    sides_[face].SetColor(1, 2, sides_[face].GetNumColor(2, 1));
    sides_[face].SetColor(2, 1, sides_[face].GetNumColor(1, 0));
    sides_[face].SetColor(1, 0, tmp_small_cube);

    tmp_small_cube = sides_[face].GetNumColor(0, 0);
    sides_[face].SetColor(0, 0, sides_[face].GetNumColor(0, 2));
    sides_[face].SetColor(0, 2, sides_[face].GetNumColor(2, 2));
    sides_[face].SetColor(2, 2, sides_[face].GetNumColor(2, 0));
    sides_[face].SetColor(2, 0, tmp_small_cube);

    int tmp_edge[3] = {sides_[up].GetNumColor(2, 0), sides_[up].GetNumColor(2, 1), sides_[up].GetNumColor(2, 2)};
    sides_[up].SetColor(2, 0, sides_[right].GetNumColor(0, 0));
    sides_[up].SetColor(2, 1, sides_[right].GetNumColor(1, 0));
    sides_[up].SetColor(2, 2, sides_[right].GetNumColor(2, 0));
    sides_[right].SetColor(0, 0, sides_[down].GetNumColor(0, 2));
    sides_[right].SetColor(1, 0, sides_[down].GetNumColor(0, 1));
    sides_[right].SetColor(2, 0, sides_[down].GetNumColor(0, 0));
    sides_[down].SetColor(0, 2, sides_[left].GetNumColor(2, 2));
    sides_[down].SetColor(0, 1, sides_[left].GetNumColor(1, 2));
    sides_[down].SetColor(0, 0, sides_[left].GetNumColor(0, 2));
    sides_[left].SetColor(2, 2, tmp_edge[0]);
    sides_[left].SetColor(1, 2, tmp_edge[1]);
    sides_[left].SetColor(0, 2, tmp_edge[2]);
}

void CCube::F()
{
    ClockwiseRotationSide(1, 0, 5, 2, 4);
}

void CCube::B()
{
    ClockwiseRotationSide(3, 0, 5, 4, 2);
}

void CCube::R()
{
    ClockwiseRotationSide(4, 0, 5, 1, 3);
}

void CCube::L()
{
    ClockwiseRotationSide(2, 0, 5, 3, 1);
}

void CCube::U()
{
    ClockwiseRotationSide(0, 3, 1, 2, 4);
}

void CCube::D()
{
    ClockwiseRotationSide(5, 1, 3, 2, 4);
}

void CCube::F_()
{
    CounterclockwiseRotationSide(1, 0, 5, 2, 4);
}

void CCube::B_()
{
    CounterclockwiseRotationSide(3, 0, 5, 4, 2);
}

void CCube::R_()
{
    CounterclockwiseRotationSide(4, 0, 5, 1, 3);
}

void CCube::L_()
{
    CounterclockwiseRotationSide(2, 0, 5, 3, 1);
}

void CCube::U_()
{
    CounterclockwiseRotationSide(0, 3, 1, 2, 4);
}

void CCube::D_()
{
    CounterclockwiseRotationSide(5, 1, 3, 2, 4);
}

void CCube::GenerationCube()
{
    srand(time(NULL));
    for (int i = 0; i < 20; ++i)
    {
        int rotation = rand() % 12;
        switch (rotation)
        {
        case 0:
            F();
            break;
        case 1:
            B();
            break;
        case 2:
            R();
            break;
        case 3:
            L();
            break;
        case 4:
            U();
            break;
        case 5:
            D();
            break;
        case 6:
            F_();
            break;
        case 7:
            B_();
            break;
        case 8:
            R_();
            break;
        case 9:
            L_();
            break;
        case 10:
            U_();
            break;
        case 11:
            D_();
            break;
        }
    }
}