/****************************************************************
void CImgProcess::ImMove(CImgProcess *pTo,int x,int y)
功能：			平移图像
注：			图像范围不变
参数：			CImgProcess *pTo：处理后得到的图像的CImgProcess指针
				int x：水平右移距离
				int y：垂直下移距离
返回值：		无
****************************************************************/

void CImgProcess::ImMove(CImgProcess *pTo,int x,int y)
{
	int nHeight=pTo->GetHeight();
	int nWidth=pTo->GetWidthPixel();

	int i,j;
	if(x>nWidth||y>nHeight)
	{
		MessageBox(NULL,"超过图片大小","错误",MB_OK|MB_ICONERROE);
		return;
	}
	for(i=0;i<nWidth;i++)
	{
		for(j=0;j<nHeight;j++)
		{
			if(i-x>0&&i-x<nWidth&&j-y>0&&j-y<nHeight)
				pTo->SetPixel(i,j,GetPixel(i-x,j-y));
			else
				pTo->SetPixel(i,j,RGB(255,255,255));
		}
	}
}