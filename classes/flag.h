#ifndef FLAG
#define FLAG

#include <ostream>
#include "point.h"
#include "segment.h"

class Flag {
public:
    // TODO: use enum instead of bool for start/terminal
    Flag(Segment s, Point p, bool start) 
        : s_(s), p_(p), start_(start)
    {
    }

    Point p() const {
        return p_;
    }

    Segment s() const {
        return s_;
    }

    bool start() const {
        return start_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Flag& f) {
        os  << "Flag: segment = " << f.s() << ", color = " << (f.s().red() ? "red" : "blue")
            << ", type = " << (f.start() ? "start" : "terminal") << "." << std::endl;
        return os;
    }

private:
	Segment s_;
	Point p_;
    bool start_;
};

inline int cmp(const Flag &lhs, const Flag &rhs) {
    if (lhs.p() != rhs.p()) {
        return cmp(lhs.p(), rhs.p());
    } else if (lhs.start() != rhs.start()) {
        return lhs.start() ? 1 : -1; // terminal goes first
    } else if (lhs.s().slope() != rhs.s().slope()) {
        return (lhs.s().slope() < rhs.s().slope()) ? -1 : 1;
    } else {
        if (lhs.start()) {
            return (lhs.s().red()) ? 1 : -1; // blue start < red start
        } else {
            return (lhs.s().red()) ? -1 : 1; // red terminal < blue terminal
        }
    }   
    std::cerr << "ERROR: overlapping lines of same color";
    return 0;
}

// overload comparison operators
inline bool operator==(const Flag& lhs, const Flag& rhs){ return cmp(lhs,rhs) == 0; }
inline bool operator!=(const Flag& lhs, const Flag& rhs){ return cmp(lhs,rhs) != 0; }
inline bool operator< (const Flag& lhs, const Flag& rhs){ return cmp(lhs,rhs) <  0; }
inline bool operator> (const Flag& lhs, const Flag& rhs){ return cmp(lhs,rhs) >  0; }
inline bool operator<=(const Flag& lhs, const Flag& rhs){ return cmp(lhs,rhs) <= 0; }
inline bool operator>=(const Flag& lhs, const Flag& rhs){ return cmp(lhs,rhs) >= 0; }

#endif