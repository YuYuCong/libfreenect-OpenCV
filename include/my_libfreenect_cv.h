#pragma once

#include "libfreenect.h"
#include "libfreenect_sync.h"
#include <opencv/cv.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

	IplImage *freenect_sync_get_depth_cv(int index, freenect_depth_format fmt);
	IplImage *freenect_sync_get_rgb_cv(int index, freenect_video_format fmt);

#ifdef __cplusplus
}
#endif