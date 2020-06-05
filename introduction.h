#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>

class introduction : public QMainWindow
{
    Q_OBJECT
public:
    explicit introduction(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

signals:
    void chooseBack();
};

#endif // INTRODUCTION_H
