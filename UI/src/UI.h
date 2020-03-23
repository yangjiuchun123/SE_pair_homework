#include <QtWidgets/QApplication>
#include <QFileDialog>
#include <iostream>
#include <QDialog>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlist.h>
#include <qlineedit.h>
#include <QPainter>
#include <QPen>

class calculate :public QDialog {
    Q_OBJECT
public:
    calculate(QWidget* parent = 0);
signals:

private slots:
    void getFile();
    void removeObj();
    void addObj();
    void showResult();
    void showImg();
    
private:
    QString Filename;
    QPushButton* getAddress;
    QPushButton* num;
    QPushButton* del;
    QPushButton* add;
    QPushButton* img;
    QLineEdit* info;
    QLineEdit* delnum;
    QLineEdit* result;
};

class picture :public QDialog {
public:
    picture(QWidget* parent = 0);

private:
    void paintEvent(QPaintEvent*);/* {
        QPainter painter(this);
        //此时painter就是我们自己的画笔了，我们开始画画，现在我要先画一个点，QPainter 给我们提供了丰富的方法，画一个点void drawPoint(int x, int y)
        painter.drawPoint(100, 100);//
        //t同理直线
       // void drawLine(const QPoint &p1,const QPoint $p2)
        painter.drawLine(QPoint(1, 1), QPoint(100, 101));//QPoint代表什么，如果你是初学者百度QPoint，百度大神会详细的告诉你
    }*/
};
