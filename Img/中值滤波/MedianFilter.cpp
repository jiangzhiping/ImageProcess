/********************************
void CImgProcess::MedianFilter(CImgProcess *pTo,int nFilterH,int nFilterW,
								int nFilterMY,int nFilterMX)
功能：			对突发性噪声，如椒盐噪声，有较好的抑制效果
参数：			CImgProcess *pTo：目标图像的CImgProcess指针
				int nFilterH：滤波器的高度
				int nFilterW：滤波器的宽度
				int nFilterMX：滤波器的中心元素Y坐标
				int nFilterMY：滤波器的中心元素X坐标
返回值：		无
*******************************/

void CImgProcess::MedianFilter(CImgProcess *pTo,int nFilterH,int nFilterW,int nFilterMY,int nFilterMX)
{
	pTo->InitPixel(0);//初始化目标图像
	int i,j,k,l;
	int nHeight=GetHeight();
	int nWidth=GetWidthPixel();
	int nGray;
	int *pAryGray;//领域像素数组
	pAryGray=new int[nFilterH*nFilterW];
	//逐行扫描图像，进行中值滤波
	for(i=nFilterMY;i<nHeight-nFilterH+nFilterMY+1;i++)//行（除去边缘几行）
	{
		for(j=nFilterMX;j<nWidth-nFilterW+nFilterMX+1;j++)//列（除去边缘几列）
		{
			//读取滤波器数组
			for(k=0;k<nFilterH;k++)
			{
				for(l=0;l<nFilterW;l++)
				{
					//原图像第i+k-nFilterMY行，第j+1-nFilterMX列的像素值
					nGray=GetGray(j+l-nFilterMX,i+k-nFilterMY);
					//保存像素值
					pAryGray[k*nFilterW+l]=nGray;
				}
			}
			nGray=GetMedianValue(pAryGray,nFilterH*nFilterW);//通过排序获取中值
			pTo->SetPixel(j,i,RGB(nGray,nGray,nGray));//以中值作为响应
		}
	}
	delete[] pAryGray;
}