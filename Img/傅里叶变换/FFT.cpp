/*************************************
void CImgProcess::FFT(complex<double>* TD,complex<double>* FD,int r)
功能：		一维快速傅里叶变换
参数：		complex<double>* TD:指向时域数组的指针
			complex<double>* FD:指向频域数组的指针
			int r:2的幂数，即迭代次数
返回值：	无
************************************/

void CImgProcess::FFT(complex<double>* TD,complex<double>* FD,int r)
{
	LONG count;//傅里叶变换点数
	int i,j,k;//循环变量
	int bfSize,p;//中间变量
	double angle;//角度

	complex<double> *W,*X1,*X2,*X;
	//计算傅里叶变换点数
	count=1<<r;
	//分配运算所需存储器
	W=new complex<double>[count/2];
	X1=new complex<double>[count];
	X2=new complex<double>[count];
	//计算加权系数
	for(i=0;i<count/2;i++)
	{
		angle=-i*PI*2/count;
		W[i]=complex<double>(cos(angle),sin(angle));
	}
	//将时域点写入X1
	memcpy(X1,TD,sizeof(complex<double>)*count);


	//采用蝶形算法进行傅里叶变化
	for(k=0;k<r;k++)
	{
		for(j=0;j<1<<k;j++)
		{
			bfSize=1<<(r-k);
			for(i=0;i<bfSize/2;i++)
			{
				p=j*bfSize;
				X2[i+p]=X1[i+p]+X1[i+p+bfSize/2];
				X2[i+p+bfSize/2]=(X1[i+p]-X1[i+p+bfSize/2])*W[i*(1<<k)];
			}
		}
		X=X1;
		X1=X2;
		X2=X;
	}

	//重新排序
	for(j=0;j<count;j++)
	{
		p=0;
		for(i=0;i<r;i++)
		{
			if(j&(1<<i))
				p+=1<<(r-i-1);
		}
		FD[j]=X1[p];
	}

	//释放内存
	delete W;
	delete X1;
	delete X2;
}