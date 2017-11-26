/*************************************
inline LONG GetFreqWidth(bool isExtending=true)
功能：		返回频域滤波或频域图像应有的宽度
参数：		bool isExtending：指定对宽度的整定拟合采取的方法
			true为扩展，对应用给定颜色补齐图像的右侧
			false为压缩，对应从右侧裁剪图像
			默认值为true
返回值：	LONG类型，整定后的宽度计算结果
***************************************/

inline LONG GetFreqWidth(bool isExtending=true)
{
	LONG w=1;
	while(w*2<=GetWidthPixel())
		w*=2;
	//如果需要扩展图像宽度，且图像宽度不恰好是2的整数幂，则
	if((w!=GetWidthPixel())&&(isExtending))
		w*=2;
	return w;
}