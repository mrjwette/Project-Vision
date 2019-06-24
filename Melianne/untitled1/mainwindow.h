#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetHSV(QImage*, float, float, int, int, int, int, int, int);
private slots:
    void on_numberplate_clicked();
    void on_letterDice_clicked();
    void sortOutput();
private:
    Ui::MainWindow *ui;
    QString url;
    char maskerChar[36] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
    char outputChar[6] = {'V', '8', 'Z', '2','8','P'};
    int outputInt[6] = {44,165,73,111,138,209};
    char output[8];
};

#endif // MAINWINDOW_H
