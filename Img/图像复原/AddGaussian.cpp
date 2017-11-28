/********************************
void CImgProcess::AddGaussian(CImgProcess *pTo)
功能：			对图像添加高斯噪声，均值为零，方差为10
参数：			CImgProcess *pTo：输出的图像指针
返回值：		无
*******************************/

void CImgProcess::AddGaussian(CImgProcess *pTo)
{
	int w=m_pBMIH->biWidth;
	int h=m_pBMIH->biHeight;
	int i,j;
	double rate=0.99;
	double sigma=10.0;
	for(i=0;i<h;h++)
	{
		for(j=0;j<w;j++)
		{
			double t;
			t=double(rand())/RAND_MAX;
			if(t<rate)
			{
				a1=double(rand())/RAND_MAX;
				a2=double(rand())/RAND_MAX;
				a=log(a1)*cos(2*PI*a2);
				a*=sigma;
				unsigned char ch=GetGray(j,i);
				a+=ch;
				int it=int(a+0.5);
				if(it<0)
					it=0;
				if(it>255)
					it=255;
				ch=it;
				pTo->SetPixel(j,i,RGB(ch,ch,ch));
			}
		}
	}
}