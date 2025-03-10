#ifndef STARTINGWINDOW_H
#define STARTINGWINDOW_H

#include <QWidget>

namespace Ui {
class StartingWindow;
}

class StartingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartingWindow(QWidget *parent = nullptr);
    ~StartingWindow();

private:
    Ui::StartingWindow *ui;

private slots:
    void on_start_button_clicked();
};

#endif // STARTINGWINDOW_H
