#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main( int argc, char** argv )
{
  Mat src;
  Mat src_gray(src.cols, src.rows, CV_BGR2GRAY, Scalar(0, 0, 0 ));
  Mat dst(src.cols, src.rows, CV_BGR2GRAY, Scalar(0, 0, 0 ));
  int kernel_size = 3;
  int scale = 1;
  int delta = 0;
  int ddepth = CV_16S;
  //char* window_name = "Laplace";
  //int c;
  src = imread( argv[1] );
  if( !src.data )
    { return -1; }
  GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
  cvtColor( src, src_gray, CV_BGR2GRAY );
  namedWindow("Laplace", CV_WINDOW_AUTOSIZE );
  Mat abs_dst;
  Laplacian( src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
  convertScaleAbs( dst, abs_dst );
  imshow( "Laplace", abs_dst );
  imwrite("lap_Eq_Phantom_0p700_4_1_1.jpg", abs_dst);
  waitKey(0);
  return 0;
  }
