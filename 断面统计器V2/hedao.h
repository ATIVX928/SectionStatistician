#pragma once
#include "stdafx.h"
#include "duanmian.h"
class hedao
{
public:
	//��������
	//s:�ļ���
	int Load(std::string s= "��������.txt");
	//����
	int Calc();

private:
	//����Դ����
	std::vector<std::shared_ptr<duanmian>> _data;
	//�����ļ���
	std::fstream _filein;
private:
	//�������
	int operator<<(std::shared_ptr<duanmian>& x);
};

