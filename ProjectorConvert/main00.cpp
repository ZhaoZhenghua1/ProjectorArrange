#include "cv.h"   
#include "highgui.h"   
using namespace cv; //下面的所有cv相关类型不用加上前缀了 
#include <cvaux.h>
#include <ml.h>
#include <iostream>
using namespace std;
#include <cmath>

#define pi 3.1415926
#define x_center 207
#define y_center 207

/*void  sphere( Mat &img)
{
	int i,j=0,i1=0,j1=0;
	int i0=img.cols/2;
	int j0=img.rows/2;
	for(i=1;i1<R/2;i++){
		for( j=0;j1<R/2;j++){
			//int i1=0,j1=0;
			i1 = cos(atan(j/i)) * sin((π*sqrt(i*i +j*j)) / (2*R)) * R;
			j1 = sin(atan(j/i)) * sin((π*sqrt(i*i +j*j)) / (2*R)) * R;
			img.at<Vec3b>(j1+j0,i1+i0)[0]=img.at<Vec3b>(i,j)[0];
			img.at<Vec3b>(j1+j0,i1+i0)[1]=img.at<Vec3b>(i,j)[1];
			img.at<Vec3b>(j1+j0,i1+i0)[2]=img.at<Vec3b>(i,j)[2];
			img.at<Vec3b>(-j1+j0,i1+i0)[0]=img.at<Vec3b>(i,j)[0];
			img.at<Vec3b>(-j1+j0,i1+i0)[1]=img.at<Vec3b>(i,j)[1];
			img.at<Vec3b>(-j1+j0,i1+i0)[2]=img.at<Vec3b>(i,j)[2];
			img.at<Vec3b>(j1+j0,-i1+i0)[0]=img.at<Vec3b>(i,j)[0];
			img.at<Vec3b>(j1+j0,-i1+i0)[1]=img.at<Vec3b>(i,j)[1];
			img.at<Vec3b>(j1+j0,-i1+i0)[2]=img.at<Vec3b>(i,j)[2];
			img.at<Vec3b>(-j1+j0,-i1+i0)[0]=img.at<Vec3b>(i,j)[0];
			img.at<Vec3b>(-j1+j0,-i1+i0)[1]=img.at<Vec3b>(i,j)[1];
			img.at<Vec3b>(-j1+j0,-i1+i0)[2]=img.at<Vec3b>(i,j)[2];
		}
		j1=0;
	}
};*/

void near(double xx,double yy,int x,int y,Mat img,Mat& img1){
	int x1=int (xx);
	double u=xx-double(x1);
	if(u>=0.5) x1+=1;
	int y1=int (yy);
	double v=yy-double(y1);
	if(v>=0.5) y1=y1+1;
	img1.at<Vec3b>(x,y)[0]=img.at<Vec3b>(x1,y1)[0];
	img1.at<Vec3b>(x,y)[1]=img.at<Vec3b>(x1,y1)[1];
	img1.at<Vec3b>(x,y)[2]=img.at<Vec3b>(x1,y1)[2];
}
void bilinear(double xx,double yy,int x,int y,Mat img,Mat& img1){
	int x1=int (xx);
	double u=xx-double(x1);
	int y1=int (yy);
	double v=yy-double(y1);
	img1.at<Vec3b>(x,y)[0]=(1-u)*(1-v)*img.at<Vec3b>(x1,y1)[0]+(1-v)*u*img.at<Vec3b>(x1+1,y1)[0]+(1-u)*v*img.at<Vec3b>(x1,y1+1)[0]+u*v*img.at<Vec3b>(x1+1,y1+1)[0];
	img1.at<Vec3b>(x,y)[1]=(1-u)*(1-v)*img.at<Vec3b>(x1,y1)[1]+(1-v)*u*img.at<Vec3b>(x1+1,y1)[1]+(1-u)*v*img.at<Vec3b>(x1,y1+1)[1]+u*v*img.at<Vec3b>(x1+1,y1+1)[1];
	img1.at<Vec3b>(x,y)[2]=(1-u)*(1-v)*img.at<Vec3b>(x1,y1)[2]+(1-v)*u*img.at<Vec3b>(x1+1,y1)[2]+(1-u)*v*img.at<Vec3b>(x1,y1+1)[2]+u*v*img.at<Vec3b>(x1+1,y1+1)[2];
}
double S(double x){
	double Sx;
	x=fabs(x);
	if(x<1)
		Sx=1-2*x*x+x*x*x;
	else if(x<2)
		Sx=4-8*x+5*x*x-x*x*x;
	else 
		Sx=0;
	return Sx;
}
void bicubic(double xx,double yy,int x,int y,Mat img,Mat& img1){
	int x1=int (xx);
	double u=xx-double(x1);
	int y1=int (yy);
	double v=yy-double(y1);
	double e;
	double temp1=S(1+u)*img.at<Vec3b>(x1-1,y1-1)[0]+S(u)*img.at<Vec3b>(x1,y1-1)[0]+S(u-1)*img.at<Vec3b>(x1+1,y1-1)[0]+S(u-2)*img.at<Vec3b>(x1+2,y1-1)[0];
	double temp2=S(1+u)*img.at<Vec3b>(x1-1,y1)[0]+S(u)*img.at<Vec3b>(x1,y1)[0]+S(u-1)*img.at<Vec3b>(x1+1,y1)[0]+S(u-2)*img.at<Vec3b>(x1+2,y1)[0];
	double temp3=S(1+u)*img.at<Vec3b>(x1-1,y1+1)[0]+S(u)*img.at<Vec3b>(x1,y1+1)[0]+S(u-1)*img.at<Vec3b>(x1+1,y1+1)[0]+S(u-2)*img.at<Vec3b>(x1+2,y1+1)[0];
	double temp4=S(1+u)*img.at<Vec3b>(x1-1,y1+2)[0]+S(u)*img.at<Vec3b>(x1,y1+2)[0]+S(u-1)*img.at<Vec3b>(x1+1,y1+2)[0]+S(u-2)*img.at<Vec3b>(x1+2,y1+2)[0];
	e=temp1*S(1+v)+temp2*S(v)+temp3*S(v-1)+temp4*S(v-2);
	if(e>255)
		img1.at<Vec3b>(x,y)[0]=255;
	else if(e<0)
		img1.at<Vec3b>(x,y)[0]=0;
	else 
		img1.at<Vec3b>(x,y)[0]=(uchar)e;

	temp1=S(1+u)*img.at<Vec3b>(x1-1,y1-1)[1]+S(u)*img.at<Vec3b>(x1,y1-1)[1]+S(u-1)*img.at<Vec3b>(x1+1,y1-1)[1]+S(u-2)*img.at<Vec3b>(x1+2,y1-1)[1];
	temp2=S(1+u)*img.at<Vec3b>(x1-1,y1)[1]+S(u)*img.at<Vec3b>(x1,y1)[1]+S(u-1)*img.at<Vec3b>(x1+1,y1)[1]+S(u-2)*img.at<Vec3b>(x1+2,y1)[1];
	temp3=S(1+u)*img.at<Vec3b>(x1-1,y1+1)[1]+S(u)*img.at<Vec3b>(x1,y1+1)[1]+S(u-1)*img.at<Vec3b>(x1+1,y1+1)[1]+S(u-2)*img.at<Vec3b>(x1+2,y1+1)[1];
	temp4=S(1+u)*img.at<Vec3b>(x1-1,y1+2)[1]+S(u)*img.at<Vec3b>(x1,y1+2)[1]+S(u-1)*img.at<Vec3b>(x1+1,y1+2)[1]+S(u-2)*img.at<Vec3b>(x1+2,y1+2)[1];
	e=temp1*S(1+v)+temp2*S(v)+temp3*S(v-1)+temp4*S(v-2);
	if(e>255)
		img1.at<Vec3b>(x,y)[1]=255;
	else if(e<0)
		img1.at<Vec3b>(x,y)[1]=0;
	else 
		img1.at<Vec3b>(x,y)[1]=(uchar)e;

	temp1=S(1+u)*img.at<Vec3b>(x1-1,y1-1)[2]+S(u)*img.at<Vec3b>(x1,y1-1)[2]+S(u-1)*img.at<Vec3b>(x1+1,y1-1)[2]+S(u-2)*img.at<Vec3b>(x1+2,y1-1)[2];
	temp2=S(1+u)*img.at<Vec3b>(x1-1,y1)[2]+S(u)*img.at<Vec3b>(x1,y1)[2]+S(u-1)*img.at<Vec3b>(x1+1,y1)[2]+S(u-2)*img.at<Vec3b>(x1+2,y1)[2];
	temp3=S(1+u)*img.at<Vec3b>(x1-1,y1+1)[2]+S(u)*img.at<Vec3b>(x1,y1+1)[2]+S(u-1)*img.at<Vec3b>(x1+1,y1+1)[2]+S(u-2)*img.at<Vec3b>(x1+2,y1+1)[2];
	temp4=S(1+u)*img.at<Vec3b>(x1-1,y1+2)[2]+S(u)*img.at<Vec3b>(x1,y1+2)[2]+S(u-1)*img.at<Vec3b>(x1+1,y1+2)[2]+S(u-2)*img.at<Vec3b>(x1+2,y1+2)[2];
	e=temp1*S(1+v)+temp2*S(v)+temp3*S(v-1)+temp4*S(v-2);
	if(e>255)
		img1.at<Vec3b>(x,y)[2]=255;
	else if(e<0)
		img1.at<Vec3b>(x,y)[2]=0;
	else 
		img1.at<Vec3b>(x,y)[2]=(uchar)e;
}
void sphere( Mat img,Mat &img1,int m){
	double xx=0,yy=0,R=200;
	int c=m;
	int i,j;
	int x=0,y=0;
	int x1=0,y1=0;
	double distance=0;
	for(i=0;i<2*R;i++)
		for(j=0;j<2*R;j++){
			distance =(double) sqrt((j - R)*(j - R) + (i - R)*(i - R));
			if (distance <= R)//区域内像素点
			{
				x = j - R + x_center; y = i - R + y_center;//输出图像的像素点坐标
				if (fabs(distance)>1e-6){
					xx = 2.0 / pi*(asin(distance / R))*R*(j - R) / distance + (double)x_center;
					yy = 2.0 / pi*(asin(distance / R))*R*(i - R) / distance + (double)y_center;
				}
				else{
					xx = x_center;
					yy = y_center;
				}
				if(c==0)
					near(xx,yy,x,y,img,img1);
				else if(c==1)
					bilinear(xx,yy,x,y,img,img1);
				else if(c==2)
					bicubic(xx,yy,x,y,img,img1);
			}
		}
}

void sphere1( Mat img,Mat &img1,int m){
	double xx=0,yy=0,R=200;
	int c=m;
	int i,j;
	int x=0,y=0;
	int x1=0,y1=0;
	double distance=0;
	for(i=0;i<2*R;i++)
		for(j=0;j<2*R;j++){
			distance =(double) sqrt((j - R)*(j - R) + (i - R)*(i - R));
			if (distance <= R)//区域内像素点
			{
				x = j - R + x_center; y = i - R + y_center;//输出图像的像素点坐标
				if (fabs(distance)>1e-6){
					xx = (double)((((double)(j - R)) / distance)*(sin(pi*distance / 2 / R))*R + x_center);
					yy = (double)((((double)(i - R)) / distance)*(sin(pi*distance / 2 / R))*R + y_center);
				}
				else{
					xx = x_center;
					yy = y_center;
				}
				if(c==0)
					near(xx,yy,x,y,img,img1);
				else if(c==1)
					bilinear(xx,yy,x,y,img,img1);
				else if(c==2)
					bicubic(xx,yy,x,y,img,img1);
			}
		}
}
void twist(Mat img,Mat &img1,int c)
{
	double beta,m,n = 3,R=200;
	double xx,yy;
	double distance=0;
	int x=0,y=0;
	int x1=0,y1=0;
	m = (double)2 / R;
	for (int i = 0; i < 2 * R; i++)
		for (int j = 0; j < 2 * R; j++)
		{
			distance = sqrt((double)(j - R)*(double)(j - R) + (double)(i - R)*(double)(i - R));
			if (distance <=R)//区域像素点
			{
				beta = pi / n*(1 - m*fabs(distance - (double)R / 2));
				x = j - R + x_center; 
				y = i - R + y_center;
				xx = (double)((j - R)*cos(beta) - (i - R)*sin(beta) + x_center); 
				yy = (double)((j - R)*sin(beta) + (i - R)*cos(beta) + y_center);
				if(c==0)
					near(xx,yy,x,y,img,img1);
				else if(c==1)
					bilinear(xx,yy,x,y,img,img1);
				else if(c==2)
					bicubic(xx,yy,x,y,img,img1);
			}
		}
}
double G(int i, double j){
	double Gij;
	switch(i){
		case 0: Gij = 1.0 / 6.0*(3*j*j - j*j*j - 3*j + 1); break;
		case 1: Gij = 1.0 / 6.0*(3*j*j*j - 6*j*j + 4); break;
		case 2: Gij = 1.0 / 6.0*(3*j*j - 3*j*j*j + 3*j + 1); break;
		case 3: Gij = 1.0 / 6.0*j*j*j; break;
		default:break;
	}
	return Gij;
}
void B_spline(int x0,int y0,int x1,int y1,Mat img,Mat &img1,int m){
	int delta=25;
	int c=m;
	for(int i = 0;i<4;i++)
		for(int j=0; j<4;j++){
			int l=3-i;
			int m=3-j;
			for(int a=0;a<delta;a++)
				for(int b=0;b<delta;b++){
					double u = 1.0 / (double)delta*a;
					double v = 1.0 / (double)delta*b;
					double x_shift = G(m, v)*G(l, u)* (double)(x1 - x0);
					double y_shift = G(m, v)*G(l, u)* (double)(y1 - y0);
					int x = delta * (i - 1) + a + x0;
					int y = delta * (j - 1) + b + y0;
					double xx= (double)x_shift + delta * (i - 1) + a + x0;
					double yy= (double)y_shift + delta * (j - 1) + b + y0;
					if(c==0)
						near(xx,yy,x,y,img,img1);
					else if(c==1)
						bilinear(xx,yy,x,y,img,img1);
					else if(c==2)
						bicubic(xx,yy,x,y,img,img1);
				}
		}
}
double U(CvPoint Pi,CvPoint Pxy)
{
	double r, result;
	if (Pi.x == Pxy.x&&Pi.y == Pxy.y)  return 0;
	r =( Pi.x-Pxy.x)*( Pi.x-Pxy.x)+( Pi.y-Pxy.y)*( Pi.y-Pxy.y);
	result = r*log(r);
	return result;
}
void TPS(CvPoint point0[5], CvPoint point1[5],Mat img,Mat &img1,int m){
	int c=m;
	cv::Mat L(8, 8, CV_64FC1);
	for (int i = 0; i < 5;i++)
	for (int j = 0; j < 5; j++)
	{
		double h=U(point0[i], point0[j]);
		L.at<double>(i, j) = U(point0[i], point0[j]);
	}
	for (int i = 0; i < 5; i++)
	{
		L.at<double>(i, 5) = 1;
		L.at<double>(i, 6) = point0[i].x;
		L.at<double>(i, 7) = point0[i].y;
	}
	for (int i = 0; i < 5; i++)
	{
		L.at<double>(5, i) = 1;
		L.at<double>(6, i) = point0[i].x;
		L.at<double>(7, i) = point0[i].y;
	}
	for (int i = 5; i < 8;i++)
	for (int j = 5; j < 8; j++)
	{
		L.at<double>(i,j) = 0;
	}
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++)
			cout<<L.at<double>(i,j)<<"  ";
		cout<<endl;}
	cv::Mat Y(8, 2, CV_64FC1);
	for (int i = 0; i < 5; i++)
	{
		Y.at<double>(i, 0) = point1[i].x;
		Y.at<double>(i, 1) = point1[i].y;
	}
	for (int i = 5; i < 8; i++)
	{
		Y.at<double>(i, 0) = 0;
		Y.at<double>(i, 1) = 0;
	}
	cv::Mat result;
	cv::Mat result1;
	cv::Mat Li;
	invert(L, Li);
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			cout<<Li.at<double>(i,j)<<endl;
	result1=Li*Y;
	transpose(result1, result);

	cv::Mat w1 = result.col(0);
	cv::Mat w2 = result.col(1);
	cv::Mat w3 = result.col(2);
	cv::Mat w4 = result.col(3);
	cv::Mat w5 = result.col(4);
	cv::Mat a1 = result.col(5);
	cv::Mat ax = result.col(6);
	cv::Mat ay = result.col(7);
	cv::Mat final;

	for (int i = 0; i<img.cols; i++)
	for (int j = 0; j<img.rows; j++)
	{
		double xx, yy;
		CvPoint pij;
		pij.x = i;
		pij.y = j;
		final=a1 + i*ax + j*ay+ U(point0[0],pij)*w1 + U(point0[1],pij)*w2 + U(point0[2],pij)*w3 + U(point0[3],pij)*w4 + U(point0[4],pij)*w5;

		xx = final.at<double>(0, 0);
		yy = final.at<double>(1, 0);

		if (xx<1 || xx>img.cols - 2 || yy<1 || yy>img.rows - 2)
		{
		}
		else
		{
			if(c==0)
				near(xx,yy,i,j,img,img1);
			else if(c==1)
				bilinear(xx,yy,i,j,img,img1);
			else if(c==2)
				bicubic(xx,yy,i,j,img,img1);
		}
	}
}
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
int main(int argc, char* argv[])  
{  
    Mat img = imread("E:\\example.png"); //声明Mat变量并调入照片   
    if(!img.data) //判断图片调入是否成功   
        return -1; //调入图片失败则退出  
	Mat img1=img.clone();
	/*for(int i=0;i<img.cols;i++)
		for(int j=0;j<img.rows;j++)
			img2.at<double>(i,j)=0;*/

	CvPoint point0[5];
	CvPoint point1[5];
	point0[0]=cvPoint(200,200);
	point0[1]=cvPoint(201,203);
	point0[2]=cvPoint(210,205);
	point0[3]=cvPoint(221,209);
	point0[4]=cvPoint(223,215);
	point1[0]=cvPoint(234,217);
	point1[1]=cvPoint(239,224);
	point1[2]=cvPoint(251,232);
	point1[3]=cvPoint(263,245);
	point1[4]=cvPoint(270,259);
	int space=0;
	//while (space !=1){
			int n;
			cout<<"请输入图像变换类型n："<<endl;
			cout<<"（0:凸面镜变形 1：凹面镜变形 2：扭曲变形 3：B样条变形 4：TPS变形）"<<endl;
			cin>>n;
			int m;
			cout<<"请输入差值类型m："<<endl;
			cout<<"(0:最近邻插值 1：双线性插值 2：双三次插值)"<<endl;
			cin>>m;
			switch(n){
			case 0: sphere(img,img1,m);break;
			case 1: sphere1(img,img1,m);break;
			case 2: twist(img ,img1,m);break;
			case 3: B_spline(200,200,210,210,img,img1,m);break;
			case 4:	
				{
					for(int i=0;i<img.cols;i++)
					for(int j=0;j<img.rows;j++){
						img1.at<Vec3b>(i,j)[0]=0;
						img1.at<Vec3b>(i,j)[1]=0;
						img1.at<Vec3b>(i,j)[2]=0;
					}
					TPS(point0,point1,img,img1,m);	
					break;}
			default:break;
			}
			//sphere(img,img1);
			//B_spline(200,200,210,210,img,img1);
	
			namedWindow("example", CV_WINDOW_AUTOSIZE); //创建窗口,并确定其为大小不可变类型窗口   
			imshow("example", img1); //显示图片。如果你不介意窗口大小可变，可以直接注释掉上一句。因为imshow可以直接创建窗口  

			//cout<<"请输入：（0：继续 1：退出）"<<endl;
			//cin>>space;
		//}
  
    waitKey(0); //等待按键   
    return 0;  
}  