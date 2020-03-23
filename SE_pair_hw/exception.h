#include <iostream>
#include <exception>
using namespace std;

struct WrongFirstLineFormatException : public exception {    //���������ʽ����
    const char* what() const throw ()
    {
        return "Wrong input format: expect a positive integer in the first line!";
    }
};

struct WrongOtherLineFormatException : public exception {    //�����������ʽ����
    const char* what() const throw ()
    {
        return "Wrong input format: expect \"L/R/S (integer) (integer) (integer) (integer)\" or \"C (integer) (integer) (integer)\"";
    }
};

struct PointOutOfRangeException : public exception {  //���귶Χ����
    const char* what() const throw ()
    {
        return "Invalid input: point out of range(-100000, 100000)!";
    }
};

struct TwoSamePointException : public exception { //ֱ�ߵ������غ�
    const char* what() const throw ()
    {
        return "Invalid input: you entered two same point for a line!";
    }
};

struct InfinityIntersectionsException : public exception {    //����ཻ��
    const char* what() const throw ()
    {
        return "Error when computing intersections: there are infinity intersections!";
    }
};

