/***********************************************
void CImgProcess::Transpose(CImgProcess *pTo)
功能：		图像的转置
注：		图像水平竖直方向互换，图像大小不变
参数：		CImgProcess *pTo：处理后得到的图像的CImgProcess指针
返回值：	无
************************************************/

void CImgProcess::Transpose(CImgProcess *pTo)
{
	int nHeight=pTo->GetHeight();
	int nWidth=pTo->GetWidthPixel();
	int i,j;
	for(i=0;i<nWidth;i++)
	{
		for(j=0;j<nHeight;j++)
		{
			if(j<nWidth&&i<nHeight)
				pTo->SetPixel(i,j,GetPixel(j,i));
			else
				pTo->SetPixel(i,j,RGB(255,255,255));
		}
	}
}