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
        //��ʱpainter���������Լ��Ļ����ˣ����ǿ�ʼ������������Ҫ�Ȼ�һ���㣬QPainter �������ṩ�˷ḻ�ķ�������һ����void drawPoint(int x, int y)
        painter.drawPoint(100, 100);//
        //tͬ��ֱ��
       // void drawLine(const QPoint &p1,const QPoint $p2)
        painter.drawLine(QPoint(1, 1), QPoint(100, 101));//QPoint����ʲô��������ǳ�ѧ�߰ٶ�QPoint���ٶȴ������ϸ�ĸ�����
    }*/
};
