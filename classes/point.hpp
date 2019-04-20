#ifndef POINT
#define POINT

#include <ostream>

class Point {
public:
    Point() 
        : x_(0), y_(0)
    {
    }

    Point(int x, int y) 
        : x_(x), y_(y)
    {
    }

    int x() const {
        return x_;
    }

    int y() const {
        return y_;
    }

    Point operator+(const Point &p) {
        return Point(x_ + p.x_, y_ + p.y_);
    } 

    Point operator-(const Point &p) {
        return Point(x_ - p.x_, y_ - p.y_);
    } 


    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x() << ", " << p.y() << ")";
        return os;
    }


private:
    int x_;
    int y_;
};

// three-way comparison funciton
inline int cmp(const Point &lhs, const Point &rhs) {
    if (lhs.x() != rhs.x()) 
        return lhs.x() - rhs.x();
    else
        return lhs.y() - rhs.y();
}

// overload comparison operators
inline bool operator==(const Point& lhs, const Point& rhs){ return cmp(lhs,rhs) == 0; }
inline bool operator!=(const Point& lhs, const Point& rhs){ return cmp(lhs,rhs) != 0; }
inline bool operator< (const Point& lhs, const Point& rhs){ return cmp(lhs,rhs) <  0; }
inline bool operator> (const Point& lhs, const Point& rhs){ return cmp(lhs,rhs) >  0; }
inline bool operator<=(const Point& lhs, const Point& rhs){ return cmp(lhs,rhs) <= 0; }
inline bool operator>=(const Point& lhs, const Point& rhs){ return cmp(lhs,rhs) >= 0; }

// returns 1 if (p, q, r) is ccw, 0 if collinear, -1 if cw.
inline int orientation(const Point &p, const Point &q, const Point &r) {
    long det = (long) (q.x() - p.x()) * (long) (r.y() - q.y()) - (long) (q.y() - p.y()) * (long) (r.x() - q.x());
    if (det > 0) 
        return 1;
    else if (det == 0) 
        return 0;
    else 
        return -1;
}
#endif