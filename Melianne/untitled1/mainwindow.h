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

private slots:
    void SetHSV(QImage*, float, float, int, int, int, int, int, int, int*, int*, int*, int*);
    void on_numberplate_clicked();
    void on_letterDice_clicked();
    void loadMasks(int);
    int compareWithMasks(QImage);

private:
    Ui::MainWindow *ui;
    QString url;

    QPixmap maskers[36];
    char maskerChar[36] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-'};
    char output[7];
};

#endif // MAINWINDOW_H
