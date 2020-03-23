// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include "exception.h"

using namespace std;

class __declspec(dllexport) Shape {
public:
    char type;
};

class __declspec(dllexport) Line : public Shape {
public:
    char subtype;
    int x1;
    int y1;
    int x2;
    int y2;
    int xmin;   //x1, x2中的较小值
    int xmax;   //x1, x2中的较大值
    int ymin;   //y1, y2中的较小值
    int ymax;   //y1, y2中的较大值
    Line(char subtype, int x1, int y1, int x2, int y2);
    void showLineStatus();

};

Line::Line(char subtype, int x1, int y1, int x2, int y2) {
    this->type = 'L';
    this->subtype = subtype; // L:直线，R:射线，S:线段
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    xmin = min(x1, x2);
    xmax = max(x1, x2);
    ymin = min(y1, y2);
    ymax = max(y1, y2);
    try {
        if (x1 == x2 && y1 == y2) {
            throw TwoSamePointException();
        }
    }
    catch (TwoSamePointException e) {
        cout << e.what() << endl;
        exit(-1);
    };
    try {
        if (x1 >= 100000 || x1 <= -100000) {
            throw PointOutOfRangeException();
        }
        if (x2 >= 100000 || x2 <= -100000) {
            throw PointOutOfRangeException();
        }
        if (y1 >= 100000 || y1 <= -100000) {
            throw PointOutOfRangeException();
        }
        if (y2 >= 100000 || y2 <= -100000) {
            throw PointOutOfRangeException();
        }
    }
    catch (PointOutOfRangeException e) {
        cout << e.what() << endl;
        exit(-1);
    };

}

void Line::showLineStatus() {
    cout << "line gets through: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << endl;
}

class __declspec(dllexport) Circle : public Shape {
public:
    int x;
    int y;
    int r;
    Circle(int x, int y, int r);
    void showCircleStatus();

};

Circle::Circle(int x, int y, int r) {
    type = 'C';
    this->x = x;
    this->y = y;
    this->r = r;
    try {
        if (x >= 100000 || x <= -100000) {
            throw PointOutOfRangeException();
        }
        if (y >= 100000 || y <= -100000) {
            throw PointOutOfRangeException();
        }
    }
    catch (PointOutOfRangeException e) {
        cout << e.what() << endl;
        exit(-1);
    };
}

void Circle::showCircleStatus() {
    cout << "circle center: (" << x << ", " << y << "), radius: " << r << endl;
}

class __declspec(dllexport) Solve {
public:
    int num;
    int cnt;
    list<Shape*> shapeList;
    set<pair<double, double>> interSet;

    Solve(int num);
    int getSolve();
    void addShape(Shape* s);
    void removeShape(); //删除图形，还未实现，得根据UI需求来
    void getIntersect(Shape* s1, Shape* s2, set<pair<double, double>>* interSet);
    void LLintersect(Line* l1, Line* l2, set<pair<double, double>>* interSet);
    void CCintersect(Circle* c1, Circle* c2, set<pair<double, double>>* interSet);
    void CLintersect(Circle* c1, Line* l2, set<pair<double, double>>* interSet);

    bool checkXRange(Line* l, pair<double, double> intersect);  //检查算出交点的x在不在线段/射线横坐标范围内
    bool checkYRange(Line* l, pair<double, double> intersect);  //检查算出交点的y在不在线段/射线纵坐标范围内
    set<pair<double, double>>::iterator getSetIter();   //返回set的迭代器，供UI画交点使用

};

__declspec(dllexport) string trim(const string& str);
#endif //PCH_H
