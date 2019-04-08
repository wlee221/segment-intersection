#ifndef SEGMENT
#define SEGMENT

#include <ostream>
#include "point.h"

class Segment {
public:
    Segment(Point p, Point q, bool red) 
        : p_(p), q_(q), red_(red)
    {
    }

    Point p() const {
        return p_;
    }

    Point q() const {
        return q_;
    }

    bool red() const {
        return red_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Segment& s) {
        os << "(" << s.p() << ", " << s.q() << ")";
        return os;
    }

private:
    Point p_;
    Point q_;
    bool red_;
};

bool intersects(const Segment &lhs, const Segment &rhs) {
    int det1 = orientation(lhs.p(), lhs.q(), rhs.p());
    int det2 = orientation(lhs.p(), lhs.q(), rhs.q());
    int det3 = orientation(rhs.p(), rhs.q(), lhs.p());
    int det4 = orientation(rhs.p(), rhs.q(), lhs.q());

    if (!(det1 * det2 == -1))
        return false;
    if (!(det3 * det4 == -1))
        return false;
    return true;
}

#endif