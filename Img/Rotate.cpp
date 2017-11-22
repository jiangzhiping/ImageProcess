/*****************************************************************
void CImgProcess::Rotate(CImgProcess *pTo,float ang)
功能：		以原点为中心的图像旋转
注：		围绕左上顶点顺时针旋转，图像范围不变
参数：		CImgProcess *pTo：处理后得到的图像的CImgProcess指针
			float ang：顺时针旋转角度，单位角，要求ang>0&&ang<360
返回值：	无
*******************************************************************/

void CImgProcess::Rotate(CImgProcess *pTo)
{
	int nHeight=pTo->GetHeight();
	int nWidth=pTo->GetWidthPixel();

	int i,j;//目标图像坐标
	int u,v;//源图像坐标
	for(i=0;i<nWidth;i++)
	{
		for(j=0;j<nHeight;j++)
		{
			u=int(i*cos(ang*PI/180)+j*sin(ang*PI/180)+0.5);
			v=int(j*cos(ang*PI/180)-i*sin(ang*PI/180)+0.5);
			if(u<nWidth&&v<nHeight&&u>=0&&v>=0)
				pTo->SetPixel(i,j,GetPixel(u,v));
			else
				pTo->SetPixel(i,j,RGB(0,0,0));
		}
	}
}