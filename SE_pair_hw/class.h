#include <iostream>

using namespace std;

class Shape {
public:
    char type;
};

class Line : public Shape {
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
}

void Line::showLineStatus() {
    cout << "line gets through: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")" << endl;
}

class Circle : public Shape {
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
}

void Circle::showCircleStatus() {
    cout << "circle center: (" << x << ", " << y << "), radius: " << r << endl;
}
