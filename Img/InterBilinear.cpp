/*********************************************
int CImgProcess::InterBilinear(double x,double y)
功能：			双线性插值
参数：			double x：需要计算插值的横坐标
				double y：需要计算插值的纵坐标
返回值：		int插值的结果
*********************************************/

int CImgProcess::InterBilinear(double x,double y)
{
	if(int(y)==300)
		int cc=1;
	//4个最邻近像素的坐标(i1,j1),(i2,j1),(i1,j2),(i2,j2)
	int x1,x2;
	int y1,y2;
	//4个最邻近像素值
	unsigned char f1,f2,f3,f4;
	//两个插值中间值
	unsigned char f12,f34;
	double epsilon=0.0001;

	//计算4个最邻近像素的坐标
	x1=(int)x;
	x2=x1+1;
	y1=(int)y;
	y2=y1+1;

	int nHeight=GetHeight();
	int nWidth=GetWidthPixel();
	if((x<0)||(x>nWidth-1)||(y<0)||(y>nHeight-1))
	{
		//如果计算的点不在原图范围内，返回-1
		return -1;
	}
	else
	{
		if(fabs(x-nWidth+1)<=epsilon)
		{
			//如果计算的点在图像右边缘上
			if(fabs(y-nHeight+1)<=epsilon)
			{
				//如果计算的点正好是图像最右下角那一个像素，直接返回该点像素值
				f1=(unsigned char)GetGray(x1,y1);
				return f1;
			}
			else
			{
				//如果是在图像右边缘上且不是最后一点，直接一次插值即可
				f1=(unsigned char)GetGray(x1,y1);
				f3=(unsigned char)GetGray(x1,y2);
				//返回插值结果
				return ((int)(f1+(y-y1)*(f3-f1)));
			}
		}
		else if(fabs(y-nHeight+1)<=epsilon)
		{
			//如果计算的点在图像下边缘上且不是最后一点，直接一次插值即可
			f1=(unsigned char)GetGray(x1,y1);
			f2=(unsigned char)GetGray(x2,y1);
			//返回插值结果
			return ((int)(f1+(x-x1)*(f2-f1)));
		}
		else
		{
			//计算4个最邻近像素值
			f1=(unsigned char)GetGray(x1,y1);
			f2=(unsigned char)GetGray(x2,y1);
			f3=(unsigned char)GetGray(x1,y2);
			f4=(unsigned char)GetGray(x2,y2);
			//插值1
			f12=(unsigned char)(f1+(x-x1)*(f2-f1));
			//插值2
			f34=(unsigned char)(f3+(x-x1)*(f4-f3));
			//插值3
			return ((int)(f12+(y-y1)*(f34-f12)));
		}
	}
}