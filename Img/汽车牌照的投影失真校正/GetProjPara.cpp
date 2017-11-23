/*****************************************************
void CImgProcess::GetProjPara(CPoint *pPointBase,CPoint *pPointSampl,double *pDbProjPara)
功能：		根据基准点对儿确定变换参数
参数：		CPoint *pPointBase：基准图像的基准点
			CPoint *pPointSamp1：输入图像的基准点
			double *pDbProjPara：变换参数
返回值：	无
******************************************************/

void CImgProcess::GetProjPara(CPoint *pPointBase,CPoint *pPointSampl,double *pDbProjPara)
{
	int i;
	//投影线性方程的系数矩阵
	double **ppParaMat;
	//m_nBasePt对数儿
	ppParaMat=new double*[m_nBasePt];
	for(i=0;i<m_nBasePt;i++)
		ppParaMat[i]=new double[m_nBasePt];
	for(i=0;i<m_nBasePt;i++)
	{
		ppParaMat[i][0]=pPointBase[i].x;
		ppParaMat[i][1]=pPointBase[i].y;
		ppParaMat[i][2]=pPointBase[i].x*pPointBase[i].y;
		ppParaMat[i][3]=1;
	}
	double *pResMat;//结果矩阵
	pResMat=new double[m_nBasePt];
	//计算前4个系数c1,c2,c3,c4
	for(i=0;i<m_nBasePt;i++)
		pResMat[i]=pPointSampl[i].x;
	//采用左乘系数矩阵的逆矩阵的方法解出投影变换的前4个系数c1,c2,c3,c4
	InvMat(ppParaMat,m_nBasePt);
	ProdMat(ppParaMat,pResMat,pDbProjPara,m_nBasePt,1,m_nBasePt);//求出前4个参数

	for(i=0;i<m_nBasePt;i++)//计算后4个系数c5,c6,c7,c8
		pResMat[i]=pPointSampl[i].y;
	//采用左乘系数矩阵的逆矩阵的方法解出投影变换的后4个系数c5,c6,c7,c8
	ProdMat(ppParaMat,pResMat,pDbProjPara+m_nBasePt,m_nBasePt,1,m_nBasePt);//求出后4个参数

	//释放空间
	delete[] pResMat;
	for(i=0;i<m_nBasePt;i++)
		delete[] ppParaMat[i];
	delete[] ppParaMat;
}