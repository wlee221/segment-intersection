#ifndef SEGMENT
#define SEGMENT

#include <ostream>
#include <limits>
#include "point.hpp"

enum class Color { red, blue };

class Segment {
public:
    Segment()
        : p_(Point()), q_(Point()), type_(Color::red)
    {
    }
    
    Segment(Point p, Point q, Color type) 
        : p_(p), q_(q), type_(type)
    {
        if (p_ > q_) 
            std::swap(p_, q_);
        else if (p_ == q_) 
            std::cerr << "ERROR: The two endpoints of a segment must be distinct. p = " << p_ << ", q = " << q_ << "." << std::endl;
    }

    Point p() const {
        return p_;
    }

    Point q() const {
        return q_;
    }

    Color type() const {
        return type_;
    }

    float slope() {
        if (q_.x() == p_.x())
            return std::numeric_limits<float>::infinity();
        else 
            return (float) (q_.y() - p_.y()) / (float) (q_.x() - p_.x());
    } 

    bool operator==(const Segment &s) const {
        return orientation(p_, q_, s.p()) == 0 && orientation(p_, q_, s.q()) == 0;
    } 

    friend std::ostream& operator<<(std::ostream& os, const Segment& s) {
        os << "(" << s.p() << ", " << s.q() << ")";
        return os;
    }

private:
    Point p_;
    Point q_;
    Color type_;
};

inline bool intersects(const Segment &lhs, const Segment &rhs) {
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

// line point orientation
inline int orientation(const Segment &s, const Point &pt) {
    return orientation(s.p(), s.q(), pt);
}

#endif