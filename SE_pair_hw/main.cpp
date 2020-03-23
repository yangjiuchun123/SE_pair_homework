#include "pch.h"
#include <cmath>
#include <set>
#include <list>
#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#pragma comment(lib,"core.lib")

int main(int argc, const char* argv[]) {
    ifstream fin("input.txt", ios::in);
    ofstream fout("output.txt", ios::out);
    string input_num;
    getline(fin, input_num);
    try {
        if (!regex_match(input_num, regex("\\s*[1-9]\\d*\\s*"))) {
            throw WrongFirstLineFormatException();
        }
    }
    catch (WrongFirstLineFormatException e) {
        fout << e.what() << endl;
        exit(-1);
    }
    int num = stoi(input_num);
    Solve* sol = new Solve(num);
    for (int i = 0; i < num; i++) {
        string input_shape;
        getline(fin, input_shape);
        try {
            if (!regex_match(input_shape, regex("\\s*[LRS]\\s*(-?[0-9]\\d*\\s*){4}"))) {
                if (!regex_match(input_shape, regex("\\s*C\\s*(-?[0-9]\\d*\\s*){3}"))) {
                    throw WrongOtherLineFormatException();
                }
            }
        }
        catch (WrongOtherLineFormatException e) {
            fout << e.what() << endl;
            exit(-1);
        }
        input_shape = trim(input_shape);
        string::size_type pos0 = input_shape.find_first_of(' ');
        char type = input_shape.substr(0, pos0)[0];
        input_shape = trim(input_shape.substr(pos0 + 1));
        if (type == 'L' || type == 'R' || type == 'S') {
            int x1, y1, x2, y2;
            string::size_type pos1 = input_shape.find_first_of(' ');
            x1 = stoi(input_shape.substr(0, pos1));
            input_shape = trim(input_shape.substr(pos1 + 1));
            string::size_type pos2 = input_shape.find_first_of(' ');
            y1 = stoi(input_shape.substr(0, pos2));
            input_shape = trim(input_shape.substr(pos2 + 1));
            string::size_type pos3 = input_shape.find_first_of(' ');
            x2 = stoi(input_shape.substr(0, pos3));
            input_shape = trim(input_shape.substr(pos3 + 1));
            string::size_type pos4 = input_shape.find_first_of(' ');
            y2 = stoi(input_shape.substr(0, pos4));
            Line* newline = new Line(type, x1, y1, x2, y2);
            sol->addShape(newline);
        }
        else {
            int x, y, r;
            string::size_type pos1 = input_shape.find_first_of(' ');
            x = stoi(input_shape.substr(0, pos1));
            input_shape = trim(input_shape.substr(pos1 + 1));
            string::size_type pos2 = input_shape.find_first_of(' ');
            y = stoi(input_shape.substr(0, pos2));
            input_shape = trim(input_shape.substr(pos2 + 1));
            string::size_type pos3 = input_shape.find_first_of(' ');
            r = stoi(input_shape.substr(0, pos3));
            Circle* newcircle = new Circle(x, y, r);
            sol->addShape(newcircle);
        }
    }

    fout << sol->getSolve() << endl;

    //fin.close();
    //fout.close();
    return 0;
}
