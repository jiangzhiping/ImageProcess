/******************************************************************
BOOL CImgProcess::Histst(CImgProcess *pTo,double *pdStdHist)
功能：			图像的灰度直方图规定化方法
参数：			CImgProcess *pTo：输出CImgProcess对象的指针
				double *pdStdHist：标准直方图数组（要求已经归一化的直方图）
返回值：		BOOL类型，true为成功，false为失败
****************************************************************/

BOOL CImgProcess::Histst(CImgProcess *pTo,double *pdStdHist)
{
	int i,j;
	if(m_pBMIH->biBitCount!=8)
		return false;
	BYTE gray;
	int target;
	double pdHist[256];
	this->GenHist(pdHist);

	double dTemp;
	int pdTran[256];
	memset(pdTran,-1,sizeof(int)*256);

	//求标准直方图的均衡化变换矩阵
	for(i=0;i<256;i++)
	{
		dTemp=0;
		for(BYTE k=0;k<i;k++)
			dTemp+=*(pdStdHist+k);
		*(pdTran+(int)(0.5+255*dTemp))=i;
	}
	//去除均衡化变换矩阵中的间断点--插值
	{
		i=0,j=0;
		while(i<255)
		{
			if(*(pdTran+i+1)!=-1)
			{
				i++;
				continue;
			}
			j=1;
			while((*(pdTran+i+j)==-1)&&((i+j)<=255))
			{
				*(pdTran+i+j)=*(pdTran+i);
				j++;
			}
		}
	}

	//对原图像首先进行灰度均衡化后再进行规定化
	for(i=0;i<m_pBMIH->biHeight;i++)
	{
		for(j=0;j<m_pBMIH->biWidth;j++)
		{
			dTemp=0;
			gray=GetGray(j,i);
			for(BYTE k=0;k<gray;k++)
				dTemp+=*(pdHist+k);
			target=*(pdTran+(int)(255*dTemp));
			if(target<0)
				target=0;
			if(target>255)
				target=255;
			pTo->SetPixel(j,i,RGB(target,target,target));
		}
	}
	return true;
}