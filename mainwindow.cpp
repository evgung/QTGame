#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand(time(NULL));

    buttons = new QButtonGroup(this);
    buttons->addButton(ui->equal_button);
    buttons->addButton(ui->less_button);
    buttons->addButton(ui->greater_button);
    connect(buttons, SIGNAL(buttonClicked(QAbstractButton*)),
            this, SLOT(on_button_clicked(QAbstractButton*)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
            this, SLOT(timeIsUp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setParameters(int number_of_rounds_to_set, int seconds_for_answer_to_set, bool shuffle_buttons_to_set)
{
    number_of_rounds = number_of_rounds_to_set;
    seconds_to_answer = seconds_for_answer_to_set;
    shuffle_buttons = shuffle_buttons_to_set;
}

void MainWindow::shuffleButtons()
{
    std::vector<std::vector<int>> coordinates = {
        { 160, 170 },
        { 220, 170 },
        { 280, 170 }
    };

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::shuffle(coordinates.begin(), coordinates.end(), generator);

    for (int i = 0; i < 3; i++)
    {
        auto button = buttons->buttons()[i];
        button->move(coordinates[i][0], coordinates[i][1]);
    }
}

void MainWindow::setRoundText()
{
    ui->problem_label->setText(QString::number(first) + " + " + QString::number(second));
    ui->answer_label->setText(QString::number(third));
    ui->round_label->setText(QString("%1 round. Correct answers: %2.")
                                 .arg(QString::number(current_round), QString::number(correct_answers)));
}

void MainWindow::setRoundEnabled(bool isEnabled)
{
    ui->problem_group->setEnabled(isEnabled);
    ui->result_label->setVisible(!isEnabled);
}

void MainWindow::applyAnswer(result res)
{
    setRoundEnabled(false);

    if (res == result::Correct)
    {
        correct_answers++;
        ui->result_label->setText("Correct!");
    }
    else if (res == result::Incorrect)
    {
        ui->result_label->setText("Incorrect!");
    }
    else if (res == result::TimeIsUp)
    {
        ui->result_label->setText("Time is up!");
    }

    QTimer::singleShot(700, [=]() {
        startNewRound(); // Переход к следующему раунду
    });
}

bool MainWindow::compare(int x, int y, QAbstractButton* button)
{
    if (button->text() == "<")
        return x < y;
    else if (button->text() == ">")
        return x > y;
    else
        return x == y;
}

void MainWindow::on_button_clicked(QAbstractButton* button)
{
    if (timer->isActive())
    {
        timer->stop();
    }

    if (compare(first + second, third, button))
    {
        applyAnswer(result::Correct);
    }
    else
    {
        applyAnswer(result::Incorrect);
    }
}

void MainWindow::timeIsUp()
{
    applyAnswer(result::TimeIsUp);
}

void MainWindow::startNewRound()
{
    current_round++;

    if (current_round > number_of_rounds)
    {
        endOfGame();
        return;
    }

    if (shuffle_buttons)
    {
        shuffleButtons();
    }
    setRoundEnabled(true);

    first = rand() % 100 + 1;
    second = rand() % 100 + 1;
    third = rand() % 200 + 1;

    setRoundText();

    // Засекаем время на ответ
    timer->start(seconds_to_answer * 1000);
}

void MainWindow::endOfGame()
{
    QMessageBox::information(nullptr, "Game is over!",
                             QString("You gave %1/%2 correct answers")
                             .arg(QString::number(correct_answers), QString::number(number_of_rounds)));
}
