/*=================================================================================
 *	                    Copyleft! 2019 William Yu
 *          Some rights reserved：CC(creativecommons.org)BY-NC-SA
 *                      Copyleft! 2019 William Yu
 *      版权部分所有，遵循CC(creativecommons.org)BY-NC-SA协议授权方式使用
 *
 * Filename                : Accuracy_assessment.cpp
 * Description             : libfreenect + kinectv1 + opencv3.3.1 + Ubuntu1604
 *                           libfreenect opencv 编程实践
 * Reference               : 
 * Programmer(s)           : William Yu, windmillyucong@163.com
 * Company                 : HUST
 * Modification History	   : ver1.0, 2019.01.23, William Yu
 *                           
=================================================================================*/

#include <iostream>
#include <opencv2/opencv.hpp>
#include "my_libfreenect_cv.h"
#include <fstream>
#include <time.h>    


/**
 * @function GlViewColor_mm------------------not finished yet
 * @author William Yu
 * @brief 输入数据范围应该在0-7000
 * 			采用8位3通道伪彩色可视化
 */
IplImage *GlViewColor_mm(IplImage *depth_mm)
{
	static IplImage *image = 0;
	if (!image) image = cvCreateImage(cvSize(640,480), 8, 3);
	unsigned char *depth_mid = (unsigned char*)(image->imageData);
	int i;
	for (i = 0; i < 640*480; i++) {
		int lb = ((short *)depth_mm->imageData)[i] % 256;
		int ub = ((short *)depth_mm->imageData)[i] / 256;
		switch (ub) {
			case 0:
				depth_mid[3*i+2] = 255;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+0] = 255-lb;
				break;
			case 1:
				depth_mid[3*i+2] = 255;
				depth_mid[3*i+1] = lb;
				depth_mid[3*i+0] = 0;
				break;
			case 2:
				depth_mid[3*i+2] = 255-lb;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+0] = 0;
				break;
			case 3:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+0] = lb;
				break;
			case 4:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+0] = 255;
				break;
			case 5:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+0] = 255-lb;
				break;
			default:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+0] = 0;
				break;
		}
	}
	return image;
}


  

int main(int argc, char **argv)
{
	//--写入txt文本
	std::ofstream txtwrite;
 	txtwrite.open("./data/associate.txt", std::ios::trunc); 
    //--文件头标识为时间
	time_t rawtime;
  	struct tm * timeinfo;
	time ( &rawtime );
	txtwrite<<"#"<<" " << "time:" << asctime ( localtime(&rawtime) ) << "\n";
	
	int imgnum = 0;
	while (1)
	{
		unsigned int timestamp_rgb, timestamp_depth;
		IplImage *image = freenect_sync_get_rgb_cv(0, FREENECT_VIDEO_RGB, timestamp_rgb);
		if (!image) {
		    std::cout<<"Error: Kinect not connected?"<<std::endl;
		    return -1;
		}
		IplImage *depth_mm = freenect_sync_get_depth_cv(0, FREENECT_DEPTH_REGISTERED, timestamp_depth);//mm + 对齐
		if (!depth_mm) {
		    std::cout<<"Error: Kinect not connected?"<<std::endl;
		    return -1;
		}
		cvCvtColor(image, image, CV_RGB2BGR);
		
		cv::Mat Imgmat;
		cv::Mat depthmat;
		//cv::Mat depthmat(640, 480, CV_16U);//16位无符号整型  
		
		Imgmat = cv::cvarrToMat(image);
		//IplImage *depthshow = GlViewColor_mm(depth_mm);
		depthmat = cv::cvarrToMat(depth_mm);

		// //--check
		// cv::circle(Imgmat, cv::Point(Imgmat.cols/2, Imgmat.rows/2), 5, cv::Scalar(0, 0, 255), -1);
		// cv::line(Imgmat, cv::Point(0, Imgmat.rows/2), cv::Point(Imgmat.cols, Imgmat.rows/2), cv::Scalar(0, 0, 255));
		// cv::line(Imgmat, cv::Point(Imgmat.cols/2, 0), cv::Point(Imgmat.cols/2, Imgmat.rows), cv::Scalar(0, 0, 255));

		cv::namedWindow("RGB", CV_WINDOW_NORMAL);
		cv::imshow("RGB", Imgmat);
		cv::namedWindow("Depth", CV_WINDOW_NORMAL);
		cv::imshow("Depth", depthmat);
//		if( (char)cv::waitKey(5) == 'c' ) // 'c'
//     	{
			imgnum++;
			
			std::cout<<"saving img"<<imgnum<<"..."<<std::endl;
			cv::imwrite( "./data/rgb/"+std::to_string(timestamp_rgb)+".png", Imgmat );
			cv::imwrite( "./data/depth/"+std::to_string(timestamp_depth)+".png", depthmat );
			
			//--输出关联txtwrite
			txtwrite<<timestamp_rgb<<" "<<"rgb/"+std::to_string(timestamp_rgb)+".png"<<" "
					<<timestamp_depth<<" "<<"depth/"+std::to_string(timestamp_depth)+".png"<<"\n";

//		}
		if( (char)cv::waitKey(30) == 27 ) // 'ESC'
            break;
	}

	txtwrite.close();//关闭文件写出
	return 0;
}