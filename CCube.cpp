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
                switch (sides_[i].GetNumColor(j, k))
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
        corner_1.emplace(sides_[i % 4 + 1].GetNumColor(0, 2));
        corner_1.emplace(sides_[0].GetNumColor(color_cor_0[i - 1][0], color_cor_0[i - 1][1]));
        corner_2.emplace(sides_[i].GetNumColor(2, 0));
        corner_2.emplace(sides_[i % 4 + 1].GetNumColor(2, 2));
        corner_2.emplace(sides_[5].GetNumColor(color_cor_5[i - 1][0], color_cor_5[i - 1][1]));
        if (corner_1 == cor_012 || corner_2 == cor_012)
        {
            corner_012 = true;
        }
        if (corner_1 == cor_023 || corner_2 == cor_023)
        {
            corner_023 = true;
        }
        if (corner_1 == cor_034 || corner_2 == cor_034)
        {
            corner_034 = true;
        }
        if (corner_1 == cor_014 || corner_2 == cor_014)
        {
            corner_014 = true;
        }
        if (corner_1 == cor_512 || corner_2 == cor_512)
        {
            corner_512 = true;
        }
        if (corner_1 == cor_523 || corner_2 == cor_523)
        {
            corner_523 = true;
        }
        if (corner_1 == cor_534 || corner_2 == cor_534)
        {
            corner_534 = true;
        }
        if (corner_1 == cor_514 || corner_2 == cor_514)
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
        int edge_left_1 = sides_[i].GetNumColor(1, 0),
            edge_left_2 = sides_[i % 4 + 1].GetNumColor(1, 2),
            edge_up_1 = sides_[i].GetNumColor(0, 1),
            edge_up_2 = sides_[0].GetNumColor(color_edg_0[i - 1][0], color_edg_0[i - 1][1]),
            edge_down_1 = sides_[i].GetNumColor(2, 1),
            edge_down_2 = sides_[5].GetNumColor(color_edg_5[i - 1][0], color_edg_5[i - 1][1]);
        if (edge_left_1 == 0 && edge_left_2 == 1 || edge_left_1 == 1 && edge_left_2 == 0 ||
            edge_up_1 == 0 && edge_up_2 == 1 || edge_up_1 == 1 && edge_up_2 == 0 ||
            edge_down_1 == 0 && edge_down_2 == 1 || edge_down_1 == 1 && edge_down_2 == 0)
        {
            edge_01 = true;
        }
        if (edge_left_1 == 0 && edge_left_2 == 2 || edge_left_1 == 2 && edge_left_2 == 0 ||
            edge_up_1 == 0 && edge_up_2 == 2 || edge_up_1 == 2 && edge_up_2 == 0 ||
            edge_down_1 == 0 && edge_down_2 == 2 || edge_down_1 == 2 && edge_down_2 == 0)
        {
            edge_02 = true;
        }
        if (edge_left_1 == 0 && edge_left_2 == 3 || edge_left_1 == 3 && edge_left_2 == 0 ||
            edge_up_1 == 0 && edge_up_2 == 3 || edge_up_1 == 3 && edge_up_2 == 0 ||
            edge_down_1 == 0 && edge_down_2 == 3 || edge_down_1 == 3 && edge_down_2 == 0)
        {
            edge_03 = true;
        }
        if (edge_left_1 == 0 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 0 ||
            edge_up_1 == 0 && edge_up_2 == 4 || edge_up_1 == 4 && edge_up_2 == 0 ||
            edge_down_1 == 0 && edge_down_2 == 4 || edge_down_1 == 4 && edge_down_2 == 0)
        {
            edge_04 = true;
        }
        if (edge_left_1 == 5 && edge_left_2 == 1 || edge_left_1 == 1 && edge_left_2 == 5 ||
            edge_up_1 == 5 && edge_up_2 == 1 || edge_up_1 == 1 && edge_up_2 == 5 ||
            edge_down_1 == 5 && edge_down_2 == 1 || edge_down_1 == 1 && edge_down_2 == 5)
        {
            edge_51 = true;
        }
        if (edge_left_1 == 5 && edge_left_2 == 2 || edge_left_1 == 2 && edge_left_2 == 5 ||
            edge_up_1 == 5 && edge_up_2 == 2 || edge_up_1 == 2 && edge_up_2 == 5 ||
            edge_down_1 == 5 && edge_down_2 == 2 || edge_down_1 == 2 && edge_down_2 == 5)
        {
            edge_52 = true;
        }
        if (edge_left_1 == 5 && edge_left_2 == 3 || edge_left_1 == 3 && edge_left_2 == 5 ||
            edge_up_1 == 5 && edge_up_2 == 3 || edge_up_1 == 3 && edge_up_2 == 5 ||
            edge_down_1 == 5 && edge_down_2 == 3 || edge_down_1 == 3 && edge_down_2 == 5)
        {
            edge_53 = true;
        }
        if (edge_left_1 == 5 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 5 ||
            edge_up_1 == 5 && edge_up_2 == 4 || edge_up_1 == 4 && edge_up_2 == 5 ||
            edge_down_1 == 5 && edge_down_2 == 4 || edge_down_1 == 4 && edge_down_2 == 5)
        {
            edge_54 = true;
        }
        if (edge_left_1 == 1 && edge_left_2 == 2 || edge_left_1 == 2 && edge_left_2 == 1 ||
            edge_up_1 == 1 && edge_up_2 == 2 || edge_up_1 == 2 && edge_up_2 == 1 ||
            edge_down_1 == 1 && edge_down_2 == 2 || edge_down_1 == 2 && edge_down_2 == 1)
        {
            edge_12 = true;
        }
        if (edge_left_1 == 2 && edge_left_2 == 3 || edge_left_1 == 3 && edge_left_2 == 2 ||
            edge_up_1 == 2 && edge_up_2 == 3 || edge_up_1 == 3 && edge_up_2 == 2 ||
            edge_down_1 == 2 && edge_down_2 == 3 || edge_down_1 == 3 && edge_down_2 == 2)
        {
            edge_23 = true;
        }
        if (edge_left_1 == 3 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 3 ||
            edge_up_1 == 3 && edge_up_2 == 4 || edge_up_1 == 4 && edge_up_2 == 3 ||
            edge_down_1 == 3 && edge_down_2 == 4 || edge_down_1 == 4 && edge_down_2 == 3)
        {
            edge_34 = true;
        }
        if (edge_left_1 == 1 && edge_left_2 == 4 || edge_left_1 == 4 && edge_left_2 == 1 ||
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

    int edge_up[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{2, 0}, {2, 1}, {2, 2}}, {{0, 0}, {1, 0}, {2, 0}}, 
                            {{0, 2}, {0, 1}, {0, 0}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 0}, {2, 1}, {2, 2}}};
    int edge_left[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 2}, {1, 2}, {0, 2}}, 
                              {{2, 2}, {1, 2}, {0, 2}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 0}, {2, 1}, {2, 2}}};
    int edge_down[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{0, 2}, {0, 1}, {0, 0}}, {{0, 0}, {1, 0}, {2, 0}}, 
                              {{2, 0}, {2, 1}, {2, 2}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 0}, {2, 1}, {2, 2}}};
    int edge_right[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{0, 0}, {1, 0}, {2, 0}}, {{0, 0}, {1, 0}, {2, 0}}, 
                               {{0, 0}, {1, 0}, {2, 0}}, {{0, 0}, {1, 0}, {2, 0}}, {{2, 0}, {2, 1}, {2, 2}}};

    int tmp_edge[3] = {sides_[up].GetNumColor(edge_up[face][0][0], edge_up[face][0][1]),
                       sides_[up].GetNumColor(edge_up[face][1][0], edge_up[face][1][1]),
                       sides_[up].GetNumColor(edge_up[face][2][0], edge_up[face][2][1])};
    sides_[up].SetColor(edge_up[face][0][0], edge_up[face][0][1], 
                        sides_[left].GetNumColor(edge_left[face][0][0], edge_left[face][0][1]));
    sides_[up].SetColor(edge_up[face][1][0], edge_up[face][1][1], 
                        sides_[left].GetNumColor(edge_left[face][1][0], edge_left[face][1][1]));
    sides_[up].SetColor(edge_up[face][2][0], edge_up[face][2][1], 
                        sides_[left].GetNumColor(edge_left[face][2][0], edge_left[face][2][1]));
    sides_[left].SetColor(edge_left[face][0][0], edge_left[face][0][1], 
                          sides_[down].GetNumColor(edge_down[face][0][0], edge_down[face][0][1]));
    sides_[left].SetColor(edge_left[face][1][0], edge_left[face][1][1], 
                          sides_[down].GetNumColor(edge_down[face][1][0], edge_down[face][1][1]));
    sides_[left].SetColor(edge_left[face][2][0], edge_left[face][2][1], 
                          sides_[down].GetNumColor(edge_down[face][2][0], edge_down[face][2][1]));
    sides_[down].SetColor(edge_down[face][0][0], edge_down[face][0][1], 
                          sides_[right].GetNumColor(edge_right[face][0][0], edge_right[face][0][1]));
    sides_[down].SetColor(edge_down[face][1][0], edge_down[face][1][1], 
                          sides_[right].GetNumColor(edge_right[face][1][0], edge_right[face][1][1]));
    sides_[down].SetColor(edge_down[face][2][0], edge_down[face][2][1], 
                          sides_[right].GetNumColor(edge_right[face][2][0], edge_right[face][2][1]));
    sides_[right].SetColor(edge_right[face][0][0], edge_right[face][0][1], tmp_edge[0]);
    sides_[right].SetColor(edge_right[face][1][0], edge_right[face][1][1], tmp_edge[1]);
    sides_[right].SetColor(edge_right[face][2][0], edge_right[face][2][1], tmp_edge[2]);
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

    int edge_up[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{2, 0}, {2, 1}, {2, 2}}, {{0, 0}, {1, 0}, {2, 0}}, 
                            {{0, 2}, {0, 1}, {0, 0}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 0}, {2, 1}, {2, 2}}};
    int edge_left[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 2}, {1, 2}, {0, 2}}, 
                              {{2, 2}, {1, 2}, {0, 2}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 0}, {2, 1}, {2, 2}}};
    int edge_down[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{0, 2}, {0, 1}, {0, 0}}, {{0, 0}, {1, 0}, {2, 0}}, 
                              {{2, 0}, {2, 1}, {2, 2}}, {{2, 2}, {1, 2}, {0, 2}}, {{2, 0}, {2, 1}, {2, 2}}};
    int edge_right[6][3][2] = {{{0, 2}, {0, 1}, {0, 0}}, {{0, 0}, {1, 0}, {2, 0}}, {{0, 0}, {1, 0}, {2, 0}}, 
                               {{0, 0}, {1, 0}, {2, 0}}, {{0, 0}, {1, 0}, {2, 0}}, {{2, 0}, {2, 1}, {2, 2}}};

    int tmp_edge[3] = {sides_[up].GetNumColor(edge_up[face][0][0], edge_up[face][0][1]),
                       sides_[up].GetNumColor(edge_up[face][1][0], edge_up[face][1][1]),
                       sides_[up].GetNumColor(edge_up[face][2][0], edge_up[face][2][1])};
    sides_[up].SetColor(edge_up[face][0][0], edge_up[face][0][1], 
                        sides_[right].GetNumColor(edge_right[face][0][0], edge_right[face][0][1]));
    sides_[up].SetColor(edge_up[face][1][0], edge_up[face][1][1], 
                        sides_[right].GetNumColor(edge_right[face][1][0], edge_right[face][1][1]));
    sides_[up].SetColor(edge_up[face][2][0], edge_up[face][2][1], 
                        sides_[right].GetNumColor(edge_right[face][2][0], edge_right[face][2][1]));
    sides_[right].SetColor(edge_right[face][0][0], edge_right[face][0][1], 
                           sides_[down].GetNumColor(edge_down[face][0][0], edge_down[face][0][1]));
    sides_[right].SetColor(edge_right[face][1][0], edge_right[face][1][1], 
                           sides_[down].GetNumColor(edge_down[face][1][0], edge_down[face][1][1]));
    sides_[right].SetColor(edge_right[face][2][0], edge_right[face][2][1], 
                           sides_[down].GetNumColor(edge_down[face][2][0], edge_down[face][2][1]));
    sides_[down].SetColor(edge_down[face][0][0], edge_down[face][0][1], 
                          sides_[left].GetNumColor(edge_left[face][0][0], edge_left[face][0][1]));
    sides_[down].SetColor(edge_down[face][1][0], edge_down[face][1][1], 
                          sides_[left].GetNumColor(edge_left[face][1][0], edge_left[face][1][1]));
    sides_[down].SetColor(edge_down[face][2][0], edge_down[face][2][1], 
                          sides_[left].GetNumColor(edge_left[face][2][0], edge_left[face][2][1]));
    sides_[left].SetColor(edge_left[face][0][0], edge_left[face][0][1], tmp_edge[0]);
    sides_[left].SetColor(edge_left[face][1][0], edge_left[face][1][1], tmp_edge[1]);
    sides_[left].SetColor(edge_left[face][2][0], edge_left[face][2][1], tmp_edge[2]);
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

void CCube::BangBangAlgorithm(std::string &solution, int front)
{
    switch (front)
    {
    case 1:
        R();
        U();
        R_();
        U_();
        solution += "R U R' U' ";
        break;
    case 2:
        F();
        U();
        F_();
        U_();
        solution += "F U F' U' ";
        break;
    case 3:
        L();
        U();
        L_();
        U_();
        solution += "L U L' U' ";
        break;
    case 4:
        B();
        U();
        B_();
        U_();
        solution += "B U B' U' ";
        break;
    }
}

void CCube::BangBangLeftAlgorithm(std::string &solution, int front)
{
    switch (front)
    {
    case 1:
        L_();
        U_();
        L();
        U();
        solution += "L' U' L U ";
        break;
    case 2:
        B_();
        U_();
        B();
        U();
        solution += "B' U' B U ";
        break;
    case 3:
        R_();
        U_();
        R();
        U();
        solution += "R' U' R U ";
        break;
    case 4:
        F_();
        U_();
        F();
        U();
        solution += "F' U' F U ";
        break;
    }
}

void CCube::SwapTwoEdgesAlgorithm(std::string &solution, int front)
{
    switch (front)
    {
    case 1:
        R();
        U();
        R_();
        U();
        R();
        U();
        U();
        R_();
        solution += "R U R' U R U U R' ";
        break;
    case 2:
        F();
        U();
        F_();
        U();
        F();
        U();
        U();
        F_();
        solution += "F U F' U F U U F' ";
        break;
    case 3:
        L();
        U();
        L_();
        U();
        L();
        U();
        U();
        L_();
        solution += "L U L' U L U U L' ";
        break;
    case 4:
        B();
        U();
        B_();
        U();
        B();
        U();
        U();
        B_();
        solution += "B U B' U B U U B' ";
        break;
    }
}

void CCube::SolveWhiteFlower(std::string &solution)
{
    while (sides_[0].GetNumColor(0, 1) != 5 || sides_[0].GetNumColor(1, 0) != 5 ||
           sides_[0].GetNumColor(1, 2) != 5 || sides_[0].GetNumColor(2, 1) != 5)
    {
        for (int i = 1; i < 5; ++i)
        {
            if (sides_[i].GetNumColor(1, 0) == 5)
            {
                switch (i)
                {
                case 1:
                    while (sides_[0].GetNumColor(1, 0) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    L_();
                    solution += "L' ";
                    break;
                case 2:
                    while (sides_[0].GetNumColor(0, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    B_();
                    solution += "B' ";
                    break;
                case 3:
                    while (sides_[0].GetNumColor(1, 2) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    R_();
                    solution += "R' ";
                    break;
                case 4:
                    while (sides_[0].GetNumColor(2, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    F_();
                    solution += "F' ";
                    break;
                }
            }

            if (sides_[i].GetNumColor(1, 2) == 5)
            {
                switch (i)
                {
                case 1:
                    while (sides_[0].GetNumColor(1, 2) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    R();
                    solution += "R ";
                    break;
                case 2:
                    while (sides_[0].GetNumColor(2, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    F();
                    solution += "F ";
                    break;
                case 3:
                    while (sides_[0].GetNumColor(1, 0) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    L();
                    solution += "L ";
                    break;
                case 4:
                    while (sides_[0].GetNumColor(0, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    B();
                    solution += "B ";
                    break;
                }
            }

            if (sides_[i].GetNumColor(0, 1) == 5)
            {
                switch (i)
                {
                case 1:
                    F();
                    solution += "F ";
                    while (sides_[0].GetNumColor(1, 2) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    R();
                    solution += "R ";
                    break;
                case 2:
                    L();
                    solution += "L ";
                    while (sides_[0].GetNumColor(2, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    F();
                    solution += "F ";
                    break;
                case 3:
                    B();
                    solution += "B ";
                    while (sides_[0].GetNumColor(1, 0) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    L();
                    solution += "L ";
                    break;
                case 4:
                    R();
                    solution += "R ";
                    while (sides_[0].GetNumColor(0, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    B();
                    solution += "B ";
                    break;
                }
            }

            if (sides_[i].GetNumColor(2, 1) == 5)
            {
                switch (i)
                {
                case 1:
                    while (sides_[0].GetNumColor(2, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    F_();
                    solution += "F' ";
                    while (sides_[0].GetNumColor(1, 2) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    R();
                    solution += "R ";
                    break;
                case 2:
                    while (sides_[0].GetNumColor(1, 0) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    L_();
                    solution += "L' ";
                    while (sides_[0].GetNumColor(2, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    F();
                    solution += "F ";
                    break;
                case 3:
                    while (sides_[0].GetNumColor(0, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    B_();
                    solution += "B' ";
                    while (sides_[0].GetNumColor(1, 0) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    L();
                    solution += "L ";
                    break;
                case 4:
                    while (sides_[0].GetNumColor(1, 2) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    R_();
                    solution += "R' ";
                    while (sides_[0].GetNumColor(0, 1) == 5)
                    {
                        U();
                        solution += "U ";
                    }
                    B();
                    solution += "B ";
                    break;
                }
            }
        }

        if (sides_[5].GetNumColor(0, 1) == 5)
        {
            while (sides_[0].GetNumColor(2, 1) == 5)
            {
                U();
                solution += "U ";
            }
            F();
            F();
            solution += "F F ";
        }
        if (sides_[5].GetNumColor(1, 2) == 5)
        {
            while (sides_[0].GetNumColor(1, 2) == 5)
            {
                U();
                solution += "U ";
            }
            R();
            R();
            solution += "R R ";
        }
        if (sides_[5].GetNumColor(2, 1) == 5)
        {
            while (sides_[0].GetNumColor(0, 1) == 5)
            {
                U();
                solution += "U ";
            }
            B();
            B();
            solution += "B B ";
        }
        if (sides_[5].GetNumColor(1, 0) == 5)
        {
            while (sides_[0].GetNumColor(1, 0) == 5)
            {
                U();
                solution += "U ";
            }
            L();
            L();
            solution += "L L ";
        }
    }
}

void CCube::SolveWhiteCross(std::string &solution)
{
    int edges_up[4][2] = {{2, 1}, {1, 0}, {0, 1}, {1, 2}};
    for (int i = 1; i < 5; ++i)
    {
        while (sides_[i].GetNumColor(0, 1) != i ||
               sides_[0].GetNumColor(edges_up[i - 1][0], edges_up[i - 1][1]) != 5)
        {
            U();
            solution += "U ";
        }
        switch (i)
        {
        case 1:
            F();
            F();
            solution += "F F ";
            break;
        case 2:
            L();
            L();
            solution += "L L ";
            break;
        case 3:
            B();
            B();
            solution += "B B ";
            break;
        case 4:
            R();
            R();
            solution += "R R ";
            break;
        }
    }
}

void CCube::DownWhiteCorners(std::string &solution)
{
    while (sides_[0].GetNumColor(0, 0) == 5 || sides_[0].GetNumColor(0, 2) == 5 ||
           sides_[0].GetNumColor(2, 0) == 5 || sides_[0].GetNumColor(2, 2) == 5 ||
           sides_[1].GetNumColor(0, 0) == 5 || sides_[1].GetNumColor(0, 2) == 5 ||
           sides_[2].GetNumColor(0, 0) == 5 || sides_[2].GetNumColor(0, 2) == 5 ||
           sides_[3].GetNumColor(0, 0) == 5 || sides_[3].GetNumColor(0, 2) == 5 ||
           sides_[4].GetNumColor(0, 0) == 5 || sides_[4].GetNumColor(0, 2) == 5)
    {
        std::set<int> corner;
        int side_front;
        if (sides_[0].GetNumColor(2, 2) == 5 || sides_[4].GetNumColor(0, 0) == 5 || 
            sides_[1].GetNumColor(0, 2) == 5)
        {
            corner.emplace(sides_[0].GetNumColor(2, 2));
            corner.emplace(sides_[4].GetNumColor(0, 0));
            corner.emplace(sides_[1].GetNumColor(0, 2));
            side_front = 1;
        }
        else if (sides_[0].GetNumColor(2, 0) == 5 || sides_[1].GetNumColor(0, 0) == 5 || 
                 sides_[2].GetNumColor(0, 2) == 5)
        {
            corner.emplace(sides_[0].GetNumColor(2, 0));
            corner.emplace(sides_[1].GetNumColor(0, 0));
            corner.emplace(sides_[2].GetNumColor(0, 2));
            side_front = 2;
        }
        else if (sides_[0].GetNumColor(0, 0) == 5 || sides_[2].GetNumColor(0, 0) == 5 || 
                 sides_[3].GetNumColor(0, 2) == 5)
        {
            corner.emplace(sides_[0].GetNumColor(0, 0));
            corner.emplace(sides_[2].GetNumColor(0, 0));
            corner.emplace(sides_[3].GetNumColor(0, 2));
            side_front = 3;
        }
        else if (sides_[0].GetNumColor(0, 2) == 5 || sides_[3].GetNumColor(0, 0) == 5 || 
                 sides_[4].GetNumColor(0, 2) == 5)
        {
            corner.emplace(sides_[0].GetNumColor(0, 2));
            corner.emplace(sides_[3].GetNumColor(0, 0));
            corner.emplace(sides_[4].GetNumColor(0, 2));
            side_front = 4;
        }

        int side_right = side_front == 1 ? 4 : side_front - 1;
        while (corner.find(sides_[side_front].GetNumColor(1, 1)) == corner.end() ||
               corner.find(sides_[side_right].GetNumColor(1, 1)) == corner.end())
        {
            side_front = side_front % 4 + 1;
            side_right = side_right % 4 + 1;
            U();
            solution += "U ";
        }

        BangBangAlgorithm(solution, side_front);
        while (sides_[side_front].GetNumColor(2, 2) != sides_[side_front].GetNumColor(1, 1) ||
               sides_[side_right].GetNumColor(2, 0) != sides_[side_right].GetNumColor(1, 1))
        {
            BangBangAlgorithm(solution, side_front);
            BangBangAlgorithm(solution, side_front);
        }
    }
}

void CCube::SolveWhiteCorners(std::string &solution)
{
    DownWhiteCorners(solution);

    int white_cor[4][2] = {{0, 2}, {0, 0}, {2, 0}, {2, 2}};
    for (int side_front = 1; side_front < 5; ++side_front)
    {
        int side_right = side_front == 1 ? 4 : side_front - 1;
        if (sides_[side_front].GetNumColor(2, 2) != sides_[side_front].GetNumColor(1, 1) ||
            sides_[side_right].GetNumColor(2, 0) != sides_[side_right].GetNumColor(1, 1))
        {
            std::set<int> corner, correct_corner = {side_front, side_right, 5};
            corner.emplace(sides_[side_front].GetNumColor(2, 2));
            corner.emplace(sides_[side_right].GetNumColor(2, 0));
            corner.emplace(sides_[5].GetNumColor(white_cor[side_front - 1][0], white_cor[side_front - 1][1]));
            if (corner == correct_corner)
            {
                while (sides_[side_front].GetNumColor(2, 2) != sides_[side_front].GetNumColor(1, 1) ||
                       sides_[side_right].GetNumColor(2, 0) != sides_[side_right].GetNumColor(1, 1))
                {
                    BangBangAlgorithm(solution, side_front);
                    BangBangAlgorithm(solution, side_front);
                }
            }
            else
            {
                BangBangAlgorithm(solution, side_front);
                DownWhiteCorners(solution);
            }
        }
    }
}

void CCube::DownMiddleEdges(std::string &solution)
{
    while (sides_[0].GetNumColor(2, 1) != 0 && sides_[1].GetNumColor(0, 1) != 0 ||
           sides_[0].GetNumColor(1, 0) != 0 && sides_[2].GetNumColor(0, 1) != 0 ||
           sides_[0].GetNumColor(0, 1) != 0 && sides_[3].GetNumColor(0, 1) != 0 ||
           sides_[0].GetNumColor(1, 2) != 0 && sides_[4].GetNumColor(0, 1) != 0)
    {
        int side_front;
        if (sides_[0].GetNumColor(2, 1) != 0 && sides_[1].GetNumColor(0, 1) != 0)
        {
            side_front = 1;
        }
        else if (sides_[0].GetNumColor(1, 0) != 0 && sides_[2].GetNumColor(0, 1) != 0)
        {
            side_front = 2;
        }
        else if (sides_[0].GetNumColor(0, 1) != 0 && sides_[3].GetNumColor(0, 1) != 0)
        {
            side_front = 3;
        }
        else if (sides_[0].GetNumColor(1, 2) != 0 && sides_[4].GetNumColor(0, 1) != 0)
        {
            side_front = 4;
        }

        while (sides_[side_front].GetNumColor(0, 1) != sides_[side_front].GetNumColor(1, 1))
        {
            side_front = side_front % 4 + 1;
            U();
            solution += "U ";
        }

        int edge_up[4][2] = {{2, 1}, {1, 0}, {0, 1}, {1, 2}};
        int side_right = side_front == 1 ? 4 : side_front - 1;
        int side_left = side_front % 4 + 1;
        if (sides_[0].GetNumColor(edge_up[side_front - 1][0], edge_up[side_front - 1][1]) ==
            sides_[side_right].GetNumColor(1, 1))
        {
            U();
            solution += "U ";
            BangBangAlgorithm(solution, side_front);
            BangBangLeftAlgorithm(solution, side_right);
        }
        else
        {
            U_();
            solution += "U' ";
            BangBangLeftAlgorithm(solution, side_front);
            BangBangAlgorithm(solution, side_left);
        }
    }
}

void CCube::SolveMiddleLayer(std::string &solution)
{
    DownMiddleEdges(solution);

    for (int side_front = 1; side_front < 5; ++side_front)
    {
        int side_right = side_front == 1 ? 4 : side_front - 1;
        if (sides_[side_front].GetNumColor(1, 2) != sides_[side_front].GetNumColor(1, 1))
        {
            BangBangAlgorithm(solution, side_front);
            BangBangLeftAlgorithm(solution, side_right);
            DownMiddleEdges(solution);
        }
    }
}

void CCube::SolveYellowCross(std::string &solution)
{
    int count_yellow_edges = 0;
    if (sides_[0].GetNumColor(0, 1) == 0)
    {
        ++count_yellow_edges;
    }
    if (sides_[0].GetNumColor(1, 0) == 0)
    {
        ++count_yellow_edges;
    }
    if (sides_[0].GetNumColor(1, 2) == 0)
    {
        ++count_yellow_edges;
    }
    if (sides_[0].GetNumColor(2, 1) == 0)
    {
        ++count_yellow_edges;
    }

    if (count_yellow_edges == 4)
    {
        return;
    }
    if (count_yellow_edges % 2 == 1)
    {
        std::cerr << "The cube cannot be solved!\n"
                  << "Disassemble the cube into parts and assemble it by color mechanically!\n";
        exit(1);
    }
    if (count_yellow_edges == 0)
    {
        F();
        solution += "F ";
        BangBangAlgorithm(solution, 1);
        F_();
        solution += "F' ";
    }

    int side_front = 1, side_right = 4, side_back = 3;
    while (sides_[side_front].GetNumColor(0, 1) != 0 ||
           (sides_[side_right].GetNumColor(0, 1) != 0 && sides_[side_back].GetNumColor(0, 1) != 0))
    {
        ++side_front;
        side_right = side_right % 4 + 1;
        side_back = side_back % 4 + 1;
    }

    while (sides_[side_front].GetNumColor(0, 1) == 0)
    {
        switch (side_front)
        {
        case 1:
            F();
            solution += "F ";
            break;
        case 2:
            L();
            solution += "L ";
            break;
        case 3:
            B();
            solution += "B ";
            break;
        case 4:
            R();
            solution += "R ";
            break;
        }

        BangBangAlgorithm(solution, side_front);

        switch (side_front)
        {
        case 1:
            F_();
            solution += "F' ";
            break;
        case 2:
            L_();
            solution += "L' ";
            break;
        case 3:
            B_();
            solution += "B' ";
            break;
        case 4:
            R_();
            solution += "R' ";
            break;
        }
    }
}

void CCube::SolveCorrectYellowCross(std::string &solution)
{
    int count_same_colors = 0;
    for (int i = 1; i < 5; ++i)
    {
        if (sides_[i].GetNumColor(0, 1) == sides_[i].GetNumColor(1, 1))
        {
            ++count_same_colors;
        }
    }

    while (count_same_colors != 4 && count_same_colors != 2)
    {
        U();
        solution += "U ";
        count_same_colors = 0;
        for (int i = 1; i < 5; ++i)
        {
            if (sides_[i].GetNumColor(0, 1) == sides_[i].GetNumColor(1, 1))
            {
                ++count_same_colors;
            }
        }
    }

    if (count_same_colors == 4)
    {
        return;
    }

    int side_front = 1, side_right = 4, side_back = 3;
    while (sides_[side_back].GetNumColor(0, 1) != sides_[side_back].GetNumColor(1, 1) ||
           (sides_[side_front].GetNumColor(0, 1) != sides_[side_front].GetNumColor(1, 1) &&
            sides_[side_right].GetNumColor(0, 1) != sides_[side_right].GetNumColor(1, 1)))
    {
        side_front = side_front % 4 + 1;
        side_right = side_right % 4 + 1;
        side_back = side_back % 4 + 1;
    }

    if (sides_[side_back].GetNumColor(0, 1) == sides_[side_back].GetNumColor(1, 1) &&
        sides_[side_front].GetNumColor(0, 1) == sides_[side_front].GetNumColor(1, 1))
    {
        SwapTwoEdgesAlgorithm(solution, side_front);
        side_front = side_front % 4 + 1;
    }

    SwapTwoEdgesAlgorithm(solution, side_front);
    U();
    solution += "U ";
}

void CCube::SolveYellowCorners(std::string &solution)
{
    int corners_up[4][2] = {{2, 0}, {0, 0}, {0, 2}, {2, 2}};
    int count_corrrect_corners = 0;
    for (int i = 1; i < 5; ++i)
    {
        std::set<int> corner, correct_cor = {0, i, i % 4 + 1};
        corner.emplace(sides_[i].GetNumColor(0, 0));
        corner.emplace(sides_[i % 4 + 1].GetNumColor(0, 2));
        corner.emplace(sides_[0].GetNumColor(corners_up[i - 1][0], corners_up[i - 1][1]));
        if (corner == correct_cor)
        {
            ++count_corrrect_corners;
        }
    }

    if (count_corrrect_corners == 2 || count_corrrect_corners == 3)
    {
        std::cerr << "The cube cannot be solved!\n"
                  << "Disassemble the cube into parts and assemble it by color mechanically!\n";
        exit(1);
    }

    while (count_corrrect_corners != 4)
    {
        int side_front = 1;
        while (side_front < 5)
        {
            std::set<int> corner, correct_cor = {0, side_front, side_front % 4 + 1};
            corner.emplace(sides_[side_front].GetNumColor(0, 0));
            corner.emplace(sides_[side_front % 4 + 1].GetNumColor(0, 2));
            corner.emplace(sides_[0].GetNumColor(corners_up[side_front - 1][0], corners_up[side_front - 1][1]));
            if (corner == correct_cor)
            {
                break;
            }
            ++side_front;
        }
        if (side_front == 5)
        {
            side_front = 1;
        }

        switch (side_front)
        {
        case 1:
            R();
            U_();
            L_();
            U();
            R_();
            U_();
            L();
            U();
            solution += "R U' L' U R' U' L U ";
            break;
        case 2:
            F();
            U_();
            B_();
            U();
            F_();
            U_();
            B();
            U();
            solution += "F U' B' U F' U' B U ";
            break;
        case 3:
            L();
            U_();
            R_();
            U();
            L_();
            U_();
            R();
            U();
            solution += "L U' R' U L' U' R U ";
            break;
        case 4:
            B();
            U_();
            F_();
            U();
            B_();
            U_();
            F();
            U();
            solution += "B U' F' U B' U' F U ";
            break;
        }

        count_corrrect_corners = 0;
        for (int i = 1; i < 5; ++i)
        {
            std::set<int> corner, correct_cor = {0, i, i % 4 + 1};
            corner.emplace(sides_[i].GetNumColor(0, 0));
            corner.emplace(sides_[i % 4 + 1].GetNumColor(0, 2));
            corner.emplace(sides_[0].GetNumColor(corners_up[i - 1][0], corners_up[i - 1][1]));
            if (corner == correct_cor)
            {
                ++count_corrrect_corners;
            }
        }
    }
}

void CCube::SolveCorrectYellowCorners(std::string &solution)
{
    while (sides_[0].GetNumColor(0, 0) != 0 || sides_[0].GetNumColor(0, 2) != 0 ||
           sides_[0].GetNumColor(2, 0) != 0 || sides_[0].GetNumColor(2, 2) != 0)
    {
        while (sides_[0].GetNumColor(2, 2) == 0)
        {
            U();
            solution += "U ";
        }
        while (sides_[0].GetNumColor(2, 2) != 0)
        {
            D_();
            R_();
            D();
            R();
            solution += "D' R' D R ";
        }
    }

    while (sides_[1].GetNumColor(0, 1) != sides_[1].GetNumColor(1, 1))
    {
        U();
        solution += "U ";
    }
}

void CCube::SolveCube(std::string &solution)
{
    if (IsSolvedCube())
    {
        return;
    }
    SolveWhiteFlower(solution);
    SolveWhiteCross(solution);
    SolveWhiteCorners(solution);
    SolveMiddleLayer(solution);
    SolveYellowCross(solution);
    SolveCorrectYellowCross(solution);
    SolveYellowCorners(solution);
    SolveCorrectYellowCorners(solution);
}