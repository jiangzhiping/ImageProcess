/***************************************************
void CImgProcess::ProMat(double** ppDbMat,double *pDbSrc2,double* pDbDest,int y,int x,int z)
功能：			计算两矩阵的乘积
注：			该函数计算两个矩阵的相乘，然后将相乘的结果存放在pDbDest中。
				其中pDbSrc1的大小为x*z，pDbSrc2的大小为z*y，pDbDest的大小为x*y
参数：			double* pDbSrc1：指向相乘矩阵的内存
				double* pDbSrc2：指向相乘矩阵的内存
				double* pDbDest：存放矩阵相乘运行结果的内存指针
				int x：矩阵的尺寸
				int y：矩阵的尺寸
				int z：矩阵的尺寸
返回值：		无
******************************************************/

void CImgProcess::ProMat(double** ppDbMat,double* pDbSrc2,double* pDbDest,int y,int x,int z)
{
	int nCnt=0;
	int i,j;
	double *pDbSrc1=new double(m_nBasePt*m_nBasePt);
	for(i=0;i<m_nBasePt;i++)
	{
		for(j=0;j<m_nBasePt;j++)
			pDbSrc1[nCnt++]=ppDbMat[i][j];//保存要求逆的输入矩阵
	}
	//矩阵相乘
	for(i=0;i<y;i++)
	{
		for(j=0;j<x;j++)
		{
			pDbDest[i*x+j]=0;
			for(int m=0;m<z;m++)
				pDbDest[i*x+j]+=pDbSrc1[i*z+m]*pDbSrc2[m*x+j];
		}
	}
	//将结果复制回系数矩阵ppDbMat
	nCnt=0;
	for(i=0;i<m_nBasePt;i++)
	{
		for(j=0;j<m_nBasePt;j++)
			ppDbMat[i][j]=pDbSrc1[nCnt+1];
	}
	delete[] pDbSrc1;
}