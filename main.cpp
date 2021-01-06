#include "opencv2/opencv.hpp"
#include <iostream>  
  
using namespace cv;  
using namespace std;  
  
int main(int, char**)  {  

    Mat img = imread("", 1);
    imshow("abcd", img);
    
  
  
    return 0;  
}  