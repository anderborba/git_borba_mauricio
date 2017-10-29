/*  Anderson Adaime de Borba
*************************************************
*/
#include <stdlib.h>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include <math.h>
//#include <time.h>
//#include <iostream>

using namespace cv;

double sol_exata(double x, double y, double t){
	    return exp(x + y + 2.0 * t)	;
}
double cond_inicial(int n, Mat u){
    int i, j;
    double h = 1.0 / (n - 1);
    for (i = 1; i < n - 1; i++ )	
    	for (j = 1; j < n -1; j++ )
	    u.at<double>(i, j) = exp(i * h + j * h);
}
double cond_contorno(int n, double t, Mat u){
    int i;
    double h = 1.0 / (n - 1);
    for (i = 0; i < n ; i++ ){	
	    u.at<double>(0,     i) = exp(i * h +           2.0 * t);
	    u.at<double>(n - 1, i) = exp(1.0   +   i * h + 2.0 * t);
	    u.at<double>(i,     0) = exp(i * h +           2.0 * t);
	    u.at<double>(i, n - 1) = exp(i * h +   1.0   + 2.0 * t);
    }    
}
double imprime(int n, Mat u){
    int i, j;
    FILE *ofp;
    double h = 1.0 / (n- 1);
    ofp = fopen("saida.txt","w");
    if(!ofp){
	    printf("Erro na abertura do arquivo de saida");
	    exit(0);
    }
    for (i = 0; i < n; i++ ){	
    	for (j = 0; j < n; j++ ){
	    fprintf(ofp,"%f %f  %6.12f\n",i * h, h * j, u.at<double>(i, j));
	}
	fprintf(ofp,"\n");
    }
    fclose(ofp);
}
double imprime_sol(int n){
    int i, j;
    FILE *ofp;
    double h = 1.0 / (n- 1);
    ofp = fopen("saida_sol.txt","w");
    if(!ofp){
	    printf("Erro na abertura do arquivo de saida");
	    exit(0);
    }
    for (i = 0; i < n; i++ ){	
    	for (j = 0; j < n; j++ ){
	    fprintf(ofp,"%f %f  %6.12f\n",i * h, h * j, sol_exata(i * h, j * h, 0.0));
	}
	fprintf(ofp,"\n");
    }
    fclose(ofp);
}
double copia(int n, Mat u_old, Mat u_new){
    int i, j;
    for (i = 1; i < n - 1; i++ )	
    	for (j = 1; j < n - 1; j++ )
	    u_old.at<double>(i, j) = u_new.at<double>(i, j);

}
double erro(int n, double t, Mat u_erro, Mat u_new){
    int i, j;
    double h = 1.0 / (n - 1);
    for (i = 0; i < n; i++ )	
    	for (j = 0; j < n; j++ )
	    u_erro.at<double>(i, j) = fabs(sol_exata(i * h, j * h, t) - u_new.at<double>(i, j));

}
double norma_max(int n, Mat u){
    int i, j;
    double normax = 0.0;
    for (i = 0; i < n; i++ )	
    	for (j = 0; j < n; j++ )
	    normax = fmax(normax, u.at<double>(i, j));
    return normax;
}
double passo_t(int n, Mat u_old, Mat u_new){
    int i, j, k;
    double aux;
    double h = 1.0 / (n - 1);
    double ht = 0.25 * h * h;
    int m = 1.0 / ht ;
    double c = ht / (h * h);
    printf(" %d , %f\n", m, c );
    //u_old.copyTo(u_new);
    //imshow("teste1", u_new);
//suppose you read an image from a file that is gray scale
// Mat image = imread("Your path", CV_8UC1);
//...do some processing
    uint8_t *myData = u_old.data;
    int width = u_old.cols;
    int height = u_old.rows;
    int _stride = u_old.step;//in case cols != strides
    namedWindow("teste1", WINDOW_AUTOSIZE); 
    imshow("teste1", u_old);
    printf("Altura = %d \n", height);
    printf("Largura = %d \n", width);
    for (k = 0; k <= m; k++){    
       printf("%f\n", k * ht);
       for(int i = 0; i < height; i++)
       {
          for(int j = 0; j < width; j++)
          {
	  aux =  u_old.at<uchar>(i + 1, j) + u_old.at<uchar>(i - 1, j) + u_old.at<uchar>(i, j + 1) + u_old.at<uchar>(i, j - 1) - 4.0 * u_old.at<uchar>(i, j);
	  u_new.at<char>(i, j) = u_old.at<char>(i, j) + c * aux;
          }
       }
    u_new.copyTo(u_old);
    }
    //copia(n, u_old, u_new);
    //double t = 0.0;
    //Mat u_erro(n, n, DataType<double>::type);
    //imprime_sol(n);
    //cond_inicial(n, u_old);
    //for (k = 0; k <= 0; k++){    
       // printf("%f\n", k * ht);
    	//cond_contorno(n, k * ht , u_old);
    	//for (i = 1; i < n - 1; i++){	
    	    //for (j = 1; j < n - 1; j++){
	    	//aux =  u_old.at<double>(i + 1, j) + u_old.at<double>(i - 1, j) + u_old.at<double>(i, j + 1) + u_old.at<double>(i, j - 1) - 4.0 * u_old.at<double>(i, j);
	    	//u_new.at<double>(i, j) = u_old.at<double>(i, j) + c * aux;
		//}	
	//}
    	//copia(n, u_old, u_new);
    //}
    //cond_contorno(n, k * ht, u_new);
    //erro(n, k * ht, u_erro, u_new);
    //imprime(n, u_erro);
    //printf("%6.12f\n", norma_max(n, u_erro));
    //imshow("teste3", u_new);
    namedWindow("teste2", WINDOW_AUTOSIZE); 
    namedWindow("teste3", WINDOW_AUTOSIZE); 
    imshow("teste2", u_new);
    absdiff(u_old, u_new, u_new);
    imshow("teste2", u_new);

    //waitKey(0);
}
int main(int argc, char** argv) {
    int n = pow(2, 7);
    Mat u_new(n, n, DataType<uchar>::type);
    Mat u_old(n, n, DataType<uchar>::type);
    //Mat teste = Mat(16, 16, CV_8UC3, 1);
    Mat teste;
    double aux;
    teste = imread(argv[1]);
    Size s(pow(2, 7), pow(2, 7));
    aux = pow(2, 7);
    Mat img(aux, aux, CV_8U, Scalar(255,255,255));
    //image.copyTo(teste);
    imread(argv[1]).convertTo(teste,CV_8U);
    resize(teste, teste, s);
  cvtColor( teste, teste, CV_BGR2GRAY );
  //absdiff(temp1, img, temp2); 
  //imshow("temp 2", temp2);
  //imshow("image", temp1);
  //Mat ruido(512, 512, CV_8U, Scalar(255,255,255));
   passo_t(n, teste, u_new);
    //imshow("teste1", teste);
    //imshow("teste2", img);
    waitKey(0);
    return 0;
}
