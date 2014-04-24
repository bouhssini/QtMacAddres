#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkInterface>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool testVirtual();
    void GetInterface();
    int randInt(int low, int high);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
