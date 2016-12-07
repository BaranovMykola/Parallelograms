#include "mainwindow.h"
#include <QApplication>
#include <memory>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    unique_ptr<int> ptr = make_unique<int>(3);
    cout << *ptr << endl;
    return a.exec();
}
