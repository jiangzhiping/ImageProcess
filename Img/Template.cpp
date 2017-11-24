/************************************
void CImgProcess::Template(CImgProcess *pTo,int nTempH,int nTempW,
							int nTempMY,int nTempMX,FLOAT *pfArray,FLOAT fCoef)
功能：			模板操作
注：			该函数用指定的模板（任意大小）来对图像进行操作，参数iTempH指定模板的高度
				，参数iTempW指定模板的宽度，参数iTempMX和iTempMY指定模板中心元素坐标，参数pfArray
				指定模板元素，fCoef指定系数。
参数：			CImgProcess *pTo：输出图像的CImgProcess指针
				int nTempH：模板的高度
				int nTempW：模板的宽度
				int nTempMY：模板中心元素Y坐标
				int nTempMX：模板中心元素X坐标
				FLOAT *pfArray：指向模板数组的指针
				FLOAT fCoef：模板系数
返回值：		无
************************************/

void CImgProcess::Template(CImgProcess *pTo,int nTempH,int nTempW,int nTempMY,int nTempMX,
	FLOAT *pfArray,FLOAT fCoef)
{
	pTo->InitPixel(0);//目标图像初始化
	int i,j;
	//扫描图像进行模板操作
	for(i=nTempMY;i<GetHeight()-(nTempH-nTempMY)+1;i++)
	{
		for(j=nTempMX;j<GetWidthPixel()-(nTempW-nTempMX)+1;j++)
		{
			//(j,i)为中心
			float fResult=0;
			for(int k=0;k<nTempH;k++)
			{
				for(int l=0;l<nTempW;l++)
				{
					//计算加权和
					fResult+=GetGray(j+1-nTempMX,i+k-nTempMY)*pfArray[k*nTempW+l];
				}
			}
			//乘以系数
			fResult+=fCoef;
			//取正
			fResult=(FLOAT)fabs(fResult);//锐化时有可能出现负数
			BYTE byte;
			if(fResult>255)
				byte=255;
			else
				byte=fResult+0.5;//四舍五入
			pTo->SetPixel(j,i,RGB(byte,byte,byte));
		}
	}
}