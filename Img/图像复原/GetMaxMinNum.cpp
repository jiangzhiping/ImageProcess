/************************************
void CImgProcess::GetMaxMinNum(unsigned char *pArray,int nFilterLen,
							unsigned char &ucMax,unsigned char &ucMin,unsigned char &ucMed)
功能：			计算当前图像窗口的最大值、最小值和中值
参数：			unsigned char* pArray：输入的图像窗口数组指针
				int nFilterLen：窗口中像素个数
				unsigned char &ucMax：输出的最大值
				unsigned char &ucMin：输出的最小值
				unsigned char &ucMed：输出的中值
返回值：		无
*******************************/

void CImgProcess::GetMaxMinNum(unsigned char *pArray,int nFilterLen,
							unsigned char &ucMax,unsigned char &ucMin,unsigned char &ucMed)
{
	int i,j;
	unsigned char iTemp,bTemp;
	for(j=0;j<nFilterLen-1;j++)
	{
		for(i=0;i<nFilterLen-j-1;i++)
		{
			if(pArray[i]>pArray[i+1])
			{
				iTemp=pArray[i];
				pArray[i]=pArray[i+1];
				pArray[i+1]=iTemp;
			}
		}
	}
	//计算中值
	if((nFilterLen&1)>0)
	{
		//数组有奇数个元素，返回中间一个元素
		bTemp=pArray[(nFilterLen+1)/2];
	}
	else
	{
		//数组有偶数个元素，返回中间两个元素平均值
		bTemp=(pArray[nFilterLen/2]+pArray[nFilterLen/2+1])/2;
	}
	ucMax=pArray[nFilterLen-1];
	ucMin=pArray[0];
	ucMed=bTemp;
}