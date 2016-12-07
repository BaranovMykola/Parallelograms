#include "mainwindow.h"

void MainWindow::resetProgresBar()const
{   //set PRogressBar to 0
    start->setEnabled(true);
    progres->setEnabled(false);
    progres->setValue(0);
}

QString MainWindow::getTextAutomaticButton()
{   //gives text for button
    //return dynamicText[dynamicTextIndex++%dynamicTextQuantity];
    return "Auto";
}

void MainWindow::drawBorder(QPixmap& pixmap)
{   //draw border in mainPanel
    pixmap.fill(QColor("white"));
    QPainter painter(&pixmap);
    QPen brush(QColor("#000000"));
    brush.setWidth(borderWidth);
    painter.setPen(brush);
    painter.drawLine(-deltaBorder, 0, -deltaBorder, mainPanel->width());
    painter.drawLine(0, 0, mainPanel->height(), 0);
    painter.drawLine(0, mainPanel->width()+deltaBorder, mainPanel->height(), mainPanel->width()+deltaBorder);//botton
    painter.drawLine(mainPanel->height()-deltaBorder, 0, mainPanel->height()-deltaBorder, mainPanel->width());//right
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      current(0),
      firstRandom(0),
      isAutomaticChange(false),
      dynamicTextIndex(0)
{
    srand(time(0));
//Layouts and objects:
    info = new QLabel(this);
    info->setText("Set quantity of parallelograms");
    input = new QLineEdit(this);
    generate = new QPushButton("Generate", this);

    top = new QHBoxLayout;
    top->addWidget(info);
    top->addWidget(input);
    top->addWidget(generate);

    lst = new QComboBox(this);
    mainPanel = new QLabel(this);
    mainPanel->resize(max_lenght*k+xAngle+borderWidth*2, max_lenght*k+xAngle+deltaBorder+borderWidth*2);

    QPixmap pixmap(mainPanel->width(), mainPanel->height());
    drawBorder(pixmap);
    mainPanel->setPixmap(pixmap);

    automatic = new QPushButton(getTextAutomaticButton(), this);
    start = new QPushButton("Transform", this);
    statusRes = new QLabel("Resistibility", this);
    resis = new QLabel(this);

    buttonsBar = new QHBoxLayout;
    middle = new QVBoxLayout();
    middle->addWidget(lst);
    middle->addWidget(mainPanel);
    buttonsBar->addWidget(start);
    buttonsBar->addWidget(automatic);
    buttonsBar->addWidget(statusRes);
    buttonsBar->addWidget(resis);

    frequencyAuto = new QSlider(Qt::Horizontal, this);
    frequencyAuto->setRange(0, maxFrequencyPosition);
    frequencyAuto->setValue(startFrequencyPosition);
    progres = new QProgressBar(this);
    progres->setRange(0,0);
    progres->setEnabled(false);
    progres->setValue(0);

    bottom = new QHBoxLayout;
    bottom->addWidget(frequencyAuto);
    bottom->addWidget(progres);

    all = new QVBoxLayout();
    all->addLayout(top);
    all->addLayout(middle);
    all->addLayout(buttonsBar);
    all->addLayout(bottom);

    setLayout(all);

//connect:
    connect(generate, &QPushButton::clicked, this, &MainWindow::generatShapes);
    connect(lst, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &MainWindow::drawShape);
    connect(start, &QPushButton::clicked, this, &MainWindow::changeSape);
    connect(automatic, &QPushButton::clicked, this, &MainWindow::autoChangeShape);

}

MainWindow::~MainWindow()
{   //all objects will been destroyed as a children
    delete top;
    delete bottom;
    delete buttonsBar;
    delete middle;
    delete all;
}

void MainWindow::updateResistibility()
{   //show resistibility for current shape
    char _ch[16];
    itoa(data[current].getResistibility(), _ch, 10);
    resis->setText(_ch);
}

void MainWindow::delay(double sec)
{   //make delay for second
    QTime dieTime= QTime::currentTime().addMSecs(sec*1000);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::drawShape(int shape)
{   //draw shape
    current = shape;
    updateResistibility();
    Parallelogram S = data[shape];
//gets shape size:
    int ShapeWidth = S.getPiece(0).lenght;
    int ShapeHeight = S.getPiece(1).lenght;

//gets margins:
    int marginLeft = (mainPanel->width()-ShapeWidth*k+xAngle)/2;
    int marginTop = (mainPanel->height()-ShapeHeight*k)/2;

//make poins:
    QPoint marks[4];
    enum POINT{A,B,C,D};
    marks[A] = QPoint(marginLeft, marginTop);
    marks[B] = QPoint(marks[A].x()+ShapeWidth*k, marks[A].y());
    marks[C] = QPoint(marks[B].x()-xAngle, marks[B].y()+ShapeHeight*k);
    marks[D] = QPoint(marks[A].x()-xAngle, marks[A].y()+ShapeHeight*k);

//make field to draw
    QPixmap pixmap(mainPanel->width(),mainPanel->height());
    pixmap.fill(QColor("white"));
    drawBorder(pixmap);
    QPainter painter(&pixmap);

//draw line from point to point with different color in order to shape
    for(int i=0;i<sides;++i)
    {
        QPen brush = brushes[S.getPiece(i).type];
        brush.setWidth(penWeight);
        painter.setPen(brush);
        painter.drawLine(marks[i], marks[(i+1)%sides]);
    }
    mainPanel->setPixmap(pixmap);//save picture
}

void MainWindow::generatShapes()
{   //generates n shapes
    int quantity;
    QString text = input->text();
    quantity = text.toInt();
    for(int i =0;i<quantity;++i)
    {
        data.push_back(Parallelogram(true));
        char _ch[16];
        itoa(data.size()-1, _ch, 10);
        lst->addItem(_ch);
    }

//partitions by monohrome type:
    auto last = stable_partition(data.begin(), data.end(), [](Parallelogram val){return val.getType();});

//Write first random shape (in order to colors):
    char _ch[16];
    firstRandom = distance(data.begin(), last);
    itoa(firstRandom, _ch, 10);
    resis->setText(_ch);
    char show[60] = "First random: ";
    strcat(show, _ch);
    resis->setText(show);

}

void MainWindow::changeSape()
{   //makes monohrome current shape
    isAutomaticChange = !isAutomaticChange;//don't let use more than two funtions in a same time
    automatic->setText(getTextAutomaticButton());
    while (!data[current].getType())
    {
        if(!isAutomaticChange)//if there are active function
        {
            isAutomaticChange = !isAutomaticChange;
            automatic->setText(getTextAutomaticButton());
            return ;//stop this and other function
        }
        data[current].tryMonohrome();
        drawShape(current);
        updateResistibility();
        delay(static_cast<double>(frequencyAuto->value())/(frequencyAuto->maximum()/maxIntervalTime));
    }
    automatic->setText(getTextAutomaticButton());
}

void MainWindow::autoChangeShape()
{   //makes monohrome all shapes
    automatic->setText(getTextAutomaticButton());
    isAutomaticChange = !isAutomaticChange;//don't let use more than two funtions in a same time
    start->setEnabled(false);
    progres->setEnabled(true);
    progres->setRange(0, data.size()-firstRandom-1);// range of nonmonohrome shapes
    int startPosition = firstRandom;
    for(;firstRandom<data.size();++firstRandom)
    {
        while(!data[firstRandom].getType())
        {
            if(!isAutomaticChange)//if there are active function
            {
                isAutomaticChange = !isAutomaticChange;
                resetProgresBar();
                return ;//stop this and other function
            }
            data[firstRandom].tryMonohrome();
            drawShape(firstRandom);
            delay(static_cast<double>(frequencyAuto->value())/(frequencyAuto->maximum()/maxIntervalTime));
        }
        progres->setValue(firstRandom-startPosition);// index of current shape in a current range (see bellow)
    }
    resetProgresBar();
    automatic->setText(getTextAutomaticButton());
}
