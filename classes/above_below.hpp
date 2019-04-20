/*
 * Class AboveBelow stores segments below and above of each color.
 */ 
#ifndef ABOVE_BELOW
#define ABOVE_BELOW

#include "segment.hpp"
#include <iostream>

class AboveBelow {
public:
    AboveBelow() {}; // default constructor

    AboveBelow(Segment same_above, Segment same_below, Segment opposite_above, Segment opposite_below) 
        : same_above_(same_above), same_below_(same_below), opposite_above_(opposite_above_), opposite_below_(opposite_below)
    {
    }

    Segment same_above() const {
        return same_above_;
    }

    Segment same_below() const {
        return same_below_;
    }

    Segment opposite_above() const {
        return opposite_above_;
    }

    Segment opposite_below() const {
        return opposite_below_;
    }

    // stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const AboveBelow& s) {
        os  << "{\n\t" << s.same_above_ << ", " 
            << "\n\t" << s.same_below_ << ", " 
            << "\n\t" << s.opposite_above_ << ", " 
            << "\n\t" << s.opposite_below_ << "\n}";
        return os;
    }

private:
    Segment same_above_; 
    Segment same_below_;
    Segment opposite_above_;
    Segment opposite_below_;

};
#endif