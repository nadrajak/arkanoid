// @author Jakub Nádraský <nadrajak@fit.cvut.cz>
// @date 5/31/20

#pragma once


/**
 * Simple helper class representing a 2 dimensional (x, y) vector.
 * Made specifically to make storing and working with velocities/positions easier.
 * */
struct CVector2 {
    double x, y;

    /** Vector addition */
    CVector2 &operator+=(const CVector2 &rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    /** Vector scaling */
    CVector2 &operator*=(double scalar)
    {
        this->y *= scalar;
        this->x *= scalar;
        return *this;
    }
};

inline CVector2 operator+(CVector2 lhs, const CVector2 &rhs)
{
    lhs += rhs;
    return lhs;
}

inline CVector2 operator*(CVector2 lhs, double scalar)
{
    lhs *= scalar;
    return lhs;
}
