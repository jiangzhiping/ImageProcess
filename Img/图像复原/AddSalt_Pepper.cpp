/*******************************
void CImgProcess::AddSalt_Pepper(CImgProcess *pTo)
功能：			对图像添加椒盐噪声
参数：			CImgProcess *pTo：输出的图像指针
返回值：		无
*******************************/

void CImgProcess::AddSalt_Pepper(CImgProcess *pTo)
{
	int w=m_pBMIH->biWidth;
	int h=m_pBMIH->biHeigth;
	int i,j;
	double rate=0.02;
	double a;
	for(i=0;i<h,i++)
	{
		for(j=0;j<w;j++)
		{
			double t;
			t=double(rand())/RAND_MAX;
			if(t<rate)
			{
				a=double(rand())/RAND_MAX;
				if(a<0.5)
					pTo->SetPixel(j,i,RGB(0,0,0));
				else
					pTo->SetPixel(j,i,RGB(255,255,255))
			}
		}
	}
}