/**************************************
void CImgProcess::AddRayleigh(CImgProcess *pTo)
功能：			对图像添加瑞利噪声
参数：			CImgProcess *pTo：输出的图像指针
返回值：		无
****************************************/

void CImgProcess::AddRayleigh(CImgProcess *pTo)
{
	int w=m_pBMIH->biWidth;
	int h=m_pBMIH->biHeight;
	int i,j;
	double rate=0.99;
	double sigma=10.0;
	double a,a0,a1,a2,a3;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
			{
				double t;
				t=double(rand())/RAND_MAX;
				if(t<rate)
				{
					a0=double(rand())/RAND_MAX;
					a1=double(rand())/RAND_MAX;
					a2=log(a0)*cos(2*PI*a1);
					a3=log(a1)*cos(2*PI*a0);
					a2*=sigma;
					a3*=sigma;
					a=sqrt(a2*a2+a3*a3);
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