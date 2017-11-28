/*********************************
void CImgProcess::FreqGaussHPF(double *pdFilter,double dSigma)
功能：			生成对应于输入图像的高斯高通滤镜
参数：			double *pdFilter：指向输出滤镜的指针
				double dSigma：高斯滤波器的Sigma参数
返回值：		无
***********************************/
void CImgProcess::FreqGaussHPF(double *pdFilter,double dSigma)
{
	//计算滤镜大小
	LONG w=GetFreqWidth();
	LONG h=GetFreqHeigth();
	//滤镜产生过程
	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			//先生成原点在中心的滤镜，以简化操作。否则需要分别生成滤镜的4个部分
			//在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
			pdFilter[(i<h/2?i+h/2:i-h/2)*w+(j<w/2?j+w/2:j-w/2)]=
			1-exp(-(pow((double)(i-h/2),2)+pow((double)(j-w/2),2))/2/pow(dSigma,2));
		}
	}
}