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
private:
    Ui::MainWindow *ui;
    QString url;
};

#endif // MAINWINDOW_H
