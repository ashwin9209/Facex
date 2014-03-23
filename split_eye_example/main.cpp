#include <QCoreApplication>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>

using namespace std;
using namespace cv;

static void help()
{
    cout << "\nThis program demonstrates the cascade recognizer. Now you can use Haar or LBP features.\n"
            "This classifier can recognize many kinds of rigid objects, once the appropriate classifier is trained.\n"
            "It's most known use is for faces.\n"
            "Usage:\n"
            "./facedetect [--cascade=<cascade_path> this is the primary trained classifier such as frontal face]\n"
               "   [--nested-cascade[=nested_cascade_path this an optional secondary classifier such as eyes]]\n"
               "   [--scale=<image scale greater or equal to 1, try 1.3 for example>]\n"
               "   [--try-flip]\n"
               "   [filename|camera_index]\n\n"
            "see facedetect.cmd for one call:\n"
            "./facedetect --cascade=\"../../data/haarcascades/haarcascade_frontalface_alt.xml\" --nested-cascade=\"../../data/haarcascades/haarcascade_eye.xml\" --scale=1.3\n\n"
            "During execution:\n\tHit any key to quit.\n"
            "\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip );

string cascadeName = "C:/opencv/data/haarcascades/haarcascade_frontalface_alt.xml";
string nestedCascadeName = "C:/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";


int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    CvCapture* capture = 0;
        Mat frame, frameCopy, image;
        const string scaleOpt = "--scale=";
        size_t scaleOptLen = scaleOpt.length();
        const string cascadeOpt = "--cascade=";
        size_t cascadeOptLen = cascadeOpt.length();
        const string nestedCascadeOpt = "--nested-cascade";
        size_t nestedCascadeOptLen = nestedCascadeOpt.length();
        const string tryFlipOpt = "--try-flip";
        size_t tryFlipOptLen = tryFlipOpt.length();
        string inputName;
        bool tryflip = false;

        help();

        CascadeClassifier cascade, nestedCascade;
        double scale = 1;

        for( int i = 1; i < argc; i++ )
        {
            cout << "Processing " << i << " " <<  argv[i] << endl;
            if( cascadeOpt.compare( 0, cascadeOptLen, argv[i], cascadeOptLen ) == 0 )
            {
                cascadeName.assign( argv[i] + cascadeOptLen );
                cout << "  from which we have cascadeName= " << cascadeName << endl;
            }
            else if( nestedCascadeOpt.compare( 0, nestedCascadeOptLen, argv[i], nestedCascadeOptLen ) == 0 )
            {
                if( argv[i][nestedCascadeOpt.length()] == '=' )
                    nestedCascadeName.assign( argv[i] + nestedCascadeOpt.length() + 1 );
                if( !nestedCascade.load( nestedCascadeName ) )
                    cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
            }
            else if( scaleOpt.compare( 0, scaleOptLen, argv[i], scaleOptLen ) == 0 )
            {
                if( !sscanf( argv[i] + scaleOpt.length(), "%lf", &scale ) || scale < 1 )
                    scale = 1;
                cout << " from which we read scale = " << scale << endl;
            }
            else if( tryFlipOpt.compare( 0, tryFlipOptLen, argv[i], tryFlipOptLen ) == 0 )
            {
                tryflip = true;
                cout << " will try to flip image horizontally to detect assymetric objects\n";
            }
            else if( argv[i][0] == '-' )
            {
                cerr << "WARNING: Unknown option %s" << argv[i] << endl;
            }
            else
                inputName.assign( argv[i] );
        }

        if( !cascade.load( cascadeName ) )
        {
            cerr << "ERROR: Could not load classifier cascade" << endl;
            help();
            return -1;
        }

        if( inputName.empty() || (isdigit(inputName.c_str()[0]) && inputName.c_str()[1] == '\0') )
        {
            capture = cvCaptureFromCAM( inputName.empty() ? 0 : inputName.c_str()[0] - '0' );
            int c = inputName.empty() ? 0 : inputName.c_str()[0] - '0' ;
            if(!capture) cout << "Capture from CAM " <<  c << " didn't work" << endl;
        }
        else if( inputName.size() )
        {
            image = imread( inputName, 1 );
            if( image.empty() )
            {
                capture = cvCaptureFromAVI( inputName.c_str() );
                if(!capture) cout << "Capture from AVI didn't work" << endl;
            }
        }
        else
        {
            image = imread( "lena.jpg", 1 );
            if(image.empty()) cout << "Couldn't read lena.jpg" << endl;
        }

        cvNamedWindow( "result", 1 );

        if( capture )
        {
            cout << "In capture ..." << endl;
            for(;;)
            {
                IplImage* iplImg = cvQueryFrame( capture );
                frame = iplImg;
                if( frame.empty() )
                    break;
                if( iplImg->origin == IPL_ORIGIN_TL )
                    frame.copyTo( frameCopy );
                else
                    flip( frame, frameCopy, 0 );

                detectAndDraw( frameCopy, cascade, nestedCascade, scale, tryflip );

                if( waitKey( 10 ) >= 0 )
                    goto _cleanup_;
            }

            waitKey(0);

    _cleanup_:
            cvReleaseCapture( &capture );
        }
        else
        {
            cout << "In image read" << endl;
            if( !image.empty() )
            {
                detectAndDraw( image, cascade, nestedCascade, scale, tryflip );
                waitKey(0);
            }
            else if( !inputName.empty() )
            {
                /* assume it is a text file containing the
                list of the image filenames to be processed - one per line */
                FILE* f = fopen( inputName.c_str(), "rt" );
                if( f )
                {
                    char buf[1000+1];
                    while( fgets( buf, 1000, f ) )
                    {
                        int len = (int)strlen(buf), c;
                        while( len > 0 && isspace(buf[len-1]) )
                            len--;
                        buf[len] = '\0';
                        cout << "file " << buf << endl;
                        image = imread( buf, 1 );
                        if( !image.empty() )
                        {
                            detectAndDraw( image, cascade, nestedCascade, scale, tryflip );
                            c = waitKey(0);
                            if( c == 27 || c == 'q' || c == 'Q' )
                                break;
                        }
                        else
                        {
                            cerr << "Aw snap, couldn't read image " << buf << endl;
                        }
                    }
                    fclose(f);
                }
            }
        }

        cvDestroyWindow("result");
    return a.exec();
}
