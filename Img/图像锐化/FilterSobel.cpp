/*****************************
void CImgProcess::FilterSobel(CImgProcess *pTo)
功能；			Sobel梯度
参数：			ImgProcess *pTo：目标输出图像的CImgProcess指针
返回值：		无
*****************************/

void CImgProcess::FilterSobel(CImgProcess *pTo)
{
	CImgProcess img1,img2;
	img1=*pTo;
	img2=*pTo;

	Template(&img1,3,3,1,1,Template_HSobel,1);
	Template(&img2,3,3,1,1,Template_VSobel,1);

	*pTo=img1+img2;
}