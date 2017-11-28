/************************************
void CImgProcess::FreqIdealLPF(double *pdFilter,int nFreq)
功能：			生成对应于输入图像的频域理想低通滤镜
参数：			double *pdFilter：指向输出滤镜的指针
				int nFreq：截止频率
返回值：		无
************************************/
void CImgProcess::FreqIdealLPF(double *pdFilter,int nFreq)
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
			if(sqrt(pow((double)(i-h/2),2)+pow((double)(j-w/2),2))>nFreq)
			{
				//在写入时对滤镜进行必要处理，按照MATLAB函数ifftshift的原则平移
				pdFilter[(i<h/2?i+h/2:i-h/2)*w+(j<w/2?j+w/2:j-w/2)]=0;
			}
			else
			{
				pdFilter[(i<h/2?i+h/2:i-h/2)*w+(j<w/2?j+w/2:j-w/2)]=1;
			}
		}
	}
}

//输出临时对象
CImgProcess imgOutput=imgInput;
//计算需要生成滤镜的大小
LONG w=imgInput.GetFreqWidth();
LONG h=imgInput.GetFreqHeight();
//生成频域滤镜
double *pdFreqFilt=new double[w*h];
imgInput.FreqIdealLPF(pdFreqFilt,dlg.m_nFreq);
//其中dlg类的成员函数m_nFreq为用户设置的截止频率
//应用滤镜
imgInput.FreqFilt(&imgOutput,pdFreqFilt);





