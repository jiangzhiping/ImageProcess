/*************************************
void CImgProcess::FFT2(CImgProcess *pTo,BOOL bExpand,complex<double> *pOutput,BYTE bFillColor)
功能：			二维快速傅里叶变换
参数：			CImgProcess *pTo:指向输出频谱图像的指针，设置为NULL，则不输出图像
				BOOL bExpand:指定使用何种方法将图像高宽整定到的整数幂
							若设置为TRUE，则使用指定颜色扩大图像
							若设置为FALSE，则从右侧和底部裁剪图像
							默认取值FALSE，即裁剪图像
				complex<double> *pOutput:指向原始输出数组的指针，即F(U,V)。默认只显示，不输出，即为NULL
				BYTE bFillColor:默认值为255.当bExpand被设置为TRUE时，这个参数指定使用何种颜色扩大图像；
								当bExpand被设置为FALSE时，这个参数被忽略。
返回值：		无
***********************************/

void CImgProcess::FFT2(CImgProcess *pTo,BOOL bExpand,complex<double> *pOutput,BYTE bFillColor)
{
	double dTemp;
	LONG i,j;
	//FFT2的宽度和高度（2的整数次幂）
	LONG w,h;
	int wp,hp;
	w=1;
	h=1;
	wp=0;
	hp=0;

	//计算进行傅里叶变换的宽度和高度（2的整数次幂）
	while(w*2<=GetWidthPixel())
	{
		w*=2;
		wp++;
	}

	while(h*2<=GetHeight())
	{
		h*=2;
		hp++;
	}

	//检查bExpand参数
	if((bExpand)&&(w!=GetWidthPixel())&&(h!=GetHeight()))
	{
		w*=2;wp++;
		h*=2;hp++;
	}

	//分配内存
	complex<double> *TD=new complex<double>[w*h];
	complex<double> *FD=new complex<double>[w*h];

	//垂直方向
	for(i=0;i<h,i++)
	{
		//水平方向
		for(j=0;j<w;j++)
		{
			//给时域赋值
			if(bExpand)
			{
				if((j<GetWidthPixel())&&(i<GetHeight()))
				{
					TD[j+w*i]=complex<double>(GetGray(j,i),0);
				}
				else
				{
					//超出原图像范围的使用给定颜色填充
					TD[j+w*i]=complex<double>(bFillColor,0);
				}
			}
			else
			{
				TD[j+w*i]=complex<double>(GetGray(j,i),0);
			}
		}
	}

	for(i=0;i<h,i++)
	{
		//对y方向机械能快速傅里叶变换
		FFT(&TD[w,i],&FD[w,i],wp);
	}

	//保存变换结果
	for(i=0;i<h,i++)
	{
		for(j=0;j<w;j++)
			TD[i+h*j]=FD[j+w*i];
	}

	for(i=0;i<w;i++)
	{
		//对x方向进行快速傅里叶变换
		FFT(&TD[i*h],&FD[i*h],hp);
	}

	//更新矩阵
	if(pOutput)
	{
		//垂直方向
		for(i=0;i<h;i++)
		{
			//水平方向
			for(j=0;j<w;j++)
				pOutput[i*w+j]=FD[j*h+i];
		}
	}

	//更新输出图像
	if(pTo)
	{
		//重设输出图像大小
		pTo->ImResize(h,w);
		//寻找幅度谱对数变换的最大值和最小值，为优化幅度谱显示输出做准备
		//幅度谱对数变换后的最大值和最小值分别定义如下
		double dMax=0,dMin=1E+006;
		for(i=0;i<h;i++)
		{
			for(j=0;j<w;j++)
			{
				//计算幅度谱
				dTemp=sqrt(FD[j*h+i].real()*FD[j*h+i].real()+FD[j*h+i].imag()*FD[j*h+i].imag())/100;
				//对数变换
				dTemp=log(1+dTemp);
				//寻找最大和最小值
				dMax=max(dMax,dTemp);
				dMin=min(dMin,dTemp);
			}
		}

		for(i=0;i<h;i++)
		{
			for(j=0;j<w;j++)
			{
				//计算幅度谱
				dTemp=sqrt(FD[j*h+i].real()*FD[j*h+i].real()+FD[j*h+i].imag()*FD[j*h+i].imag())/100;
				//对数变换
				dTemp=log(1+dTemp);
				//改变动态范围并归一化到0~255
				dTemp=(dTemp-dMin)/(dMax-dMin)*255;
				//更新目标图像
				//此处不直接取j和i，是为了将变换后的原点移到中心
				pTo->SetPixel((j<w/2?j+w/2:j-w/2))
			}
		}
	}

	//删除临时变量
	delete TD;
	delete FD;
}