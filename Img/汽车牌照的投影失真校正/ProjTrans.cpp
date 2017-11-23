/*****************************************
MYPOINT CImgProcess::ProjTrans(CPoint pt,double* pDbProjPara)
功能：			根据变换参数对点pt实施投影变换
参数：			CPoint pt：要进行投影变换的点坐标
				double* pDbProjPara：变换参数
返回值：		MYPOINT
**************************************/

MYPOINT CImgProcess::ProjTrans(CPoint pt,double *pDbProjPara)
{
	MYPOINT retPt;
	retPt.x=pDbProjPara[0]*pt.x+pDbProjPara[1]*pt.y+pDbProjPara[2]*pt.x*pt.y+pDbProjPara[3];
	retPt.y=pDbProjPara[4]*pt.x+pDbProjPara[5]*pt.y+pDbProjPara[6]*pt.x*pt.y+pDbProjPara[7];
	return retPt;
}