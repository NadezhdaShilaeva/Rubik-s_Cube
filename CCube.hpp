#include "CSide.hpp"

class CCube
{
public:
    CCube();
    CCube(CSide sides[6]);
    ~CCube();

    friend std::ifstream &operator>>(std::ifstream &stream, CCube &cube);
    friend std::ostream &operator<<(std::ostream &stream, const CCube &cube);
    friend std::ofstream &operator<<(std::ofstream &stream, const CCube &cube);

    const CSide &GetSide(int i) const;
    bool IsCorrectCube() const;

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
    CSide sides_[6];
};