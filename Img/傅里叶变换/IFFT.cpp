/*****************************************
void CImgProcess::IFFT(complex<double>* FD,complex<double>* TD,int r)
功能：			一维快速傅里叶反变换
参数：			complex<double>* FD:指向频域数组的指针
				complex<double>* TD:指向时域数组的指针
				int r:2的幂数，即迭代次数
返回值:			无
*****************************************/

void CImgProcess::IFFT(complex<double> *FD,complex<double> *TD,int r)
{
	LONG count;//傅里叶变换
	int i;//循环变量
	complex<double> *X;
	
	//计算傅里叶变换点数
	count=1<<r;

	//分配运算所需存储器
	X=new complex<double>[count];

	//将频域点写入X
	memcpy(X,FD,sizeof(complex<double>)*count);

	//求共轭
	for(i=0;i<count;i++)
		X[i]=complex<double>(X[i].real(),X[i].imag());

	//调用快速傅里叶变换
	FFT(X,TD,r);

	//求时域点的共轭
	for(i=0;i<count;i++)
		TD[i]=complex<double>(TD[i].real/count,-TD[i].imag()/count);

	//释放内存
	delete X; 
}