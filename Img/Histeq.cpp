/**************************************************************
BOOL CImgProcess:Histeq(CImgProcess *pTo)
功能：		图像的灰度直方图均衡化方法
参数：		CImgProcess *pTo
			输出CImgProcess对象的指针
返回值：	BOOL类型，true为成功，false为失败
***************************************************************/

BOOL CImgProcess::Histeq(CImgProcess *pTo)
{
	if(m_pBMIH->bitBitCount!=8)
		return false;
	BYTE gray;
	int target;
	double pdHist[256];
	double dTemp;
	this->GenHist(pdHist);
	for(int i=0;i<m_pBMIH->biHeight;i++)
	{
		for(int j=0;j<m_pBMIH->biWidth;j++)
		{
			dTemp=0;
			gray=GetGray(j,i);
			for(BYTE k=0;k<gray;k++)
				dTemp+=*(pdHist+k);
			target=255*dTemp;
			if(target<0)	target=0;
			if(target>255)	target=255;
			pTo->SetPixel(j,i,RGB(target,target,target));
		}
	}
	return true;
}