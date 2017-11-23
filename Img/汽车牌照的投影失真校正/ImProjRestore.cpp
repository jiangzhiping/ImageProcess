/**************************************
BOOL CImgProcess::ImProjRestore(CImgProcess *pTo,CPoint *pPointBase,CPoint *pPointSampl,bool bInterp)
功能：		实施投影变形校正
参数：		CImgProcess* pTo：校准后图像的CImgProcess指针
			CPoint *pPointBase：基准图像的基准点数组
			CPoint *pPointSampl：输入图像的基准点数组
			bool bInterp：是否使用（双线性）插值
返回值：	MYPOINT
*************************************/

BOOL CImgProcess::ImProjRestore(CImgProcess *pTo,CPoint *pPointBase,CPoint *pPointSampl,bool bInterp)
{
	double *pDbProjPara=new double[m_nBase*2];
	GetProjPara(pPointBase,pPointSampl,pDbProjPara);
	//用得到的变换系数对图像实时变换
	int i,j;
	int nHeight=pTo->GetHeight();
	int nWidth=pTo->GetWidthPixel();
	for(i=0;i<nHeight;i++)
	{
		for(j=0;j<nWidth;j++)
		{
			//对每个点(j,i)，计算其投影失真后的点ptProj
			MYPOINT ptProj=ProjTrans(CPoint(j,i),pDbProjPara);
			if(bInterp)
			{
				int nGray=InterBilinear(ptProj.x,ptProj.y);
				if(nGray>=0)
					pTo->SetPixel(j,i,RGB(nGray,nGray,nGray));
				else
					pTo->SetPixel(j,i,RGB(255,255,255));
			}
			else
			{
				int ii=ptProj.y+0.5;
				int jj=ptProj.x+0.5;
				if(ii>0&&ii<GetHeight()&&jj>0&&jj<GetWidthPixel())
					pTo->SetPixel(j,i,GetPixel(jj,ii));
				else
					pTo->SetPixel(j,i,RGB(255,255,255));
			}
		}
	}
	delete pDbProjPara;
	return TRUE;
}