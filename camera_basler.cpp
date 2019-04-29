#include <QApplication>
#include <QTime>
#include <pylon/PylonIncludes.h>
#include "thread.h"
using namespace Pylon;
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;

int first_frame_flag = 1;
int time_process = 0;
uint8_t *pImageBuffer = new uint8_t[640*480*3];
Mat edge;

void basler_grabbing(ThreadCamera *tc)
{
    // Before using any pylon methods, the pylon runtime must be initialized.
    PylonInitialize();
    try
    {
        // Create an instant camera object with the camera device found first.
        CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());

        // Print the model name of the camera.
        cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera.MaxNumBuffer = 5;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        camera.StartGrabbing( );
//        camera.StartGrabbing( c_countOfImagesToGrab);

        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;

        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while ( camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);



            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
//                cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
//                cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
//                const uint8_t *pImageBuffer = (uint8_t *) ptrGrabResult->GetBuffer();
                CImageFormatConverter formatconverter;
                formatconverter.OutputPixelFormat=PixelType_RGB8packed;
                CPylonImage pylonImage;
                formatconverter.Convert(pylonImage,ptrGrabResult);
//                pImageBuffer = (uint8_t *) pylonImage.GetBuffer();
                memcpy(pImageBuffer , pylonImage.GetBuffer(),sizeof(uint8_t)*640*480*3);

                //opencv process
                QTime time_p;
                time_p.start();
                Mat srcImage = Mat(cv::Size(640,480),CV_8UC3,pImageBuffer);
                Mat grayImage;
                cvtColor(srcImage,grayImage,CV_BGR2GRAY);
                blur(grayImage,edge,Size(3,3));
                Canny(edge,edge,3,9,3);
                time_process = time_p.elapsed();
                //                cv:: imwrite("1.jpg",mat);

//                update
                 emit  tc->signalsupdate();
//                first_frame_flag = 0;
//                this->ui->centralWidget->update();
//                this->ui->centralWidget->repaint();


//                QImage qimg;
//                qimg = QImage((const unsigned char*)(pImageBuffer),640,480,QImage::Format_RGB888);
//                qimg.save("2.jpg","JPG");


                //save img
//                CImageFormatConverter formatconverter;
//                formatconverter.OutputPixelFormat=PixelType_RGB8packed;
//                CPylonImage pylonImage;
//                formatconverter.Convert(pylonImage,ptrGrabResult);
//                int temp = pylonImage.GetPixelType();
//                pylonImage.Save(ImageFileFormat_Png,"1.png");


//                cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << endl << endl;
//                cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[1] << endl << endl;
//                cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[2] << endl << endl;
            }
            else
            {
                cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
            }
        }
    }
    catch (const GenericException &e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;
//        exitCode = 1;
    }
    // Releases all pylon resources.
    PylonTerminate();
}
