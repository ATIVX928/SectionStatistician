#include "stdafx.h"
#include "duanmian.h"
duanmian::duanmian(int num, int l)
{
	_num = num;
	_l = l;
}

int duanmian::GetNum()
{
	return _num;
}

int duanmian::GetL()
{
	return _l;
}

int duanmian::operator<<(Eigen::Vector2d point)
{
	_data.push_back(point);
	return 1;
}

int duanmian::operator+(std::string annotation)
{
	_annotation.push_back(annotation);
	return 1;
}

int duanmian::operator--()
{
	_annotation.pop_back();
	return 1;
}

duanmian::duanmian()
{
}
