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

private:
    const CSide &GetSide(int i) const;
    void ClockwiseRotationSide(int face, int up, int down, int left, int right);
    void CounterclockwiseRotationSide(int face, int up, int down, int left, int right);

private:
    CSide sides_[6];
};