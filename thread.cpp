#include "thread.h"
#include "camera_basler.h"

using namespace std;

extern int first_frame_flag ;
int frame_count=0;

ThreadCamera::ThreadCamera(MainWindow *mainwin)
{
    this->w = mainwin;
    connect(this,SIGNAL(signalsupdate()),this,SLOT(slotsupdate()));
}


void ThreadCamera::slotsupdate()
{
    //        update
    first_frame_flag = 0;
//                this->ui->centralWidget->update();
//    this->ui->centralWidget->repaint();
    w->centralWidget()->repaint();

    frame_count++;
}


void ThreadCamera::run()
{
   basler_grabbing(this);
}



//ThreadTimer::ThreadTimer()
//{
//    connect(this,SIGNAL(signalsupdate_timer()),this,SLOT(slotsupdate_timer()));
//}
//void ThreadTimer::slotsupdate_timer()
//{
//    cout<<"hi"<<endl;
//}


