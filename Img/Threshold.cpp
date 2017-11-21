/*******************************************************
void CImgProcess::Threshold(CImgProcess *pTo,BYTE nThres)
功能：		图像的阈值变换
参数：		CImgProcess *pTo：输出CImgProcess对象的指针
			BYTE nThres：设置的基准阈值
返回值：	无
*******************************************************/

void CImgProcess:Threshold(CImgProcess *pTo,BYTE nThres)
{
	int i,j;
	BYTE bt;
	for(i=0;i<m_pBMIH->biHeight;i++)
	{
		for(j=0;j<m_pBMIH->biWidth;j++)
		{
			//小于nThres的设为0，其他设为255，从而得到二值图像
			bt=GetGray(j,i);
			if(bt<nThres)
				bt=0;
			else
				bt=255;
			pTo->SetPixel(j,i,RGB(bt,bt,bt));
		}
	}
}