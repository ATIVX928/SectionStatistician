#pragma once
#include "stdafx.h"
class duanmian
{
public:
	duanmian(int num,int l);
	//计算
	int Calc();
private:
	//计算河道低点
	int CalcLowestPoint();
	//计算线段连接向量
	int CalcConnectVector();
	//计算线性权重
	int CalcLinearWeights();
	//计算平均高程
	int CalcAverageElevation();
	//计算河道中点
	int CalcMidPoint();
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

	//连接向量
	std::vector<Eigen::Vector2d> _connect_vector;

	//平均高程
	double _average_elevation;

	//线性权重
	std::vector<double>_linear_weights;

	//河道中点(编号)
	int _mid_point;

	//河道低点(编号)
	int _lowest_point;
	
};

