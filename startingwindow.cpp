#include "startingwindow.h"
#include "ui_startingwindow.h"
#include "mainwindow.h"

StartingWindow::StartingWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartingWindow)
{
    ui->setupUi(this);
}

StartingWindow::~StartingWindow()
{
    delete ui;
}

void StartingWindow::on_start_button_clicked()
{
    MainWindow *mainWindow = new MainWindow();

    mainWindow->setParameters(
        ui->number_of_rounds->value(),
        ui->seconds_for_answer->value(),
        ui->shuffle_buttons->isChecked()
    );

    mainWindow->startNewRound();
    mainWindow->show();

    this->close();
}

