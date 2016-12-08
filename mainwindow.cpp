#include "mainwindow.h"

void MainWindow::resetProgresBar()const
{   //set PRogressBar to 0
    singleTransformButton->setEnabled(true);
    tranformProgressStatus->setEnabled(false);
    tranformProgressStatus->setValue(0);
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
      currentShape(0),
      firstRandom(0)
{
    srand(time(0));
//Layouts and objects:
    generateInfoText = new QLabel(this);
    generateInfoText->setText("Set quantity of parallelograms");
    numberToGenerate = new QLineEdit(this);
    generateButton = new QPushButton("Generate", this);

    top = new QHBoxLayout;
    top->addWidget(generateInfoText);
    top->addWidget(numberToGenerate);
    top->addWidget(generateButton);

    parallelogramList = new QComboBox(this);
    mainPanel = new QLabel(this);
    mainPanel->resize(max_lenght*k+xAngle+borderWidth*2, max_lenght*k+xAngle+deltaBorder+borderWidth*2);

    QPixmap pixmap(mainPanel->width(), mainPanel->height());
    drawBorder(pixmap);
    mainPanel->setPixmap(pixmap);

    automaticTransformButton = new QPushButton("Auto", this);
    singleTransformButton = new QPushButton("Transform", this);
    resistybilityInfoText = new QLabel("Resistibility", this);
    resistybilityNumber = new QLabel(this);

    buttonsBar = new QHBoxLayout;
    middle = new QVBoxLayout();
    middle->addWidget(parallelogramList);
    middle->addWidget(mainPanel);
    buttonsBar->addWidget(singleTransformButton);
    buttonsBar->addWidget(automaticTransformButton);
    buttonsBar->addWidget(resistybilityInfoText);
    buttonsBar->addWidget(resistybilityNumber);

    frequencyTransform = new QSlider(Qt::Horizontal, this);
    frequencyTransform->setRange(0, maxFrequencyPosition);
    frequencyTransform->setValue(startFrequencyPosition);
    tranformProgressStatus = new QProgressBar(this);
    tranformProgressStatus->setRange(0,0);
    tranformProgressStatus->setEnabled(false);
    tranformProgressStatus->setValue(0);

    bottom = new QHBoxLayout;
    bottom->addWidget(frequencyTransform);
    bottom->addWidget(tranformProgressStatus);

    all = new QVBoxLayout();
    all->addLayout(top);
    all->addLayout(middle);
    all->addLayout(buttonsBar);
    all->addLayout(bottom);

    setLayout(all);

//connect:
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generatShapes);
    connect(parallelogramList, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &MainWindow::drawShape);
    connect(singleTransformButton, &QPushButton::clicked, this, &MainWindow::changeSape);
    connect(automaticTransformButton, &QPushButton::clicked, this, &MainWindow::autoChangeShape);

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
    itoa(data[currentShape].getResistibility(), _ch, 10);
    resistybilityNumber->setText(_ch);
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
    currentShape = shape;
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
    QString text = numberToGenerate->text();
    quantity = text.toInt();
    for(int i =0;i<quantity;++i)
    {
        data.push_back(Parallelogram(true));
        char _ch[16];
        itoa(data.size()-1, _ch, 10);
        parallelogramList->addItem(_ch);
    }

//partitions by monohrome type:
    auto last = stable_partition(data.begin(), data.end(), [](Parallelogram val){return val.getType();});

//Write first random shape (in order to colors):
    char _ch[16];
    firstRandom = distance(data.begin(), last);
    itoa(firstRandom, _ch, 10);
    resistybilityNumber->setText(_ch);
    char show[60] = "First random: ";
    strcat(show, _ch);
    resistybilityNumber->setText(show);

}

void MainWindow::changeSape()
{   //makes monohrome current shape
    if(data.size() == 0)
    {
        return ;
    }
    automaticTransformButton->setEnabled(false);
    singleTransformButton->setEnabled(false);
    while (!data[currentShape].getType())
    {
        data[currentShape].tryMonohrome();
        drawShape(currentShape);
        updateResistibility();
        delay(static_cast<double>(frequencyTransform->value())/(frequencyTransform->maximum()/maxIntervalTime));
    }
    automaticTransformButton->setEnabled(true);
    singleTransformButton->setEnabled(true);
}

void MainWindow::autoChangeShape()
{   //makes monohrome all shapes
    if(data.size() == 0)
    {
        return ;
    }
    automaticTransformButton->setEnabled(false);
    singleTransformButton->setEnabled(false);
    tranformProgressStatus->setEnabled(true);
    tranformProgressStatus->setRange(0, data.size()-firstRandom-1);// range of nonmonohrome shapes
    int startPosition = firstRandom;
    for(;firstRandom<data.size();++firstRandom)
    {
        while(!data[firstRandom].getType())
        {
            data[firstRandom].tryMonohrome();
            drawShape(firstRandom);
            delay(static_cast<double>(frequencyTransform->value())/(frequencyTransform->maximum()/maxIntervalTime));
        }
        tranformProgressStatus->setValue(firstRandom-startPosition);// index of current shape in a current range (see bellow)
    }
    resetProgresBar();
    automaticTransformButton->setEnabled(true);
    singleTransformButton->setEnabled(true);
}
