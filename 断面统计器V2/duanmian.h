#pragma once
#include "stdafx.h"
class duanmian
{
public:
	duanmian(int num,int l);
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
	
};

