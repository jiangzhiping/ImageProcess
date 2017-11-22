/*********************************************************************
BOOL CImgProcess:ParLinTran(CImg *pTo,BYTE x1,BYTE x2,BYTE y1,BYTE y2)
功能：			图像的灰度分段线性变换
限制：			x1<x2
参数：			CImg *pTo：输出CImg对象的指针
				BYTE x1：分段线性变换第一点的横坐标
				BYTE x2：分段线性变换第二点的横坐标
				BYTE y1：分段线性变换第一点的纵坐标
				BYTE y2：分段线性变换第二点的纵坐标
返回值：		BOOL类型，TRUE为成功，FALSE为失败
**********************************************************************/

BOOL CImgProcess:ParLinTran(CImgProcess *pTo,BYTE x1,BYTE x2,BYTE y1,BYTE y2)
{
	if(m_pBMIH->biBitCount!=8)
		return FALSE;
	if(x1>x2)
		return FALSE;
	BYTE gray;
	int target;
	for (int i = 0; i < m_pBMIH->biHeight; ++i)
	{
		for (int j = 0; j < m_pBMIH->biWidth; ++j)
		{
			gray=GetGray(j,i);
			//
			if(gray<=x1)
				target=y1*gray/x1;
			else if(gray<=x2)
				target=(y2-y1)*(gray-x1)/(x2-x1)+y1;
			else
				target=(255-y2)*(gray-x2)/(255-x2)+y2;
			if(target<0) target=0;
			if(target>255) target=255;
			pTo->SetPixel(j,i,RGB(target,target,target));
		}
	}
	return TRUE;

}

//输出的临时对象
CImgProcess imgOutput=imgInput;
//分段线性变换
imgInput.ParLinTran(&imgOutput,dlg.m_bS1,dlg.m_bS2,dlg.m_bT1,dlg.m_bT2);
//将结果返回给文档类
pDoc->mImage=imgOutput;
