#pragma once
#include "stdafx.h"
#include "duanmian.h"
class hedao
{
public:
	//���ض�������
	//s:�ļ���
	int Load_duanmian(std::string s= "��������.txt");

private:
	//����Դ����
	std::vector<std::shared_ptr<duanmian>> _data;
	//�����ļ���
	std::fstream _filein;
};

