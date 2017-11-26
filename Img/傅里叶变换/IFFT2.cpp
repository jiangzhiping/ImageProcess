/************************************
void CImgProcess::IFFT2(CImgProcess *pTo,complex<double> *pInput,long lWidth,long lHeight,
						long lOutW,long lOutH)
功能：			二维快速反傅里叶变换
参数：			CImgProcess *pTo:指向输出图像的指针
				complex<double> *pInput:指向输入数组的指针
				long lWidth:输入数组中需要进行反傅里叶变换的高度
				long lHeight:输入数组中需要进行反傅里叶变换的高度
				long lOutW:指定输出图像的宽度，可以省略，默认与输入数组宽度相同
				long lOutH:指定输出图像的高度，可以省略，默认与输入数组高度相同
返回值:			无
*************************************/

void CImgProcess::IFFT2(CImgProcess *pTo,complex<double> *pInput,long lWidth,long lHeight,
						long lOutW,long lOutH)
{
	double dTemp;
	LONG i,j;
	//IFFT2的宽度和高度（2的整数次方）
	LONG w,h;
	int wp,hp;
	w=1,h=1;
	wp=0,hp=0;

	//输出图像的高宽
	if(lOutH==0)
		lOutH=lHeight;
	if(lOutW==0)
		lOutW=lWidth;

	//计算进行反傅里叶变换的宽度和高度（2的整数次方）
	while(w*2<=lWidth)
	{
		w*=2;
		wp++;
	}

	while(h*2<=lHeight)
	{
		h*=2;
		hp++;
	}

	//分配内存
	complex<double> *TD=new complex<double>[w*h];
	complex<double> *FD=new complex<double>[w*h];

	//设定输出图像大小
	pTo->ImResize(lOutH,lOutW);

	//垂直方向
	for(i=0;i<h;i++)
	{
		//水平方向
		for(j=0;j<w;j++)
		{
			//给频域赋值
			FD[j+w*i]=pInput[j+w*i];
		}
	}
	for(i=0;i<h;i++)
	{
		//对y方向进行快速反傅里叶变换
		IFFT(&FD[w*i],&TD[w*i],wp);
	}

	//保存变换结果
	//垂直方向
	for(i=0;i<h;i++)
	{
		//水平方向
		for(j=0;j<w;j++)
			FD[i+h*j]=TD[j+w*i];
	}

	for(i=0;i<w;i++)
	{
		//对x方向进行快速反傅里叶变换
		IFFT(&FD[i*h],&TD[i*h],hp);
	}

	//寻找反变换结果对数变换的最大值与最小值，为优化显示输出做准备
	//对最大值和最小值分别定义如下
	double dMax=0,dMin=1E+006;
	for(i=0;i<lOutH;i++)
	{
		for(j=0;j<lOutW;j++)
		{
			//计算模值
			dTemp=sqrt(TD[j*h+i].real()*TD[j*h+i].real()+TD[j*h+i].imag()*TD[j*h+i].imag());

			//寻找最大和最小值
			dMax=max(dMax,dTemp);
			dMin=min(dMin,dTemp)
		}
	}

	//行
	for (i = 0; i < lOutH; ++i)
	{
		//列
		for(j=0;j<lOutW;j++)
		{
			//计算模值
			dTemp=sqrt(TD[j*h+i].real()*TD[j*h+i].real()+TD[j*h+i].imag()*TD[j*h+i].imag());
			//改变动态范围并归一化到0~255
			dTemp=(dTemp-dMin)/(dMax-dMin)*255;
			//更新目标图像
			pTo->SetPixel(j,i,RGB(dTemp,dTemp,dTemp));
		}
	}

	//删除临时变量
	delete TD;
	delete FD;
}
