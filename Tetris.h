#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <QDialog>
#include <vector>
#include <QtWidgets/QApplication>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QFileDialog>
#include <QTimer>
#include <QColor>
#include <QKeyEvent>
#include "Gamemanger.h"

#define map_width 16
#define map_height 32
class Tetris : public QWidget
{
    Q_OBJECT

public:
    Tetris(QWidget *parent = nullptr);
    ~Tetris();
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);
    bool land();
    bool arrive();
    void checkLine();

private:
    int map[map_height][map_width];
    QTimer* timer;
    block* now_block;
    int num;
};
