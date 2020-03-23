#include <iostream>
#include <exception>
using namespace std;

struct WrongFirstLineFormatException : public exception {    //首行输入格式错误
    const char* what() const throw ()
    {
        return "Wrong input format: expect a positive integer in the first line!";
    }
};

struct WrongOtherLineFormatException : public exception {    //其他行输入格式错误
    const char* what() const throw ()
    {
        return "Wrong input format: expect \"L/R/S (integer) (integer) (integer) (integer)\" or \"C (integer) (integer) (integer)\"";
    }
};

struct PointOutOfRangeException : public exception {  //坐标范围超限
    const char* what() const throw ()
    {
        return "Invalid input: point out of range(-100000, 100000)!";
    }
};

struct TwoSamePointException : public exception { //直线的两点重合
    const char* what() const throw ()
    {
        return "Invalid input: you entered two same point for a line!";
    }
};

struct InfinityIntersectionsException : public exception {    //无穷多交点
    const char* what() const throw ()
    {
        return "Error when computing intersections: there are infinity intersections!";
    }
};

