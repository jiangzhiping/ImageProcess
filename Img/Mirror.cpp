/*******************************************************************
void CImgProcess::HorMirror(CImgProcess *pTo)
功能：			图像的水平镜像
注：			图像的左右镜像
参数：			CImgProcess *pTo：处理后得到的图像的CImgProcess指针
返回值：		无
*******************************************************************/
void CImgProcess::HorMirror(CImgProcess *pTo)
{
	int nHeight=pTo->GetHeight();
	int nWidth=pTo->GetWidthPixel();
	int i,j;
	int u;
	for(i=0;i<nWidth;i++)
	{
		u=nWidth-i-1;
		for(j=0;j<nHeight;j++)
			pTo->SetPixel(i,j,GetPixel(u,j));
	}
}

/*******************************************************************
void CImgProcess::VerMirror(CImgProcess *pTo)
功能：			图像的竖直镜像
注：			图像的上下镜像
参数：			CImgProcess *pTo：处理后得到的图像的CImgProcess指针
返回值：		无
*******************************************************************/

void CImgProcess::VerMirror(CImgProcess *pTo)
{
	int nHeight=pTo->GetHeight();
	int nWidth=pTo->GetWidthPixel();
	int i,j;
	int u=0;
	for(i=0;i<nWidth;i++)
	{
		for(j=0;j<nHeight;j++)
		{
			u=nHeight-j-1;
			pTo->SetPixel(i,j,GetPixel(i,u));
		}
	}

}