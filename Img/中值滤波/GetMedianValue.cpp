/*************************************
int CImgProcess::GetMedianValue(int* pAryGray,int nFilterLen)
功能：		采用冒泡法对数组进行排序，并返回数组元素的中值。
参数：		int* pAryGray：要排序提取中值的数组
			int* nFilterLen：数组长度
返回值：	int：中值
*************************************/

int CImgProcess::GetMedianValue(int* pAryGray,int nFilterLen)
{
	int i,j;
	int nMedianValue;
	int nTemp;//中间变量
	//排序
	for(j=0;j<nFilterLen-1;j++)
	{
		for(i=0;i<nFilterLen-j-1;i++)
		{
			if(pAryGray[i]>pAryGray[i+1])
			{
				//交换位置
				nTemp=pAryGray[i];
				pAryGray[i]=pAryGray[i+1];
				pAryGray[i+1]=nTemp;
			}
		}
	}
	//计算中值
	if((nFilterLen&1)>0)
	{
		//数组有奇数个元素，返回中间一个元素
		nMedianValue=pAryGray[(nFilterLen+1)/2];
	}
	else
	{
		//数组有偶数个元素，返回中间两个元素平均值
		nMedianValue=(pAryGray[nFilterLen/2]+pAryGray[nFilterLen/2+1])/2;
	}
	return nMedianValue;
}