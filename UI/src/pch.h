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
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <list>

using namespace std;

//__declspec(dllexport) list<Shape*> shapeList;

  class __declspec(dllexport) Shape {
public:
	void setType(char c);
	char getType();
private:
	char type;
};

void Shape::setType(char c) {
	type = c;
}

char Shape::getType() {
	return type;
}

 class __declspec(dllexport) Line : public Shape {
public:
	Line(char subtype, int x1, int y1, int x2, int y2);
	void showLineStatus();
	char getSubtype() {
		return subtype;
	}
	int getX1() {
		return x1;
	}
	int getY1() {
		return y1;
	}
	int getX2() {
		return x2;
	}
	int getY2() {
		return y2;
	}
	int getXmin() {
		return xmin;
	}
	int getXmax() {
		return xmax;
	}
	int getYmin() {
		return ymin;
	}
	int getYmax() {
		return ymax;
	}

private:
	char subtype;
	int x1;
	int y1;
	int x2;
	int y2;
	int xmin;   //x1, x2ÖÐµÄ½ÏÐ¡Öµ
	int xmax;   //x1, x2ÖÐµÄ½Ï´óÖµ
	int ymin;   //y1, y2ÖÐµÄ½ÏÐ¡Öµ
	int ymax;   //y1, y2ÖÐµÄ½Ï´óÖµ
};

Line::Line(char subtype, int x1, int y1, int x2, int y2) {
	setType('L');
	this->subtype = subtype; // L:Ö±Ïß£¬R:ÉäÏß£¬S:Ïß¶Î
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

class __declspec(dllexport) Circle : public Shape {
public:
	Circle(int x, int y, int r);
	void showCircleStatus();
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getR() {
		return r;
	}

private:
	int x;
	int y;
	int r;
};

Circle::Circle(int x, int y, int r) {
	setType('C');
	this->x = x;
	this->y = y;
	this->r = r;
}

void Circle::showCircleStatus() {
	cout << "circle center: (" << x << ", " << y << "), radius: " << r << endl;
}

class __declspec(dllexport) Solve {
public:
	Solve(int num);
	int getSolve();
	list<Shape*> getList() {
		return shapeList;
	}
	void removeList(int i) {
		list<Shape*>::iterator it;
		int mark = 1;
		for (it = shapeList.begin(); it != shapeList.end(); it++) {
			if (mark == i) {
				shapeList.erase(it);
				break;
			}
			mark++;
		}
	}
	void addShape(Shape* s);
	void getIntersect(Shape* s1, Shape* s2, set<pair<double, double>>* interSet);
	void LLintersect(Line* l1, Line* l2, set<pair<double, double>>* interSet);
	void CCintersect(Circle* c1, Circle* c2, set<pair<double, double>>* interSet);
	void CLintersect(Circle* c1, Line* l2, set<pair<double, double>>* interSet);

	bool checkXRange(Line* l, pair<double, double> intersect);  //检查算出交点的x在不在线段/射线横坐标范围内
	bool checkYRange(Line* l, pair<double, double> intersect);  //检查算出交点的y在不在线段/射线纵坐标范围内

private:
	int num;
	int cnt;
	list<Shape*> shapeList;
	set<pair<double, double>> interSet;
};

#endif //PCH_H
