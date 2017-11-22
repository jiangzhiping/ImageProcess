/****************************************************
void CImgProcess::Scale(CImgProcess *pTo,double times)
功能：		图像的等比例缩放
注：		包括扩大缩小，图像大小不变
参数：		CImgProcess *pTo：处理后得到的图像的CImgProcess指针
			double times：缩放因子
返回值：	无
*****************************************************/

void CImgProcess::Scale(CImgProcess *pTo,double times)
{
	int nHeight=pTo->GetHeight();
	int nWidth=pTo->GetWidthPixel();

	int i,j;
	for(i=0;i<nWidth;i++)
	{
		for(j=0;j<nHeight;j++)
		{
			if(int(i*1/times+0.5)<nWidth&&int(j*1/times+0.5)<nHeight)
				pTo->SetPixel(i,j,GetPixel(int(i*1/times+0.5),int(j*1/times+0.5)));
			else
				pTo->SetPixel(i,j,RGB(255,255,255));
		}
	}
}