/*=================================================================================
 *	                    Copyleft! 2019 William Yu
 *          Some rights reserved：CC(creativecommons.org)BY-NC-SA
 *                      Copyleft! 2019 William Yu
 *      版权部分所有，遵循CC(creativecommons.org)BY-NC-SA协议授权方式使用
 *
 * Filename                : my_libfreenect_cv.cpp
 * Description             : libfreenect+kinectv1+opencv3.3.1+Ubuntu1604
 * Reference               : 
 * Programmer(s)           : William Yu, windmillyucong@163.com
 * Company                 : HUST
 * Modification History	   : ver1.0, 2019.01.23, William Yu
 *                           
=================================================================================*/

#include "libfreenect.h"
#include "libfreenect_sync.h"
#include "my_libfreenect_cv.h"

/*-----------------------------[Note]---------------------------*/
// /// Enumeration of depth frame states
// /// See http://openkinect.org/wiki/Protocol_Documentation#RGB_Camera for more information.
// typedef enum {
// 	FREENECT_DEPTH_11BIT        = 0, /**< 11 bit depth information in one uint16_t/pixel */
// 	FREENECT_DEPTH_10BIT        = 1, /**< 10 bit depth information in one uint16_t/pixel */
// 	FREENECT_DEPTH_11BIT_PACKED = 2, /**< 11 bit packed depth information */
// 	FREENECT_DEPTH_10BIT_PACKED = 3, /**< 10 bit packed depth information */
// 	FREENECT_DEPTH_REGISTERED   = 4, /**< processed depth data in mm, aligned to 640x480 RGB */ mm单位，像素对齐至RGB
// 	FREENECT_DEPTH_MM           = 5, /**< depth to each pixel in mm, but left unaligned to RGB image */
// 	FREENECT_DEPTH_DUMMY        = 2147483647, /**< Dummy value to force enum to be 32 bits wide */
// } freenect_depth_format;
/*--------------------------------------------------------------*/
IplImage *freenect_sync_get_depth_cv(int index, freenect_depth_format fmt)
{
	static IplImage *image = 0;
	static char *data = 0;
	if (!image) image = cvCreateImageHeader(cvSize(640,480), 16, 1);
	unsigned int timestamp;
	if (freenect_sync_get_depth((void**)&data, &timestamp, index, fmt))
	    return NULL;
	cvSetData(image, data, 640*2);
	return image;
}


/*-----------------------------[Note]---------------------------*/
// /// Enumeration of video frame information states.
// /// See http://openkinect.org/wiki/Protocol_Documentation#RGB_Camera for more information.
// typedef enum {
// 	FREENECT_VIDEO_RGB             = 0, /**< Decompressed RGB mode (demosaicing done by libfreenect) */
// 	FREENECT_VIDEO_BAYER           = 1, /**< Bayer compressed mode (raw information from camera) */
// 	FREENECT_VIDEO_IR_8BIT         = 2, /**< 8-bit IR mode  */ 红外图
// 	FREENECT_VIDEO_IR_10BIT        = 3, /**< 10-bit IR mode */
// 	FREENECT_VIDEO_IR_10BIT_PACKED = 4, /**< 10-bit packed IR mode */
// 	FREENECT_VIDEO_YUV_RGB         = 5, /**< YUV RGB mode */
// 	FREENECT_VIDEO_YUV_RAW         = 6, /**< YUV Raw mode */
// 	FREENECT_VIDEO_DUMMY           = 2147483647, /**< Dummy value to force enum to be 32 bits wide */
// } freenect_video_format;
/*--------------------------------------------------------------*/
IplImage *freenect_sync_get_rgb_cv(int index, freenect_video_format fmt)
{
	static IplImage *image = 0;
	static char *data = 0;
	if (!image) image = cvCreateImageHeader(cvSize(640,480), 8, 3);
	unsigned int timestamp;
	if (freenect_sync_get_video((void**)&data, &timestamp, index, fmt))
	    return NULL;
	cvSetData(image, data, 640*3);
	return image;
}