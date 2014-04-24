#include "widget.h"
#include "ui_widget.h"
#include <QGlobal.h>
#include <QTime>
//VirtualBox 08:00:27
//VMware     00:50:56
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTime time = QTime::currentTime();

    qsrand((uint)time.msec());

    int randomValue = randInt(0,255);
    QString txt = QString::number( randomValue, 16 ).toUpper();
    randomValue = randInt(0,255);
    txt += ":"+QString::number( randomValue, 16 ).toUpper();
    if (testVirtual()){
        ui->plainTextEdit->insertPlainText("Virtual Machine\n");
    }else{
        GetInterface();
    }
}
Widget::~Widget()
{
    delete ui;
}
bool Widget::testVirtual()
{
    bool virMachin = false;
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < ifaces.count();i++)
    {
        QString mac = ifaces.at(i).hardwareAddress();
        QString mn = ifaces.at(i).humanReadableName();

        unsigned int flags = ifaces.at(i).flags();
        bool isLoopback = (bool)(flags & QNetworkInterface::IsLoopBack);
        bool isRunning = (bool)(flags & QNetworkInterface::IsRunning);

        if ( !ifaces[i].isValid() || isLoopback ) continue;
        if (isRunning)
        {
            if (mac.mid(0,8) == "08:00:27")
                virMachin = true;
            else if (mac.mid(0,8) == "00:50:56")
                virMachin = true;
            else{
                virMachin = false;
                break;
            }
        }
    }
    return virMachin;
}
void Widget::GetInterface()
{
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    for (int i = 0; i < ifaces.count();i++)
    {
        QString mac = ifaces.at(i).hardwareAddress();
        QString mn = ifaces.at(i).humanReadableName();

        unsigned int flags = ifaces.at(i).flags();
        bool isLoopback = (bool)(flags & QNetworkInterface::IsLoopBack);
        bool CanMulticast = (bool)(flags & QNetworkInterface::CanMulticast);
        bool isP2P = (bool)(flags & QNetworkInterface::IsPointToPoint);

        if ( !ifaces[i].isValid() || isLoopback ) continue;
        if (mac.mid(0,8) == "08:00:27") continue;
        if (mac.mid(0,8) == "00:50:56") continue;
        if (CanMulticast)
        {
            ui->plainTextEdit->insertPlainText(mn+"\n");
            ui->plainTextEdit_2->insertPlainText(mac+"\n");
            ui->plainTextEdit_3->insertPlainText(QString::number(flags)+"\n");
        }
    }
}

int Widget::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}
