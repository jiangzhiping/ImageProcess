/****************************
BOOL CImgProcess::FreqWienerFilter(double *pdFilter,int nRad,double K)
功能：			生成对应于维纳滤波的滤镜
参数：			double *pdFilter：指向输出滤镜的指针
				int nRad：逆滤镜的半径
返回值：		BOOL类型，true为成功，false为失败
*****************************/

BOOL CImgProcess::FreqWienerFilter(double *pdFilter,int nRad,double K)
{
	if(m_pBMIH->biBiCount!=8)
		return false;
	//计算滤镜大小
	LONG w=GetFreqWidth();
	LONG h=GetFreqHeight();
	//滤镜产生过程
	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			//在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
			double f1=((i-h/2)*(i-h/2)+(j-w/2)*(j-w/2));
			f1=pow(f1,5.0/6);
			f1*=-0.0025;
			f1=exp(f1);
			pdFilter[(i<h/2?i+h/2:i-h/2)*w+(j<w/2?j+w/2:j-w/2)]=1.0*f1*f1/((f1*f1+K)*(f1+0.000001));
		}
	}
	return true;
}