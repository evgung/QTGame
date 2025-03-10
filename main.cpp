#include "mainwindow.h"
#include "startingwindow.h"

#include <iostream>
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartingWindow window;
    window.show();

    return a.exec();
}
