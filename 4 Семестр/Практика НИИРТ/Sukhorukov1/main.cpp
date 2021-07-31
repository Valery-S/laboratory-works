#include <QApplication>
#include <QPushButton>
#include <QBoxLayout>
#include <QGroupBox>

#include "nniirt_style.h"
#include "button_with_window.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QWidget w;
    QWidget second_w;


    QGroupBox gbx("BUTTONS",&w);
    QHBoxLayout * phbxLayout = new QHBoxLayout;

    QPushButton * button1=new QPushButton ("QUIT");
    QPushButton * button2=new QPushButton ("CHECK");
    Button_with_window * button3=new Button_with_window (QString("OPEN WINDOW"),&second_w,&w);
    QPushButton * button4=new QPushButton("CLOSE",&second_w);

    button1->setMinimumSize(120,60);
    button2->setMinimumSize(120,60);
    button3->setMinimumSize(120,60);
    button4->setMinimumSize(120,60);

    button2->setCheckable(true);
    button4->move(20,30);
    QObject::connect(button1,SIGNAL(clicked()),&a,SLOT(quit()));
    QObject::connect(button4,SIGNAL(clicked()),&second_w,SLOT(close()));

    phbxLayout->addWidget(button1);
    phbxLayout->addWidget(button2);
    phbxLayout->addWidget(button3);
    gbx.setLayout(phbxLayout);
    gbx.move(50,100);

    QColor background( 190, 190, 190 );
    w.setAutoFillBackground(true);
    w.setPalette(background);

    w.setMinimumSize(500,300);
    second_w.setMinimumSize(200,200);
    a.setStyle(new NNIIRT_Style());

    w.show();

    return a.exec();
}
