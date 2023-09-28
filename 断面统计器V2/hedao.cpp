#include "stdafx.h"
#include "hedao.h"

using namespace std;
using namespace Eigen;
int hedao::Load(std::string s)
{
    _filein.open(s, ios::in);

	if (!_filein.is_open())
	{
		cout << "打开文件错误" << endl;
		return -1;
	}

	auto  cs = make_shared<duanmian>(0,0);
	while (!_filein.eof())
	{
		_filein >> s;
		if (s.find("CS") == 0)
		{
			int num = atoi(s.data() + 2);
			int l = atoi(s.data() + s.find("(") + 1) * 1000 + atoi(s.data() + s.find("+") + 1);
			cs = make_shared<duanmian>(num, l);
			*this<<cs;
			continue;
		}
		if (cs->GetNum() == 0)
		{
			continue;
		}
		if (s[0] & 0x80 && s.length() >= 2)
		{
			if (s[1] & 0x80)
			{
				cs->operator--();
				*cs+s;
				continue;
			}
		}
		double x = atof(s.data());
		_filein >> s;
		double y = atof(s.data());
		*cs << Vector2d(x,y);
		*cs+"";
	}
    return 1;
}

int hedao::operator<<(std::shared_ptr<duanmian>& x)
{
	_data.push_back(x);
	return 1;
}
