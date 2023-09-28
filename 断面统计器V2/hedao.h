#pragma once
#include "stdafx.h"
#include "duanmian.h"
class hedao
{
public:
	//加载数据
	//s:文件名
	int Load(std::string s= "测试数据.txt");
	//计算
	int Calc();

private:
	//断面源数据
	std::vector<std::shared_ptr<duanmian>> _data;
	//输入文件流
	std::fstream _filein;
private:
	//载入断面
	int operator<<(std::shared_ptr<duanmian>& x);
};

