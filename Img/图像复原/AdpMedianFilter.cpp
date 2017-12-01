/****************************
void CImgProcess::AdpMedianFilter(unsigned char* lpImage,long lWidth,long lHeight,int nSmax)
功能：				对当前图像做自适应中值滤波
参数：				unsigned char* lpImage：输入的图像数组指针
					long lWidth：图像的宽度
					long lHeight：图像的高度
					int nSmax：最大窗口大小，必须为奇数
返回值：无
*****************************/

void CImgProcess::AdpMedianFilter(unsigned char* lpImage,long lWidth,long lHeight,int nSmax)
{
	//nSmax必须为奇数
	if(2*(nSmax/2)==nSmax)
	{
		AfxMessage("第4个参数必须为奇数！");
		return;
	}
	unsigned char* lpSrc=0;*lpDst=0;
	//long lSaveWidth=(((8*lWidth)+31)/32*4);
	long lSaveWidth=lWidth;
	unsigned char* lpNewImage=nwe unsigned char[lSaveWidth*lHeight];
	memcpy(lpNewImage,lpImage,lSaveWidth*lHeight);

	LPBYTE pArray=new BYTE[nSmax*nSmax];
	int nFileterMX,nFileterMY;
	unsigned char iMin,iMax,iMed,iCurPixel;
	int A1,A2,B1,B2;
	BOOL *pbProcessed=new BOOL[lWidth*lHeight];
	memset(pbProcessed,FALSE,lWidth*lHeight*sizeof(BOOL));
	int nWindowOrder;//窗口大小

	for(nWindowOrder=3;nWindowOrder<=nSmax;nWindowOrder+=2)
	{
		nFileterMX=nWindowOrder/2;
		nFileterMY=nWindowOrder/2;
		for(long i=nFileterMY;i<lHeight-nWindowOrder+nFileterMY+1;i++)
		{
			for(long j=nFileterMX;j<lWidth-nWindowOrder+nFileterMX+1;j++)
			{
				lpDst=lpNewImage+lSaveWidth*(lHeight-1-i)+j;
				for(int k=0;k<nWindowOrder;k++)
				{
					for(m=0;m<nWindowOrder;m++)
					{
						lpSrc=lpImage+lSaveWidth*(lHeight-1+nFileterMY-k)+j-nFileterMX+m;
						pArray[k*nWindowOrder+m]=*lpSrc;
					}
				}
				GetMaxMinNum(pArray,nWindowOrder*nWindowOrder,iMax,iMin,iMed);
				lpSrc=lpImage+lSaveWidth*(lHeight-1-i)+j;
				iCurPixel=*lpSrc;
				A1=iMed-iMin;
				A2=iMed-iMax;
				if(A1>=0&&A2<=0&&!pbProcessed[lWidth*(lHeight-1-i)+j])
				{
					pbProcessed[lWidth*(lHeight-1-i)+j]=TRUE;
					B1=iCurPixel-iMin;
					B2=iCurPixel-iMax;
					if(B1>0&&B2<0)
						*lpDst=iCurPixel;
					else
						*lpDst=iMed;
				}
			}
		}
	}
	memcpy(lpImage,lpNewImage,lSaveWidth*lHeight);
	delete []pArray;
	delete []lpNewImage;
	delete []pbProcessed;
}
