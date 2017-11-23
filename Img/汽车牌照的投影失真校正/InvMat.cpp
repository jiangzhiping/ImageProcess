/**********************************************
算法采用Gauss-Jordan方法
BOOL CImgProcess::InvMat(double **ppDbMat,int nLen)
功能：			计算ppDbMat的逆矩阵
注：			ppDbMat必须为方阵
参数：			double **ppDbMat：输入矩阵
				int nLen：矩阵ppDbMat的尺寸
返回值：		BOOL
				=true：执行成功
				=false：计算过程中出现错误
*************************************************/

BOOL CImgProcess::InvMat(double **ppDbMat,int nLen)
{
	double* pDbSrc=new double[nLen*nLen];
	int *is,*js,*i,j,k;
	//保存要求逆的输入矩阵
	int nCnt=0;
	for(i=0;i<nLen;i++)
	{
		for(j=0;j<nLen;j++)
			pDbSrc[nCnt++]=ppDbMat[i][j];
	}
	double d,p;
	is=new int[nLen];
	js=new int[nLen];
	for(k=0;k<nLen;k++)
	{
		d=0.0;
		for(i=k;i<nLen;i++)
			for(j=k;j<nLen;j++)
			{
				p=fabs(pDbSrc[i*nLen+j]);//找到绝对值最大的系数
				if(p>d)
				{
					d=p;
					//记录绝对值最大的系数的行、列索引值
					is[k]=i;
					js[k]=j;
				}
			}
			if(d+1.0==1.0)
			{
				//系数全是0，系数矩阵为0阵，此时为奇异矩阵
				delete is;
				delete js;
				return false;
			}
			if(is[k]!=k)//当前行不包含最大元素
				for(j=0;j<nLen;j++)
				{
					//交换两行元素
					p=pDbSrc[k*nLen+j];
					pDbSrc[k*nLen+j]=pDbSrc[(is[k]*nLen)+j];
					pDbSrc[(is[k])+nLen+j]=p;
				}

			if(js[k]!=k)//当前列不包含最大元素
				for(i=0;i<nLen;i++)
				{
					//交换两列元素
					p=pDbSrc[i*nLen+k];
					pDbSrc[i*nLen+k]=pDbSrc[i*nLen+(js[k])];
					pDbSrc[i*nLen+(js[k])]=p;
				}

			pDbSrc[k*nLen+k]=1.0/pDbSrc[k*nLen+k];//求主元的倒数
			//a[k,j]a[k,k]->a[k,j]
			for(j=0;j<nLen;j++)
				if(j!=k)
					pDbSrc[k*nLen+j]*=pDbSrc[k*nLen+k];
			//a[i,j]-a[i,k]a[k,j]->a[i,j]
			for(i=0;i<nLen;i++)
				if(i!=k)
					for(j=0;j<nLen;j++)
						if(j!=k)
							pDbSrc[i*nLen+j]-=pDbSrc[i*nLen+k]*pDbSrc[k*nLen+j];
			//-a[i,k]a[k,k]->a[i,k]
			for(i=0;i<nLen;i++)
				if(i!=k)
					pDbSrc[i*nLen+k]*=-pDbSrc[k*nLen+k];
	}

	for(k=nLen-1;k>0;k--)
	{
		//恢复列
		if(js[k]!=k)
			for(j=0;j<nLen;j++)
			{
				p=pDbSrc[k*nLen+j];
				pDbSrc[k*nLen+j]=pDbSrc[(js[k])*nLen+j];
				pDbSrc[(js[k])*nLen+j]=p;
			}
		//恢复行
		if(is[k]!=k)
			for(i=0;i<nLen;i++)
			{
				p=pDbSrc[i*nLen+k];
				pDbSrc[i*nLen+k]=pDbSrc[i*nLen+(is[k])];
				pDbSrc[i*nLen+(is[k])]=p;
			}
	}

	//将结果复制回系数矩阵ppDbMat
	nCnt=0;
	for(i=0;i<m_nBasePt;i++)
	{
		for(j=0;j<m_nBasePt;j++)
			ppDbMat[i][j]=pDbSrc[nCnt++];
	}

	//释放空间
	delete is;
	delete js;
	delete[] pDbSrc;
	return TRUE;
}