#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <list>
#include "class.h"

using namespace std;

static Shape* shapeList[500000];

class Solve {
public:
    int num;
    int cnt;
    set<pair<double, double>> interSet;

    Solve(int num);
    int getSolve();
    void addShape(Shape* s);
    void getIntersect(Shape* s1, Shape* s2, set<pair<double, double>>* interSet);
    void LLintersect(Line* l1, Line* l2, set<pair<double, double>>* interSet);
    void CCintersect(Circle* c1, Circle* c2, set<pair<double, double>>* interSet);
    void CLintersect(Circle* c1, Line* l2, set<pair<double, double>>* interSet);
    
    bool checkXRange(Line *l, pair<double, double> intersect);  //检查算出交点的x在不在线段/射线横坐标范围内
    bool checkYRange(Line *l, pair<double, double> intersect);  //检查算出交点的y在不在线段/射线纵坐标范围内
};

Solve::Solve(int num) {
    this->num = num;
    cnt = 0;
}

int Solve::getSolve() {
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            getIntersect(shapeList[i], shapeList[j], &interSet);
        }
    }
    return (int)interSet.size();
}

void Solve::addShape(Shape* s) {
    shapeList[cnt++] = s;
}

void Solve::getIntersect(Shape* s1, Shape* s2, set<pair<double, double>>* interSet) {   //计算两图形的交点
    char t1, t2;
    t1 = s1->type;
    t2 = s2->type;
    if (t1 == 'L' && t2 == 'L') {   //求两线的交点
        LLintersect((Line*)s1, (Line*)s2, interSet);
    }
    else if (t1 == 'C' && t2 == 'C') {  //求两圆的交点
        CCintersect((Circle*)s1, (Circle*)s2, interSet);
    }
    else {  //求线与圆的交点
        if (s1->type == 'L' && s2->type == 'C') {
            CLintersect((Circle*)s2, (Line*)s1, interSet);
        }
        else if (s1->type == 'C' && s2->type == 'L') {
            CLintersect((Circle*)s1, (Line*)s2, interSet);
        }
        else {
            cout << "something goes wrong!" << endl;
        }
    }
}

void Solve::LLintersect(Line* l1, Line* l2, set<pair<double, double>>* interSet) {
    double a1 = (double)l1->y1 - l1->y2;
    double b1 = (double)l1->x2 - l1->x1;
    double c1 = (double)l1->x1 * l1->y2 - (double)l1->x2 * l1->y1;  //l1: a1x + b1y + c1 = 0
    double a2 = (double)l2->y1 - l2->y2;
    double b2 = (double)l2->x2 - l2->x1;
    double c2 = (double)l2->x1 * l2->y2 - (double)l2->x2 * l2->y1;  //l2: a2x + b2y + c2 = 0
    double d = a1 * b2 - a2 * b1;
    if (d == 0) {   //d == 0时两直线平行
        return;
    }
    else {
        double x = (b1 * c2 - b2 * c1) / d;
        double y = (a2 * c1 - a1 * c2) / d;
        if (checkXRange(l1, pair<double, double>(x, y)) && checkXRange(l2, pair<double, double>(x, y))) {
            (*interSet).insert(pair<double, double>(x, y));
        }
        return;
    }
}

void Solve::CCintersect(Circle* c1, Circle* c2, set<pair<double, double>>* interSet) {
    double a1 = c1->x;
    double b1 = c1->y;
    double r1 = c1->r;
    double a2 = c2->x;
    double b2 = c2->y;
    double r2 = c2->r;
    if ((pow((a1 - a2), 2) + pow((b1 - b2), 2)) > pow(r1 + r2, 2)) {
        return; //两圆不相交
    }
    else {
        double value1 = a1 * a1 - 2 * a1 * a2 + a2 * a2 + b1 * b1 - 2 * b1 * b2 + b2 * b2;
        double value2 = -r1 * r1 * a1 + r1 * r1 * a2 + r2 * r2 * a1 - r2 * r2 * a2 + a1 * a1 * a1 - a1 * a1 * a2 - a1 * a2 * a2 + a1 * b1 * b1 - 2 * a1 * b1 * b2 + a1 * b2 * b2 + a2 * a2 * a2 + a2 * b1 * b1 - 2 * a2 * b1 * b2 + a2 * b2 * b2;
        double value3 = -r1 * r1 * b1 + r1 * r1 * b2 + r2 * r2 * b1 - r2 * r2 * b2 + a1 * a1 * b1 + a1 * a1 * b2 - 2 * a1 * a2 * b1 - 2 * a1 * a2 * b2 + a2 * a2 * b1 + a2 * a2 * b2 + b1 * b1 * b1 - b1 * b1 * b2 - b1 * b2 * b2 + b2 * b2 * b2;
        double sigma = sqrt((r1 * r1 + 2 * r1 * r2 + r2 * r2 - a1 * a1 + 2 * a1 * a2 - a2 * a2 - b1 * b1 + 2 * b1 * b2 - b2 * b2) * (-r1 * r1 + 2 * r1 * r2 - r2 * r2 + value1));

        double p1_x = (value2 - sigma * b1 + sigma * b2) / (2 * value1);
        double p2_x = (value2 + sigma * b1 - sigma * b2) / (2 * value1);
        double p1_y = (value3 + sigma * a1 - sigma * a2) / (2 * value1);
        double p2_y = (value3 - sigma * a1 + sigma * a2) / (2 * value1);

        (*interSet).insert(pair<double, double>(p1_x, p1_y));
        (*interSet).insert(pair<double, double>(p2_x, p2_y));
        return;
    }
}

void Solve::CLintersect(Circle* circle1, Line* line2, set<pair<double, double>>* interSet) {
    double a = circle1->x;
    double b = circle1->y;
    double r = circle1->r;
    double a1 = (double)line2->y1 - line2->y2;
    double b1 = (double)line2->x2 - line2->x1;
    double c1 = (double)line2->x1 * line2->y2 - (double)line2->x2 * line2->y1;  //l2: a1x + b1y + c1 = 0

    double d = abs((a1 * a + b1 * b + c1) / sqrt(a1 * a1 + b1 * b1));
    if (d > r) {    //圆与直线不相交
        return;
    }
    else {
        if (a1 == 0) {
            double y = -c1 / b1;
            double p1_x = sqrt(r * r - (y - b) * (y - b)) + a;
            double p2_x = -sqrt(r * r - (y - b) * (y - b)) + a;
            if (checkXRange(line2, pair<double, double>(p1_x, y))) {
                (*interSet).insert(pair<double, double>(p1_x, y));
            }
            if (checkXRange(line2, pair<double, double>(p2_x, y))) {
                (*interSet).insert(pair<double, double>(p2_x, y));
            }
        }
        else {
            double delta = sqrt(-a * a * a1 * a1 - 2 * a * a1 * b * b1 - 2 * a * a1 * c1 + a1 * a1 * r * r - b * b * b1 * b1 - 2 * b * b1 * c1 + b1 * b1 * r * r - c1 * c1);
            double value1 = - a1 * a1 * b + a * a1 * b1;
            double value2 = a1 * a1 + b1 * b1;

            double p1_x = -(c1 - (b1 * (b1 * c1 + a1 * delta + value1)) / (value2)) / a1;
            double p2_x = -(c1 - (b1 * (b1 * c1 - a1 * delta + value1)) / (value2)) / a1;
            double p1_y = -(b1 * c1 + a1 * delta + value1) / (value2);
            double p2_y = -(b1 * c1 - a1 * delta + value1) / (value2);
            if (checkXRange(line2, pair<double, double>(p1_x, p1_y))) {
                (*interSet).insert(pair<double, double>(p1_x, p1_y));
            }
            if (checkXRange(line2, pair<double, double>(p2_x, p2_y))) {
                (*interSet).insert(pair<double, double>(p2_x, p2_y));
            }
        }
        return;
    }
}

bool Solve:: checkXRange(Line *l, pair<double, double> intersect) {
    if (l->x1 == l->x2) {   //垂直于x轴的直线，这种情况不能用x判断
        return checkYRange(l, intersect);
    }
    char subtype = l->subtype;
    if (subtype == 'L') {   //l是直线，无需检查
        return true;
    }
    else if (subtype == 'R') {  //l是射线
        if (l->x1 < l->x2) {
            if (intersect.first >= l->x1) {
                return true;
            }
        }
        else {
            if (intersect.first <= l->x1) {
                return true;
            }
        }
    }
    else {  //l是线段
        if (intersect.first <= l->xmax && intersect.first >= l->xmin) {
            return true;
        }
    }
    return false;
}

bool Solve:: checkYRange(Line *l, pair<double, double> intersect) {
    char subtype = l->subtype;
    if (subtype == 'L') {   //l是直线，无需检查
        return true;
    }
    else if (subtype == 'R') {  //l是射线
        if (l->y1 < l->y2) {
            if (intersect.second >= l->y1) {
                return true;
            }
        }
        else {
            if (intersect.second <= l->y1) {
                return true;
            }
        }
    }
    else {  //l是线段
        if (intersect.second <= l->ymax && intersect.second >= l->ymin) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char* argv[]) {
    //ifstream fin(argv[2], ios::in);
    //ofstream fout(argv[4], ios::out);
    int num = 0;
    cin >> num;
    Solve* sol = new Solve(num);
    for (int i = 0; i < num; i++) {
        char type;
        cin >> type;
        if (type == 'L' || type == 'R' || type == 'S') {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Line* newline = new Line(type, x1, y1, x2, y2);
            sol->addShape(newline);
        }
        else {
            int x, y, r;
            cin >> x >> y >> r;
            Circle* newcircle = new Circle(x, y, r);
            sol->addShape(newcircle);
        }
    }

    cout << sol->getSolve() << endl;

    //fin.close();
    //fout.close();
    return 0;
}

