/*  Anderson Adaime de Borba
*************************************************
   Visão Computacional
*************************************************
*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


using namespace cv;
using namespace std;

const char* window_name = "Piramide laplaciana";
void scale(Mat &input, Mat &output, float height, float width) {
    height = ( ( rand() % 20 ) * -1 ) + height;
    width  = ( ( rand() % 20 ) * -1 ) + width;
    Size s(width, height);
    resize(input, output, s);
}
int main(int argc, char** argv) {
    Mat image = imread(argv[1]);
    int level = 9;
    Mat temp1, temp2;
    Mat Lap;
    Mat imgblur;
    vector<Point2f> pontos(10);
    image.copyTo(temp1);
    imread(argv[1]).convertTo(temp1,CV_8U);
    Size s(pow(2, level), pow(2, level));
    resize(temp1, temp1, s);
    //scale(temp1, temp1, pow(2, level), pow(2, level));
    cvtColor( temp1, temp1, CV_BGR2GRAY );
    GaussianBlur( temp1, temp1, Size( 3, 3), 0, 0 );
    //Laplacian( temp1, temp1, CV_8U, 3, 1, 0, BORDER_DEFAULT );
    Laplacian( temp1, temp1, CV_8U, 1, 1, 0, BORDER_DEFAULT );
    imgblur = temp1;
    for(int i=0; i<level; i++){
        pyrDown(temp1, temp2);
        temp1 = temp2;
    }
    for(int i=0; i<level; i++){
         pyrUp(temp2, temp1);
         temp2 = temp1; 
    }
    Lap = 3*(imgblur - temp1);
    Size ss(500, 500);
    resize(Lap, Lap, ss);
    imshow(window_name, Lap );
    imwrite("lap_pir_Eq_Phantom_0p700_4_1_1.jpg", Lap );
    waitKey(0); 
    return 0;
}
