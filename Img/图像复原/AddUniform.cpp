/************************************
void CImgProcess::AddUniform(CImgProcess *pTo)
功能：				对图像添加均匀噪声
参数：				CImgProcess *pTo：输出的图像指针
返回值：			无
************************************/

void CImgProcess::AddUniform(CImgProcess *pTo)
{
	int w=m_pBMIH->biWidth;
	int h=m_pBMIH->biHeight;
	int i,j;
	double rate=0.99;
	double a;
	double low=-20.0;
	double high=20.0;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			double t;
			t=double(rand())/RAND_MAX;
			if(t<rate)
			{
				a=double(rand())/RAND_MAX;
				unsigned char ch=GetGray(j,i);
				a*=(high-low);
				a+=low;
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