#ifndef THREAD
#define THREAD

#include <QThread>
#include "mainwindow.h"

class ThreadCamera : public QThread
{
    Q_OBJECT
public:
    ThreadCamera(MainWindow *mainwin);
    void run();
signals:
    void signalsupdate();
public slots:
    void slotsupdate();
private:
    MainWindow *w;
};


//class ThreadTimer : public QThread
//{
//    Q_OBJECT
//public:
//    ThreadTimer();
//    void run();
//signals:
//    void signalsupdate_timer();
//public slots:
//    void slotsupdate_timer();
//};

#endif // THREAD

