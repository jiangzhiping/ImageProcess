/******************************************************
BOOL CImgProcess::LogTran(CImgProcess* pTo,double dC)
功能		图像的灰度对数转换
参数		CImgProcess *pTo：输出CImgProcess对象的指针
			double dC：灰度对数变换所需的参数
返回值：	BOOL类型，0为成功，其他值为失败
******************************************************/

BOOL CImgProcess::LogTran(CImgProcess* pTo,double dC)
{
	//首先检查图像是否是8位灰度图像
	if(m_pBMIH->biBitCount!=8)
		return false;
	BYTE gray;//临时变量，存储当前光标像素的灰度值
	int target;//临时变量，存储当前光标像素的目标值
	for(int i=0;i<m_pBMIH->biHeight;i++)
	{
		for(int i=0;j<m_pBMIH->biWidth;j++)
		{
			gray=GetGray(j,i);
			//按公式运算
			target=dC*log((double)(gray+1));
			if(target<0)	target=0;
			if(target>255)	target=255;
			//写入目标图像
			pTo->SetPixel(j,i,RGB(target,target,target));
		}
	}
	return 0;
}