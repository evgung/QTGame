#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "result.h"
#include <algorithm>
#include <vector>
#include <random>

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QButtonGroup>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setParameters(int, int, bool);
    void startNewRound();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    QButtonGroup* buttons;

    int current_round = 0;
    int correct_answers = 0;
    int first, second, third;

    int seconds_to_answer;
    int number_of_rounds;
    bool shuffle_buttons;

    void setRoundText();
    void setRoundEnabled(bool);
    bool compare(int, int, QAbstractButton*);
    void applyAnswer(result);
    void endOfGame();
    void shuffleButtons();

private slots:
    void timeIsUp();
    void on_button_clicked(QAbstractButton*);
};
#endif // MAINWINDOW_H
