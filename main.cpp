#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>  
#include <list>
#include <vector>

using namespace cv;  
using namespace std;  

void onMouse(int event, int x, int y, int flags, void* param){
	cv::Mat *im = reinterpret_cast<cv::Mat*>(param);

	switch (event){ // 이벤트 전달
        case EVENT_LBUTTONDOWN: // 마우스 좌클릭시 이벤트
            std::cout << "(" << x << ", " << y << "): " << static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl; // (x, y)에 있는 화소값 출력
            break;

        case EVENT_RBUTTONDOWN: // 마우스 우클릭시 이벤트
            std::cout << "Hello!" << std::endl; // Hello! 출력
            break;
	}
}

void getPixel(Mat img, string imgfile){
    cout<< imgfile << " pixel ~ ";
    for(int i=280; i<300; i++){
        cout<< static_cast<int>(img.at<uchar>(cv::Point(i, 75))) << " ";
    }cout<<endl;
    rectangle(img, Point(280, 62), Point(300, 68), Scalar(255, 0, 255), 20);
    cout<< "backgroung ~ ";
    for(int i=500; i<520; i++){
        cout<< static_cast<int>(img.at<uchar>(cv::Point(i, 75))) << " ";
    }cout<<endl<<endl;
}

Mat Roi_strip(Mat img){
   return img(Rect(0, 280, img.size().width, 130)); // 0~808 280~410
}

void getWidthHistogram(Mat image){
    int height = image.size().height;
    int width = image.size().width;

    double max=250;
    int height_standard = 300; //255 //275
    int gap_analy = 33;
    cout<< "image height: "<< height << "width: "<< width <<endl;

    //int half_height = height/2;
    list<vector<cv::Point>> m_data;    
    m_data.clear();
    vector<Point> points;
    points.reserve(width);

    for(int j=0; j< width; j++)    {
        double r=0;
        for(int i=height_standard; i< height_standard+gap_analy; i++){
             //r += image.data[image.channels()*(image.cols*half_height + j) + 0];
             r += (image.at<unsigned short>(i,j));
        }
        r = r /gap_analy;
        //qDebug() << r;
        if(max < r)
            max = r;
        //mFileOut.addData(QString::number(r)+"\n");

        //ui->result->graph(0)->addData(j, r);
        points.push_back(Point(j, r));

    }
    //mFileOut.closeFile();
    m_data.push_back(points);
/*
    if(!image.data){
        qDebug() << "Could not open image!!!" << endl;
    }else{
        getAlgorithm(points);

    }*/
}
double getSumInVector(vector<Point> points, int start, int end){

    double sum = 0.0;
    for(int i=start; i<=end; i++){
        Point data = points.at(i);
        double y(0);
        y=data.y;
        //y = data.y();
        
        sum += y;
    }

    return sum;
}
double getAverageInVector(vector<Point> points, int start, int end){
    double sum = 0.0;
    for(int i=start; i<=end; i++){
        Point data = points.at(i);
        double y(0);
        y = data.y;     
        sum += y;
    }
    sum = sum /(end-start+1); //for average

    return sum;
}
/*
void getAlgorithm(vector<Point> points){
    int control_s = 270;
    int control_e = control_s + 50; double control_sum =0;
    int test_s = control_e + 50; int test_e = test_s+100; double test_sum = 0;
    int back_s = test_e+50; int back_e = back_s+70; double back_sum = 0;

    double back_average = getAverageInVector(points, back_s, back_e);
    points = processOffset(points, back_average);
    points = processMovingAverage(points, 5);
    cout<< "ctrl ssss" <<control_s;
    if(points.count() >= back_e ){
        back_sum = getSumInVector(points, back_s, back_e);
        test_sum = getSumInVector(points, test_s, test_e);
        control_sum = getSumInVector(points, control_s, control_e);
        cout <<"back= " << back_sum <<"\t test= " << test_sum << "\t control= " << control_sum << "\t";


        double test_area = test_sum-back_sum;
        double control_area = control_sum -back_sum;
        double tc_ratio = test_area/control_area * 100;


    }else{

    }
}*/

int main(int, char**)  {  

    Mat img1 = imread("101937_capture-0.png", -1);
    Mat img2 = imread("101937_capture-0.png", 0);
    Mat img3 = imread("101937_capture-0.png", 1);
    
    Mat ROI_img1 = Roi_strip(img1);
    Mat ROI_img2 = Roi_strip(img2);
    Mat ROI_img3 = Roi_strip(img3);
    //pixelformat CV_16UC1

    imshow("-1", ROI_img1);
    imshow("0", ROI_img2);
    imshow("1", ROI_img3);

    
    setMouseCallback("-1", onMouse, reinterpret_cast<void*>(&ROI_img1));
    setMouseCallback("0", onMouse, reinterpret_cast<void*>(&ROI_img2));
    setMouseCallback("1", onMouse, reinterpret_cast<void*>(&ROI_img3));

    getPixel(ROI_img1, "img1");
    getPixel(ROI_img2, "img2");
    getPixel(ROI_img3, "img3");

    //waitKey(0);
    cout<< "fff" << endl;
    

    return 0;  
}  

/*
// declaration
cv::Mat img;
	
// member variables
img.dims // 차원 수
img.rows // 행의 수
img.cols // 열의 수
img.data // 원소 데이터에 대한 포인터
img.step // 한 행이 차지하는 바이트 수
 
// member methods
img.channels()	// 채널 수
img.depth()		// 자료형
img.elemSize()	// 원소 바이트 크기
img.elemSize1()	// 원소 한 채널 바이트 크기
img.empty()		// 비어있는지 확인
img.isSubmatrix()	// 참조 행렬인지 여부 확인
img.size()		// 행렬 크기를 Size 형으로 
img.total()		// 원소 전체 개수 
img.type()		// 데이터 타입 (상위 3비트 자료형, 하위 3비트 채널 수)\
img.clone()
img.copyTo()
img.convertTo()

enum ImreadModes {
       IMREAD_UNCHANGED            = -1, //!< If set, return the loaded image as is (with alpha channel, otherwise it gets cropped).
       IMREAD_GRAYSCALE            = 0,  //!< If set, always convert image to the single channel grayscale image (codec internal conversion).
       IMREAD_COLOR                = 1,  //!< If set, always convert image to the 3 channel BGR color image.
       IMREAD_ANYDEPTH             = 2,  //!< If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit.
       IMREAD_ANYCOLOR             = 4,  //!< If set, the image is read in any possible color format.
       IMREAD_LOAD_GDAL            = 8,  //!< If set, use the gdal driver for loading the image.
       IMREAD_REDUCED_GRAYSCALE_2  = 16, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/2.
       IMREAD_REDUCED_COLOR_2      = 17, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/2.
       IMREAD_REDUCED_GRAYSCALE_4  = 32, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/4.
       IMREAD_REDUCED_COLOR_4      = 33, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/4.
       IMREAD_REDUCED_GRAYSCALE_8  = 64, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/8.
       IMREAD_REDUCED_COLOR_8      = 65, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/8.
       IMREAD_IGNORE_ORIENTATION   = 128 //!< If set, do not rotate the image according to EXIF's orientation flag.
     };

*/