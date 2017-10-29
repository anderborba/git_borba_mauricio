/*  Anderson Adaime de Borba
*************************************************
   Visão Computacional
*************************************************
*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


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
    int lup  = 9;
    int ldow = 2;
    int nf;
    int ng;
    Mat temp1;
    Mat img_aux;
    vector <Mat> imgmult(10);
    image.copyTo(temp1);
    imread(argv[1]).convertTo(temp1,CV_8U);
    Size s(pow(2, lup), pow(2, lup));
    resize(temp1, temp1, s);
    cvtColor( temp1, temp1, CV_BGR2GRAY );
//    imshow("teste", temp1 );
//    printf("dim temp1.height %d\n", temp1.rows);
//    printf("dim temp1.width  %d\n", temp1.cols);
    imgmult[lup] = temp1;
    for(int i=lup; i>= ldow; i--){
        nf = pow(2, i);
        ng = int(nf/2);
        GaussianBlur(imgmult[i], imgmult[i], Size( 3, 3), 0, 0 );
        Laplacian( imgmult[i],imgmult[i], CV_8U, 1, 1, 0, BORDER_DEFAULT );
        pyrDown(imgmult[i], imgmult[i - 1], Size(ng, ng) );
    }
    for(int i=ldow; i <= lup; i++){
        nf = pow(2,  i);
        ng = int(nf/2);
        pyrUp(imgmult[i - 1], img_aux, Size(nf, nf) );
        imgmult[i] = imgmult[i] + img_aux;
//        GaussianBlur(imgmult[i], imgmult[i], Size( 3, 3), 0, 0 );
//        Laplacian( imgmult[i],imgmult[i], CV_8U, 3, 1, 0, BORDER_DEFAULT ); 
    }
    imshow(window_name, 3 * imgmult[lup]  );
    imwrite("mult_Eq_Phantom_0p700_4_1_1.jpg", 3 * imgmult[lup]);
    waitKey(0); 
    return 0;
}
