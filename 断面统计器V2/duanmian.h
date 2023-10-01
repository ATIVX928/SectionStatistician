#pragma once
#include "stdafx.h"
class duanmian
{
public:
	duanmian(int num,int l);
	//����
	int Calc();
private:
	//����ӵ��͵�
	int CalcLowestPoint();
	//�����߶���������
	int CalcConnectVector();
	//��������Ȩ��
	int CalcLinearWeights();
	//����ƽ���߳�
	int CalcAverageElevation();
	//����ӵ��е�
	int CalcMidPoint();
public:
	//��ö�����
	int GetNum();
	//��ö����������
	int GetL();
	//��������
	int operator<<(Eigen::Vector2d point);
	int operator+(std::string annotation);
	int operator--();
private:
	//����Ĭ�Ϲ���
	duanmian();

	//Դ����
	std::vector<Eigen::Vector2d> _data;

	//����������
	std::vector<std::string> _annotation;

	//������
	int _num;

	//�����������
	int _l;

	//��������
	std::vector<Eigen::Vector2d> _connect_vector;

	//ƽ���߳�
	double _average_elevation;

	//����Ȩ��
	std::vector<double>_linear_weights;

	//�ӵ��е�(���)
	int _mid_point;

	//�ӵ��͵�(���)
	int _lowest_point;
	
};

