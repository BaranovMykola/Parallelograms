#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <vector>
#include <QLineEdit>
#include <QPushButton>
#include "clickedlabel.h"
#include <QBoxLayout>
#include <algorithm>
#include "parallelogram.h"
#include <QDebug>
#include <QPen>
#include <QPoint>
#include <QTime>
#include <iostream>
#include <iterator>
#include <QCoreApplication>
#include <QEventLoop>
#include <QSlider>
#include <ctime>
#include <QProgressBar>
#include <memory>
#include <QString>
#include <cmath>

using std::vector;

const int k = 30;
const int xAngle = 100;
const QPoint A(100,10);
const QPen brushes[3] = {QColor("#FF0000"), QColor("#00FF00"), QColor("#0000FF")};
const int penWeight = 3;
const double maxIntervalTime = 1;
const unsigned short maxFrequencyPosition = 200;
const unsigned short startFrequencyPosition = 50;
const QString dynamicText[2] = {"Auto", "Stop"};
const int dynamicTextQuantity = 2;
const int borderWidth = 5;
const int deltaBorder = std::floor(borderWidth/2.0)-1;

class MainWindow : public QWidget
{
    Q_OBJECT

    QHBoxLayout* top;
    QVBoxLayout* middle;
    QHBoxLayout* buttonsBar;
    QHBoxLayout* bottom;
    QVBoxLayout* all;

    QLabel* generateInfoText;
    QLabel* resistybilityInfoText;
    QLabel* mainPanel;
    QLabel* resistybilityNumber;

    QPushButton* singleTransformButton;
    QPushButton* generateButton;
    QPushButton* automaticTransformButton;

    QComboBox* parallelogramList;

    QLineEdit* numberToGenerate;

    QProgressBar* tranformProgressStatus;

    QSlider* frequencyTransform;

    vector<Parallelogram> data;
    int currentShape;
    int firstRandom;

    void resetProgresBar()const;
    void drawBorder(QPixmap&);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateResistibility();
    void delay(double);

public slots:
    void drawShape(int);
    void generatShapes();
    void changeSape();
    void autoChangeShape();
};

#endif // MAINWINDOW_H
