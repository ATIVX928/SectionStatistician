#pragma once
#include "stdafx.h"
class duanmian
{
public:
	duanmian(int num,int l);
public:
	//获得断面编号
	int GetNum();
	//获得断面距零点距离
	int GetL();
	//输入数据
	int operator<<(Eigen::Vector2d point);
	int operator+(std::string annotation);
	int operator--();
private:
	//禁用默认构造
	duanmian();

	//源数据
	std::vector<Eigen::Vector2d> _data;

	//点数据描述
	std::vector<std::string> _annotation;

	//断面编号
	int _num;

	//断面距零点距离
	int _l;
	
};

