/******************************
void CImgProcess::FreqFilt(CImgProcess *pTo,double *pdFilter,BYTE bFillColor)
功能：		执行频域滤波操作。请首先使用相应的滤镜生成函数生成pdFilter滤镜
参数：		CImgProcess *pTo:指向输出图像的指针
			double *pdFilter:给定的频域滤镜
			BYTE bFillColor:用来补齐原图像使用的颜色，默认为（白色）。建议与图像右侧和底部边缘附近的颜色尽量保持一致。
返回值：	无
*******************************/

void CImgProcess::FreqFilt(CImgProcess *pTo,double *pdFilter,BYTE bFillColor)
{
	//计算滤镜大小
	LONG w=GetFreqWidth();
	LONG h=GetFreqHeight(); 
	//定义临时频域图像（逐行连续存储）
	complex<double> *cdFreImg=new complex<double>[w*h];
	//首先对原图像进行傅里叶变换，如果宽度不是2的整数次幂则采用边界填充的方式
	FFT2(NULL,1,cdFreImg,bFillColor);
	//然后执行核心滤波操作，将频域图像和滤镜逐元素相乘
	for(LONG i=0;i<w*h;i++)
		cdFreImg[i]=cdFreImg[i]*pdFilter[i];
	//最后将滤波结果进行傅里叶反变换
	IFFT2(pTo,cdFreImg,w,h,GetWidthPixel(),GetHeight());
	//最后2个参数指定了输出图像的大小与原始图像相同（裁剪掉了填充的边界）
	//由于动态范围问题，如果原始图像存在较明显的灰度分界
	//不能完全保证滤波结果在灰度层次上与原图像保持类同
	//因此可能需要对输出图像再进行点运算操作
	//删除临时频域图像
	delete cdFreImg;
}			