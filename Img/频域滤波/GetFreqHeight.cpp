/*********************************
inline LONG GetFreqHeight(bool isExtending=true)
功能：		返回频域滤镜或频域图像应用的高度
参数：		bool isExtending：指定对宽度的整定拟合采取的方法
				true为扩展，对应用给定颜色补齐图像的底部
				false为压缩，对应从底部裁剪图像
				默认值为true
返回值：	LONG类型，整定后的高度计算结果
*********************************/

inline LONG GetFreqHeight(bool isExtending=true)
{
	LONG h=1;
	while(h*2<=GetHeight())
		h*=2;
	//如果需要扩展图像高度，且图像高度不恰好是2整数幂，则：
	if((h!=GetHeight())&&(isExtending))
		h*=2;
	return h;
}