#ifndef FLAG
#define FLAG

#include <ostream>
#include "point.hpp"
#include "segment.hpp"

enum class FlagType { start, terminal };

class Flag {
public:
    Flag(Segment s, Point p, FlagType type) 
        : s_(s), p_(p), type_(type)
    {
    }

    Point p() const {
        return p_;
    }

    Segment s() const {
        return s_;
    }

    FlagType type() const {
        return type_;
    }

    Color color() const {
        return s_.type();
    }

    friend std::ostream& operator<<(std::ostream& os, const Flag& f) {
        os  << "Flag: p = " << f.p() << ", slope = " << f.s().slope() << ", color = " << (f.s().type() == Color::red ? "red" : "blue")
            << ", s = " << f.s() << ", type = " << (f.type() == FlagType::start ? "start" : "terminal") << ".";
        return os;
    }

private:
	Segment s_;
	Point p_;
    FlagType type_;
};

inline int cmp(const Flag &lhs, const Flag &rhs) {
    if (lhs.p() != rhs.p()) {
        return cmp(lhs.p(), rhs.p());
    } else if (lhs.type() != rhs.type()) {
        return (lhs.type() == FlagType::terminal) ? -1 : 1; // terminal goes first
    } else if (lhs.s().slope() != rhs.s().slope()) {
        return (lhs.s().slope() < rhs.s().slope()) ? -1 : 1;
    } else if (lhs.type() == rhs.type()) {
        std::cout << "Error: overlapping segment with same color";
        return 0;
    } else if (lhs.type() == FlagType::start) {
        return (lhs.s().type() == Color::blue) ? -1 : 1; // blue start < red start
    } else {
        return (lhs.s().type()) == Color::red ? -1 : 1; // red terminal < blue terminal
    }
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