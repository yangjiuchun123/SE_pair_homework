#include "UI.h"
#include <QtGui>
#include <QPaintEvent>
#include <QHBoxLayout>
#include "pch.h"
#pragma comment(lib,"core.lib")

Solve* sol = new Solve(10000);
calculate::calculate(QWidget* parent) :QDialog(parent)
{
    setFixedSize(1000, 300);
    getAddress = new QPushButton(tr("get Address"), this);
    del = new QPushButton(tr("delete number"), this);
    delnum = new QLineEdit(this);
    add = new QPushButton(tr("add obj"), this);
    info = new QLineEdit(this);
    num = new QPushButton(tr("number of intersets"), this);
    img = new QPushButton(tr("img"), this);
    result = new QLineEdit(this);
    QHBoxLayout* mainLayout = new QHBoxLayout();
    //QString input = delnum->text();
    mainLayout->addWidget(getAddress);
    mainLayout->addWidget(img);
    mainLayout->addWidget(del);
    mainLayout->addWidget(delnum);
    mainLayout->addWidget(add);
    mainLayout->addWidget(info);
    mainLayout->addWidget(num);
    mainLayout->addWidget(result);
    setLayout(mainLayout);
    connect(getAddress, SIGNAL(clicked()), this, SLOT(getFile()));
    connect(del, SIGNAL(clicked()), this, SLOT(removeObj()));
    connect(add, SIGNAL(clicked()), this, SLOT(addObj()));
    connect(num, SIGNAL(clicked()), this, SLOT(showResult()));
    connect(img, SIGNAL(clicked()), this, SLOT(showImg()));
}

void input(QString fileName) {
    string name = fileName.toStdString();
    string buffer;
    char type;
    int x1, y1, x2, y2, x, y, r;
    ifstream infile;
    infile.open(name);
    if (infile.eof()) {
        return;
    }
    getline(infile, buffer);
    int n = stoi(buffer);
    int i = 0;
    while (i < n) {
        getline(infile, buffer);
        if (buffer[0] == 'C') {
            if (sscanf(buffer.c_str(), "%c %d %d %d", &type, &x, &y, &r) == NULL) {
                return;
            }
            Circle* newcircle = new Circle(x, y, r);
            sol->addShape(newcircle);
        }
        else {
            if (sscanf(buffer.c_str(), "%c %d %d %d %d", &type, &x1, &y1, &x2, &y2) == NULL) {
                return;
            }
            Line* newline = new Line(type, x1, y1, x2, y2);
            sol->addShape(newline);
        }
        i++;
    }
}

void calculate::getFile() {
    QFileDialog* fileDialog = new QFileDialog(); 
    fileDialog->setWindowTitle("open picture");
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter("Text file(*.txt)");
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QString fileName;
    if (fileDialog->exec())
    {
        fileName = fileDialog->getOpenFileName();
    }
    this->Filename = fileName;
    input(this->Filename);
    //qDebug() << fileName << endl;
}

void calculate::removeObj() {
    QString input = delnum->text();
    int temp = input.toInt();
    sol->removeList(temp);
}

void calculate::addObj() {
    QString input = info->text();
    string information = input.toStdString();
    char type;
    int x1, y1, x2, y2, x, y, r;
    if (information[0] == 'C') {
        if (sscanf(information.c_str(), "%c %d %d %d", &type, &x, &y, &r) == NULL) {
            return;
        }
        Circle* newcircle = new Circle(x, y, r);
        sol->addShape(newcircle);
    }
    else {
        if (sscanf(information.c_str(), "%c %d %d %d %d", &type, &x1, &y1, &x2, &y2) == NULL) {
            return;
        }
        Line* newline = new Line(type, x1, y1, x2, y2);
        sol->addShape(newline);
    }
}

void calculate::showResult() {
    result->setText(QString::number(sol->getSolve()));
}


void calculate::showImg() {
    picture *img = new picture();
    img->show();
    //QDialog* d = new QDialog();
    //d->show();
}

picture::picture(QWidget* parent) :QDialog(parent) {
    setFixedSize(1000, 1000);
}

void picture::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.translate(500, 500);
    painter.setPen(Qt::black);
    painter.drawText(490, -10, "x");
    painter.drawText(10, -490, "y");
    painter.drawText(10, -10, "o");
    painter.drawLine(-500,0 ,500 , 0);
    painter.drawLine(0, 500, 0, -500);
    painter.drawLine(495, 5, 500, 0);
    painter.drawLine(495, -5, 500, 0);
    painter.drawLine(0, -500, 5, -495);
    painter.drawLine(0, -500, -5, -495);
    list<Shape*> llist = sol->getList();
    list<Shape*>::iterator it;
    int x1, x2, y1, y2, x, y, r;
    for (it = llist.begin(); it != llist.end(); it++) {
        if ((*it)->getType() == 'C') {
            x = (((Circle*)(*it))->getX())*100;
            y = (((Circle*)(*it))->getY())*100;
            r = (((Circle*)(*it))->getR())*100;
            painter.drawEllipse(x, -y, 2 * r, 2 * r);
        }
        else {
            x1 = (((Line*)(*it))->getX1())*100;
            y1 = (((Line*)(*it))->getY1())*100;
            x2 = (((Line*)(*it))->getX2())*100;
            y2 = (((Line*)(*it))->getY2())*100;
            painter.drawLine(x1, -y1, x2, -y2);
            if (((Line*)(*it))->getSubtype() == 'L') {//直线
                painter.drawText(((double)x1+x2)/2, -((double)y1 + y2) / 2,"L");
            }
            else if (((Line*)(*it))->getSubtype() == 'R') {//射线
                painter.drawText(x1, -y1,"R");
            }
            else {//线段
                painter.drawText(((double)x1 + x2) / 2, -((double)y1 + y2) / 2, "S");
            }
        }
    }
}