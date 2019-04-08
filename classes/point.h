#include <ostream>

class Point {
public:
    Point(int x = 0, int y = 0) 
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
int cmp(const Point &lhs, const Point &rhs) {
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

