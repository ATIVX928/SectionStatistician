#include "stdafx.h"
#include "duanmian.h"
using namespace Eigen;
using namespace std;
duanmian::duanmian(int num, int l)
{
	_num = num;
	_l = l;
}

int duanmian::Calc()
{
	CalcLowestPoint();
	CalcConnectVector();
	CalcLinearWeights();
	CalcAverageElevation();
	CalcMidPoint();
	return 1;
}

int duanmian::CalcLowestPoint()
{
	_lowest_point = 0;
	for (int i = 0; i < _data.size(); i++)
	{
		if (_data[i].y() < _data[_lowest_point].y())
		{
			_lowest_point = i;
		}
	}
	return 1;
}

int duanmian::CalcConnectVector()
{
	_connect_vector.clear();
	const size_t vectorsize = _data.size() - 1;
	for (int i = 0; i < vectorsize; i++)
	{
		_connect_vector.push_back(_data[i + 1] - _data[i]);
	}
	return 1;
}

int duanmian::CalcLinearWeights()
{
	_linear_weights.clear();
	int s = _data.size() - 1;
	double sum_linear_weights = 0;
	double w;
	w = _connect_vector[0].norm();
	_linear_weights.push_back(w);
	sum_linear_weights += w;
	for (int i = 1; i < s; i++)
	{
		w= _connect_vector[i - 1].norm()+ _connect_vector[i].norm();
		_linear_weights.push_back(w);
		sum_linear_weights += w;
	}
	w = _connect_vector[s - 1].norm();
	_linear_weights.push_back(w);
	sum_linear_weights += w;
	for (auto &i : _linear_weights)
	{
		i /= sum_linear_weights;
	}
	return 1;
}

int duanmian::CalcAverageElevation()
{
	_average_elevation = 0;
	for (int i = 0; i < _data.size(); i++)
	{
		_average_elevation += _data[i].y() * _linear_weights[i];
	}
	return 1;
}

int duanmian::CalcMidPoint()
{
	int enable = 2;
	int l, r;
	const double decision_elevation = (_average_elevation + _data[_lowest_point].y()) / 2;
	for (int i = 0; i < _data.size(); i++)
	{
		if (enable == 2)
		{
			if (_data[i].x() > 0 && _data[i].y() < decision_elevation)
			{
				enable--;
				l = i;
			}
			else
			{
				continue;
			}
		}
		if (enable == 1)
		{
			if (_data[i].y() > decision_elevation)
			{
				enable--;
				r = i-1;
			}
		}
	}
	int k;
	for (int i = l; i <= r; i++)
	{
		k = 0;
		double m = 9e99;
		Vector2d n;
		n = Vector2d(0, 0);
		for (int j = l; j <= r; j++)
		{
			n += _data[j] - _data[i];
		}
		if (n.norm() < m)
		{
			m = n.norm();
			k = i;
		}
	}
	_mid_point = k;
#ifdef _DEBUG
	cout << _data[_mid_point];
#endif
	return 1;
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
