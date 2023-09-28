#pragma once
#include "stdafx.h"
#include "duanmian.h"
class hedao
{
public:
	//加载断面数据
	//s:文件名
	int Load_duanmian(std::string s= "测试数据.txt");

private:
	//断面源数据
	std::vector<std::shared_ptr<duanmian>> _data;
	//输入文件流
	std::fstream _filein;
};

