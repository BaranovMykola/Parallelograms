#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clickedlabel.h"
#include "parallelogram.h"

#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <memory>
#include <cmath>

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <algorithm>
#include <QDebug>
#include <QPen>
#include <QPoint>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <QSlider>
#include <QProgressBar>
#include <QString>
#include <QApplication>
#include <QDesktopWidget>

using std::vector;
const int xAngle = 100;
const QPoint A(100,10);
const double resolution = 0.5;
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
    int coeficient;

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
