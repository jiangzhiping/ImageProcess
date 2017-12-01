/***********************************
void CImgProcess::RGB2CMY(CImgProcess *pTo)
功能：			把一幅RGB图转CMY图
参数：			CImgProcess *pTo：目标输出图像的CImgProcess指针
返回值：		无
**************************************/

void CImgProcess::RGB2CMY(CImgProcess *pTo)
{
	int nHeight=GetHeight();
	int nWidth=GetWidthPixel();

	int i,j;
	for(i=0;i<nHeight;i++)
	{
		for(j=0;j<nWidth;j++)
		{
			COLORREF RGBPixel=GetPixel(j,i);
			//抽取RGB分量
			int R=GetRValue(RGBPixel);
			int G=GetRValue(RGBPixel);
			int B=GetRValue(RGBPixel);
			int C,M,Y;

			C=255-R;
			M=255-G;
			Y=255-B;

			//将分量联合形成CMY图像
			pTo->SetPixel(j,i,RGB(C,M,Y));
		}
	}
}