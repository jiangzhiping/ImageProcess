/**************************************************
BOOL CImgProcess::GenHist(double * pdHist, int n)

功能：
生成图像的灰度直方图

参数：
double * pdHist
输出的灰度直方图数组
BYTE n
灰度直方图的灰度级数（段数）
返回值：
BOOL类型，true为成功，false为失败
***************************************************/

BOOL CImgProcess::GenHist(double * pdHist, int n)
{
	// 首先检查图像的类型
	if (m_pBMIH->biBitCount!=8) return false;

	// 检查n范围
	if ((n<=0)||(n>256)) return false;

	// 计算分段因子
	double dDivider;

	memset(pdHist, 0, n * sizeof(double));
	dDivider = 256.0 / (double)n;

	BYTE bGray;	// 临时变量,存储当前光标像素的灰度值
	for (int i=0; i<m_pBMIH->biHeight; i++)
	{
		for (int j=0; j<m_pBMIH->biWidth; j++)
		{
			bGray = GetGray(j, i);
			pdHist[(int)(bGray / dDivider)]++;	// 指定的灰度区间自加
		}
	};

	UINT square = m_pBMIH->biWidth * m_pBMIH->biHeight;

	for (int k=0; k<n; k++) 
	{
		pdHist[k]=pdHist[k]/square;
	}

	return true;
}