/********************************
void CImgProcess::EnhanceFilter(CImgProcess *pTo,double dProportion,int nTempH,int nTempW,
								int nTempMY,int nTempMX,FLOAT *pfArray,FLOAT fCoef)
功能：				高提升滤波
参数：				CImgProcess *pTo：输出图像的CImgProcess指针
					doubel dProportion：高提升滤波中图像的混合比例
					int nTempH：模板的高度
					int nTempW：模板的宽度
					int nTempMY：模板的中心元素Y坐标（<iTempH-1）
					int nTempMX：模板的中心元素X坐标（<iTempW-1）
					FLOAT *fpArray：指向模板数组的指针
					FLOAT fCoef：模板系数
返回值：无
********************************/

void CImgProcess::EnhanceFilter(CImgProcess *pTo,double dProportion,int nTempH,int nTempW,
								int nTempMY,int nTempMX,FLOAT *pfArray,FLOAT fCoef)
{
	int i,j;
	int nHeight=GetHeight();
	int nWidth=GetWidthPixel();
	*pTo=*this;//目标图像初始化
	//GrayMat暂存按比例叠加图像（不能在CImg类对象中直接进行像素相加，因为相加的结果可能超出范围[0,255]）
	vector<vector<int>> GrayMat;
	vector<int> vecRow(nWidth,0);//GrayMat中的一行（初始化为0）
	for(i=0;i<nHeight;i++)
		GrayMat.push_back(vecRow);
	//锐化图像，输出带符号响应，并与原图像按比例叠加
	for(i=nTempMY;i<GetHeight()-(nTempH-nTempMY)+1;i++)
	{
		for(j=nTempMX;j<GetWidthPixel()-(nTempW-nTempMx)+1;j++)
		{
			//(j,i)为中心点
			float fResult=0;
			for(int k=0;k<nTempH;k++)
			{
				for(int l=0;l<nTempW;l++)
				{
					//计算加权和
					fResult+=GetGray(j+1-nTempMX,i+k-nTempMY)*pfArray[k*nTempW+1];
				}
			}
			//乘以系数
			fResult*=fCoef;
			
			//限制响应值范围
			if(fResult>255)
				fResult=255;
			if(fResult<-255)
				fResult=-255;
			GrayMat[i][j]=dProportion*GetGray(j,i)+fResult+0.5;//求和，结果四舍五入
		}
	}

	int nMax=0;//最大灰度值
	int nMin=65535;//最小灰度值
	//统计最大、最小值
	for(i=nTempMY;i<GetHeight()-(nTempH-nTempMY)+1;i++)
	{
		for(j=nTempMX;j<GetWidthPixel()-(nTempW-nTempMx)+1;j++)
		{
			if(GrayMat[i][j]>nMax)
				nMax=GrayMat[i][j];
			if(GrayMat[i][j]<nMin)
				nMin=GrayMat[i][j];
		}
	}

	//将GrayMat的取值范围重新归一化到[0,255]
	int nSpan=nMax-nMin;
	for(i=nTempMY;i<GetHeight()-(nTempH-nTempMY)+1;i++)
	{
		for(j=nTempMX;j<GetWidthPixel-(nTempW-nTempMx)+1;j++)
		{
			BYTE bt;
			if(nSpan>0)
				bt=(GrayMat[i][j]-nMin)*255/nSpan;
			else if(GrayMat[i][j]<=255)
				bt=GrayMat[i][j];
			else
				bt=255;
			pTo->SetPixel(j,i,RGB(bt,bt,bt));
		}
	}
}