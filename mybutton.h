#ifndef BUTTON_START_H
#define BUTTON_START_H

#include <QWidget>
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString pix);
    void zoomdown();
    void zoomup();

signals:

};

#endif // BUTTON_START_H
