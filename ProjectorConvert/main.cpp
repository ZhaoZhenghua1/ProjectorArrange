#include "projectorconvert.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	
	QRectF r(0, 0, 10, 10);
	QPointF tl =  r.topLeft();
	QApplication a(argc, argv);
	ProjectorConvert w;
	w.show();
	return a.exec();
}
 #include<cv.h>
 #include<highgui.h>
//cv::Mat a;
// #pragma comment(lib, "cv.lib")
// #pragma comment(lib, "cxcore.lib")
// #pragma comment(lib, "highgui.lib")

//  int main()
 //  {
 //  	CvPoint2D32f srcTri[4], dstTri[4];
 //  	CvMat*       warp_mat = cvCreateMat(3, 3, CV_32FC1);
 //  	IplImage*    src = NULL;
 //  	IplImage*    dst = NULL;
 //  
 //  	src = cvLoadImage("E:\\origpic.png");//("D:\\1.jpg");//("E:\\Í¼Ïñ´¦Àí\\25.bmp");
 //  	dst = cvCloneImage(src);
 //  	dst->origin = src->origin;
 //  	cvZero(dst);
 //  
 //  	srcTri[0].x = 0;
 //  	srcTri[0].y = 0;
 //  	srcTri[1].x = src->width - 1;
 //  	srcTri[1].y = 0;
 //  	srcTri[2].x = 0;
 //  	srcTri[2].y = src->height - 1;
 //  	srcTri[3].x = src->width - 1;
 //  	srcTri[3].y = src->height - 1;
 // 
 // 	dstTri[0].x = 0;
 // 	dstTri[0].y = 0;
 // 	dstTri[1].x = src->width - 1;
 // 	dstTri[1].y = 0;
 // 	dstTri[2].x = 0;
 // 	dstTri[2].y = src->height - 1;
 // 	dstTri[3].x = src->width - 1;
 // 	dstTri[3].y = src->height - 1;
 //  
 // //  	dstTri[0].x = src->width * 0;
 // //  	dstTri[0].y = src->height * 0;
 // //  	dstTri[1].x = src->width * 0.9;
 // //  	dstTri[1].y = src->height * 0.1;
 // //  	dstTri[2].x = src->width * 0.21;
 // //  	dstTri[2].y = src->height*0.8;
 // //  	dstTri[3].x = src->width*0.9;
 // //  	dstTri[3].y = src->height*0.8;
 //  
 //  	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
 //  	cvWarpPerspective(src, dst, warp_mat);
 //  
 //  	cvNamedWindow("src", 1);
 //  	cvShowImage("src", src);
 //  	cvNamedWindow("Affine_Transform", 1);
 //  	cvShowImage("Affine_Transform", dst);
 //  
 //  	cvWaitKey(0);
 //  
 //  	cvReleaseImage(&src);
 //  	cvReleaseImage(&dst);
 //  	cvReleaseMat(&warp_mat);
 //  
 //  	return 0;
 //  }