/**************************************************
BOOL CImgProcess::LinTran(CImgProcess* pTo, double dFa, double dFb)

功能：
图像的线性变换方法

参数：
CImgProcess * pTo
输出CImgProcess对象的指针
double dFa
线性变换斜率
double dFb
线性变换截距

返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::LinTran(CImgProcess* pTo, double dFa, double dFb)
{
	// 首先检查图像是否是8位灰度图像
	if (m_pBMIH->biBitCount!=8) return false;

	BYTE gray;		// 临时变量,存储当前光标像素的灰度值
	int target;		// 临时变量,存储当前光标像素的目标值

	for (int i=0; i<m_pBMIH->biHeight; i++)
	{
		for (int j=0; j<m_pBMIH->biWidth; j++)
		{
			gray = GetGray(j, i);

			target = int (dFa * gray + dFb);

			if (target < 0) target = 0;
			if (target > 255) target = 255;

			// 写入目标图像
			pTo->SetPixel(j, i, RGB(target, target, target));
		}
	};

	return true;
}