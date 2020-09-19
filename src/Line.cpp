#include "Line.hpp"

Line::Line(CorrectionPoint && p1, CorrectionPoint && p2)
{
    p[0] = p1;
    p[1] = p2;

    if (getValid())
    {
        p[0].weigth = float(p[1].distance) / (p[0].distance + p[1].distance);
        p[1].weigth = float(p[0].distance) / (p[0].distance + p[1].distance);
    } else
    {
        p[0].weigth = 0.f;
        p[1].weigth = 0.f;
    }
}

bool Line::getValid() const
{
    return p[0].valid && p[1].valid;
}

int Line::getDistance() const
{
    return p[0].distance + p[1].distance;
}

CorrectionPoint &Line::operator[](int index)
{
    return p[index];
}

const CorrectionPoint &Line::operator[](int index) const
{
    return p[index];
}