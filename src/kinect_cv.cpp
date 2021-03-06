/*=================================================================================
 *	                    Copyleft! 2019 William Yu
 *          Some rights reserved：CC(creativecommons.org)BY-NC-SA
 *                      Copyleft! 2019 William Yu
 *      版权部分所有，遵循CC(creativecommons.org)BY-NC-SA协议授权方式使用
 *
 * Filename                : kinect_cv.cpp
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

/**
 * @function GlViewColor
 * @author libfreenect
 * @brief 伪彩色可视化
 */
IplImage *GlViewColor(IplImage *depth)
{
	static IplImage *image = 0;
	if (!image) image = cvCreateImage(cvSize(640,480), 8, 3);
	unsigned char *depth_mid = (unsigned char*)(image->imageData);
	int i;
	for (i = 0; i < 640*480; i++) {
		int lb = ((short *)depth->imageData)[i] % 256;
		int ub = ((short *)depth->imageData)[i] / 256;
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

/**
 * @function GlViewColor_mm------------------not finished yet
 * @author William Yu
 * @brief 输入数据范围
 * 			采用16位伪灰度可视化
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
	while (1) 
	{
		unsigned int timestamp_rgb, timestamp_depth;
		IplImage *image = freenect_sync_get_rgb_cv(0, FREENECT_VIDEO_RGB, timestamp_rgb);
		if (!image) {
		    std::cout<<"Error: Kinect not connected?"<<std::endl;
		    return -1;
		}
		IplImage *depth = freenect_sync_get_depth_cv(0, FREENECT_DEPTH_11BIT, timestamp_depth);
		if (!depth) {
		    std::cout<<"Error: Kinect not connected?"<<std::endl;
		    return -1;
		}
		cvCvtColor(image, image, CV_RGB2BGR);
		
		cv::Mat Imgmat, depthmat;
		Imgmat = cv::cvarrToMat(image);
		depthmat = cv::cvarrToMat( GlViewColor(depth) );
		cv::namedWindow("RGB", CV_WINDOW_NORMAL);
		cv::imshow("RGB", Imgmat);
		cv::namedWindow("Depth", CV_WINDOW_NORMAL);
		cv::imshow("Depth", depthmat);
		if( (char)cv::waitKey(10) == 27 ) // 'ESC'
            break;
	}
	return 0;
}
