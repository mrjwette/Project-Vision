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
    void on_numberplate_clicked();
    void SetHSV(QImage *image, float MaxpixY, float MaxpixX, int h_min, int h_max, int s_min, int s_max, int v_min, int v_max);
    void on_letterDice_clicked();
    void sortOutput();
    void ExportImage(QImage image);

private:
    Ui::MainWindow *ui;
    QString url;
    char maskerChar[35] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char outputChar[6];
    int outputInt[6];
    char output[8];
};

#endif // MAINWINDOW_H
