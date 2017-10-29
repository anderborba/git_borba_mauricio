#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
 
using namespace cv;
using namespace std;
 
int main( int, char** argv)
{
    Mat src1;
    src1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    namedWindow( "Original image", CV_WINDOW_AUTOSIZE );
    imshow( "Original image", src1 );
 
    Mat gray, edge, draw;
    cvtColor(src1, gray, CV_BGR2GRAY);
    int par = int (mean(src1)[1]);
    int par_l = int(0.6666 * par);
    int par_h = int(1.3333 * par);
    Canny( gray, edge, par_l, par_h, 3);
 
    edge.convertTo(draw, CV_8U);
    namedWindow("image", CV_WINDOW_AUTOSIZE);
    imshow("image", draw);
    imwrite("canny_Eq_Phantom_0p000_4_1_1.jpg", draw); 
    waitKey(0);                                       
    return 0;
} 
