#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <QThread>

namespace Ui {
class MainWindow;
}

//class PaintWidget : public QWidget
//{
//    Q_OBJECT
//protected:
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//public:
//    explicit PaintWidget(QWidget *parent = 0);
//    ~PaintWidget();
//private:
//    Ui::PaintWidget *ui;
//};



class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void slot_timer();

private:
    Ui::MainWindow *ui;
};

//class ThreadCamera : public QThread
//{
//    Q_OBJECT
//public:
//    ThreadCamera(MainWindow *mainwin);
//    void run();
//signals:
//    void signalsupdate();
//public slots:
//    void slotsupdate();
//private:
//    MainWindow *w;
//};



#endif // MAINWINDOW_H
