/********************************
void CImgProcess::FreqLaplace(double *pdFilter)
功能：			生成对应输入图像的频域拉普拉斯滤波器
参数：			double *pdFilter：指向输出滤镜的指针
返回值：		无
********************************/

void CImgProcess::FreqLaplace(double *pdFilter)
{
	//计算滤镜大小
	LONG w=GetFreqWidth();
	LONG h=GetFreqHeight();
	//滤镜产生过程
	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			//先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的4个部分
			//在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
			pdFilter[(i<h/2?i+h/2:i-h/2)*w+(j*w/2?j+w/2:j-w/2)]=
			-(pow((double)(i-h/2),2)+pow((double)(j-w/2),2));
		}
	}
}