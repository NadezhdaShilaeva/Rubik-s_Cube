#include "CSide.cpp"

class CCube
{
public:
    CCube();
    CCube(CSide sides[6]);
    ~CCube();

    friend std::ifstream &operator>>(std::ifstream &stream, CCube &cube);
    friend std::ostream &operator<<(std::ostream &stream, const CCube &cube);
    friend std::ofstream &operator<<(std::ofstream &stream, const CCube &cube);

    bool IsCorrectCube() const;
    bool IsSolvedCube() const;
    void GenerationCube();

    void F();
    void B();
    void R();
    void L();
    void U();
    void D();
    void F_();
    void B_();
    void R_();
    void L_();
    void U_();
    void D_();

    void BangBangAlgorithm(std::string &solution, int front);
    void BangBangLeftAlgorithm(std::string &solution, int front);
    void SwapTwoEdgesAlgorithm(std::string &solution, int front);
    void SolveWhiteFlower(std::string &solution);
    void SolveWhiteCross(std::string &solution);
    void DownWhiteCorners(std::string &solution);
    void SolveWhiteCorners(std::string &solution);
    void DownMiddleEdges(std::string &solution);
    void SolveMiddleLayer(std::string &solution);
    void SolveYellowCross(std::string &solution);
    void SolveCorrectYellowCross(std::string &solution);
    void SolveYellowCorners(std::string &solution);
    void SolveCorrectYellowCorners(std::string &solution);

    void SolveCube(std::string &solution);

private:
    const CSide &GetSide(int i) const;
    void ClockwiseRotationSide(int face, int up, int down, int left, int right);
    void CounterclockwiseRotationSide(int face, int up, int down, int left, int right);

private:
    CSide sides_[6];
};