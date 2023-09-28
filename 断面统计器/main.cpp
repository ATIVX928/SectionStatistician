#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<cmath>
using namespace std;
class duanmian
{
public:
	vector<double>x, h;
	vector<string>a;
	int n,l;
public:
	duanmian(int _n,int _l)
	{
		n = _n;
		l = _l;
	}
};
int main()
{
	fstream filein, fileout, fileout2;
	filein.open("��������.txt",ios::in);
	fileout.open("�������.csv", ios::out);
	fileout2.open("����.csv", ios::out);
	if (!filein.is_open()|| !fileout.is_open())
	{
		cout << "���ļ�����" << endl;
		return 0;
	}
	string s;
	vector<duanmian*>hedao;
	duanmian* cs=0;
	while (!filein.eof())
	{
		filein >> s;
		if (s.find("CS")==0)
		{
			int num = atoi(s.data()+2);
			int l= atoi(s.data() + s.find("(") + 1)*1000+ atoi(s.data() + s.find("+") + 1);
			cs = new duanmian(num, l);
			hedao.push_back(cs);
			continue;
		}
		if (!cs)
		{
			continue;
		}
		if (s[0] & 0x80 && s.length()>=2)
		{
			if (s[1] & 0x80)
			{
				cs->a.pop_back();
				cs->a.push_back(s);
				continue;
			}
		}
		cs->x.push_back(atof(s.data()));
		filein >> s;
		cs->h.push_back(atof(s.data()));
		cs->a.push_back("");
		//cout << s << endl;
	}
	for (auto i : hedao)
	{
		for (int j = 0; j < i->x.size(); j++)
		{

			fileout2 << i->l << "," << i->x[j] << "," << i->h[j] << endl;
		}
	}




	fileout << format("{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}\n", "׮��", "�󰶵�����״�߳�", "�󰶵̶���״�߳�", "�󰶵̶���·����", "�󰶵̶���·���", "�󰶵̶����", "�󰶺ӿڸ߳�", "���±�", "�ӿڼ��", "�ӵ׸߳�", "�ӵ׼��", "�Ұ��±�", "�Ұ��ӿڸ߳�", "�Ұ��̶����", "�Ұ��̶���·���", "�Ұ��̶���·����", "�Ұ��̶���״�߳�", "�Ұ�������״�߳�", "��ע");
	for (auto i : hedao)
	{
		/*for (int j = 0; j < i->x.size(); j++)
		{
			//string s;
			//fileout << format("{},{},{}\n", i->x[j], i->h[j], i->a[j]);
			//cout << i->x[j] << " " << i->h[j] << " " << i->a[j] << endl;
		}*/



		//�ӿ�
		int _hekou = 0, i_l = 0, i_r = 0;
		double x_l, x_r, h_l, h_r;
		for (int j = 0; j < i->x.size(); j++)
		{
			if (i->a[j] == "�ӿ�")
			{
				if (!_hekou)
				{
					if (abs(i->x[j]) > 0.01)continue;
					x_l = i->x[j];
					h_l = i->h[j];
					i_l = j;
					_hekou++;
				}
				else
				{
					x_r = i->x[j];
					h_r = i->h[j];
					i_r = j;
					_hekou++;
				}
			}
		}
		if (_hekou == 1)
		{
			_hekou = 0;
			for (int j = 0; j < i->x.size(); j++)
			{
				if (i->a[j] == "�ӹ�")
				{
					if (i->x[j] < 0.01)continue;
					if (!_hekou)
					{
						_hekou++;
					}
					else
					{
						x_r = i->x[j];
						h_r = i->h[j];
						i_r = j;
						_hekou++;
					}
				}
			}
		}
		if (_hekou != 2)
		{
			//fileout << format("{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}\n", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "���ش��󣺺ӿ�������Ϊ2");
			continue;
		}
		fileout << i->l << ",";

		//������״�̣߳��̶���״�̣߳��̶���·���ͣ��̶���·��ȣ��̶����
		//ˮ��·����·���ڲ���·

		int r_l1 = -1, r_l2 = -1, r_r1 = -1, r_r2 = -1;//��·ָ��
		int d_l1 = -1, d_l2 = -1, d_r1 = -1, d_r2 = -1;//�̶�ָ��
		int d_l0 = -1, d_r0 = -1;//�̶��ߵ�
		int gl = -1, gr = -1;//������״�̻߳���
		string mes;
		//��
		for (int j = 0; j < i_l; j++)
		{
			if (gl == -1 && abs((i->h[j + 1] - i->h[j]) / (i->x[j + 1] - i->x[j])) < 0.1 /* && abs((i->h[j + 2] - i->h[j]) / (i->x[j + 2] - i->x[j])) < 0.1*/)
			{
				gl = j;
			}
			if (i->a[j].empty())continue;
			if (i->a[j] == "ˮ��·" || i->a[j] == "��·" || i->a[j] == "�ڲ���·")
			{
				if (r_l1 == -1)
				{
					r_l1 = j;
				}
				else
				{
					if (r_l2 == -1)
					{
						r_l2 = j;
					}
					else
					{
						mes += "�����󰶳���������·��";
					}
				}
			}
		}
		if (gl == -1)
		{
			mes += "�����󰶵�����״��ȷ�����޷�����������������";
		}
		else
		{
			if (i->h[gl] > h_l + 10)
			{
				mes += "��Ϣ���󰶵�����ںӿڣ����������رգ�";
			}
			else
			{
				d_l0 = gl;
				for (int j = gl; j < i_l; j++)
				{
					if (i->h[j] > i->h[d_l0])
					{
						d_l0 = j;
					}
				}
				if (d_l0 == gl || i->h[d_l0]- i->h[gl]<1) d_l0 = -1;
				if (d_l0 > 0)
				{
					d_l1 = d_l0;
					d_l2 = d_l0;
					for (int j = d_l0; j < i_l; j++)
					{
						d_l2 = j;
						if (abs((i->h[j + 1] - i->h[j]) / (i->x[j + 1] - i->x[j])) > 0.12) break;
					}
					for (int j = d_l0; j > gl; j--)
					{
						d_l1 = j;
						if (abs((i->h[j - 1] - i->h[j]) / (i->x[j - 1] - i->x[j])) > 0.12) break;
					}
					if (abs(i->x[d_l1] - i->x[d_l2]) <= 3)
					{
						int d_l1e = d_l1;
						int d_l2e = d_l2;
						while (1)
						{
							if (i->h[d_l1e - 1] + 1 < i->h[d_l1] || d_l1e == gl)break;
							if (d_l1e > 1)
							{
								d_l1e--;
							}
							else
							{
								break;
							}
							if (abs((i->h[d_l1e - 1] - i->h[d_l1e]) / (i->x[d_l1e - 1] - i->x[d_l1e])) > 0.2 && abs((i->h[d_l1e + 1] - i->h[d_l1e]) / (i->x[d_l1e + 1] - i->x[d_l1e])) < 0.1)
							{
								d_l1 = d_l1e;
							}
						}
						while (1)
						{
							if (i->h[d_l2e + 1] + 1 < i->h[d_l2] || d_l2e == i_l)break;
							d_l2e++;
							if (abs((i->h[d_l2e + 1] - i->h[d_l2e]) / (i->x[d_l2e + 1] - i->x[d_l2e])) > 0.2 && abs((i->h[d_l2e - 1] - i->h[d_l2e]) / (i->x[d_l2e - 1] - i->x[d_l2e])) < 0.1)
							{
								d_l2 = d_l2e;
							}
						}
					}
					while (abs(i->x[d_l1] - i->x[d_l2]) > 10)
					{
						double dy1 = abs((i->h[d_l1 + 1] - i->h[d_l1]) / (i->x[d_l1 + 1] - i->x[d_l1]) + (i->h[d_l1 + 2] - i->h[d_l1]) / (i->x[d_l1 + 2] - i->x[d_l1]));
						double dy2 = abs((i->h[d_l2 - 1] - i->h[d_l2]) / (i->x[d_l2 - 1] - i->x[d_l2]) + (i->h[d_l2 - 2] - i->h[d_l2]) / (i->x[d_l2 - 2] - i->x[d_l2]));
						if (dy1 < 0.04 && dy2 < 0.04)break;
						if (dy1 > dy2)
						{
							d_l1++;
						}
						else
						{
							d_l2--;
						}
					}
					if (abs(i->x[d_l1] - i->x[d_l2]) <= 3)
					{
						int d_l1e = d_l1;
						int d_l2e = d_l2;
						while (1)
						{
							if (i->h[d_l1e - 1] + 1 < i->h[d_l1] || d_l1e == gl)break;
							if (d_l1e > 1)
							{
								d_l1e--;
							}
							else
							{
								break;
							}
							if (abs((i->h[d_l1e - 1] - i->h[d_l1e]) / (i->x[d_l1e - 1] - i->x[d_l1e])) > 0.2 && abs((i->h[d_l1e + 1] - i->h[d_l1e]) / (i->x[d_l1e + 1] - i->x[d_l1e])) < 0.1)
							{
								d_l1 = d_l1e;
							}
						}
						while (1)
						{
							if (i->h[d_l2e + 1] + 1 < i->h[d_l2] || d_l2e == i_l)break;
							d_l2e++;
							if (abs((i->h[d_l2e + 1] - i->h[d_l2e]) / (i->x[d_l2e + 1] - i->x[d_l2e])) > 0.2 && abs((i->h[d_l2e - 1] - i->h[d_l2e]) / (i->x[d_l2e - 1] - i->x[d_l2e])) < 0.1)
							{
								d_l2 = d_l2e;
							}
						}
					}
				}
			}
		}
		if (gl >= 0)
		{
			fileout << i->h[gl] << ",";
		}
		else
		{
			fileout << "" << ",";
		}
		if (d_l0 >= 0 && i->h[d_l0] > i->h[gl])
		{
			fileout << i->h[d_l0] << ",";
		}
		else
		{
			fileout << i->h[gl] << ",";
		}
		if (r_l1 >= 0)
		{
			fileout << i->a[r_l1] << "," << abs(i->x[r_l1] - i->x[r_l2]) << ",";
		}
		else
		{
			fileout << "0" << "," << "" << ",";
		}
		if (d_l1 >= 0)
		{
			fileout << abs(i->x[d_l1] - i->x[d_l2]) << ",";
		}
		else
		{
			fileout << "0" << ",";
		}

		//�ӵ�
		int h0 = i_l;
		for (int j = i_l; j < i_r; j++)
		{
			if (i->h[j] < i->h[h0])h0 = j;
		}
		int h1 = h0-1;
		int h2 = h0+1;
		for (int j = h1; j > i_l; j--)
		{
			if (abs(i->x[j - 1] - i->x[j]) < 0.5)
			{
				h1 = j;
				continue;
			}
			if (abs((i->h[j - 1] - i->h[j]) / (i->x[j - 1] - i->x[j])) > 0.15 && abs((i->h[j - 2] - i->h[j]) / (i->x[j - 2] - i->x[j])) > 0.15 && (i->h[j]-i->h[h0])>0.5) break;
			h1 = j;
		}
		for (int j = h2; j < i_r; j++)
		{
			if (abs(i->x[j + 1] - i->x[j]) < 0.5)
			{
				h2 = j;
				continue;
			}
			if (abs((i->h[j + 1] - i->h[j]) / (i->x[j + 1] - i->x[j])) > 0.15 && abs((i->h[j + 2] - i->h[j]) / (i->x[j + 2] - i->x[j])) > 0.15 && (i->h[j] - i->h[h0]) > 0.5) break;
			h2 = j;
		}
		fileout << h_l << "," << abs((i->h[i_l] - i->h[h1]) / (i->x[i_l] - i->x[h1])) << "," << x_r - x_l << "," << i->h[h0] << "," << i->x[h2] - i->x[h1] << "," << abs((i->h[i_r] - i->h[h2]) / (i->x[i_r] - i->x[h2])) << "," << h_r << ",";


		//�Ұ�
		for (int j = i->x.size()-1; j > i_r; j--)
		{
			if (gr == -1 && abs((i->h[j - 1] - i->h[j]) / (i->x[j - 1] - i->x[j])) < 0.1 /*&& abs((i->h[j - 2] - i->h[j]) / (i->x[j - 2] - i->x[j])) < 0.1*/)
			{
				gr = j;
			}
			if (i->a[j].empty())continue;
			if (i->a[j] == "ˮ��·" || i->a[j] == "��·" || i->a[j] == "�ڲ���·")
			{
				if (r_r1 == -1)
				{
					r_r1 = j;
				}
				else
				{
					if (r_r2 == -1)
					{
						r_r2 = j;
					}
					else
					{
						mes += "�����Ұ�����������·��";
					}
				}
			}
		}
		if (gr == -1)
		{
			mes += "�����Ұ�������״��ȷ�����޷������Ұ�����������";
		}
		else
		{
			if (i->h[gr] > h_r + 10)
			{
				mes += "��Ϣ���Ұ�������ںӿڣ����������رգ�";
			}
			else
			{
				d_r0 = gr;
				for (int j = gr; j > i_r; j--)
				{
					if (i->h[j] > i->h[d_r0])
					{
						d_r0 = j;
					}
				}
				if (d_r0 == gr || i->h[d_r0] - i->h[gr] < 1) d_r0 = -1;
				if (d_r0 > 0)
				{
					d_r1 = d_r0;
					d_r2 = d_r0;
					for (int j = d_r0; j > i_r; j--)
					{
						d_r2 = j;
						if (abs((i->h[j - 1] - i->h[j]) / (i->x[j - 1] - i->x[j])) > 0.12) break;
					}
					for (int j = d_r0; j < gr; j++)
					{
						d_r1 = j;
						if (abs((i->h[j + 1] - i->h[j]) / (i->x[j + 1] - i->x[j])) > 0.12) break;
					}
					if (abs(i->x[d_r1] - i->x[d_r2]) <= 3)
					{
						int d_r1e = d_r1;
						int d_r2e = d_r2;
						while (1)
						{
							if (i->h[d_r2e - 1] + 1 < i->h[d_r2] || d_r2e == gr)break;
							d_r2e--;
							if (abs((i->h[d_r2e - 1] - i->h[d_r2e]) / (i->x[d_r2e - 1] - i->x[d_r2e])) > 0.2 && abs((i->h[d_r2e + 1] - i->h[d_r2e]) / (i->x[d_r2e + 1] - i->x[d_r2e])) < 0.1)
							{
								d_r2 = d_r2e;
							}
						}
						while (1)
						{
							if (i->h[d_r1e + 1] + 1 < i->h[d_r1] || d_r1e == i_r)break;
							if (d_r1e < i->x.size() - 2)
							{
								d_r1e++;
							}
							else
							{
								break;
							}
							if (abs((i->h[d_r1e + 1] - i->h[d_r1e]) / (i->x[d_r1e + 1] - i->x[d_r1e])) > 0.2 && abs((i->h[d_r1e - 1] - i->h[d_r1e]) / (i->x[d_r1e - 1] - i->x[d_r1e])) < 0.1)
							{
								d_r1 = d_r1e;
							}
						}
					}
					while (abs(i->x[d_r1] - i->x[d_r2]) > 10)
					{
						double dy1 = abs((i->h[d_r1 - 1] - i->h[d_r1]) / (i->x[d_r1 - 1] - i->x[d_r1]) + (i->h[d_r1 - 2] - i->h[d_r1]) / (i->x[d_r1 - 2] - i->x[d_r1]));
						double dy2 = abs((i->h[d_r2 + 1] - i->h[d_r2]) / (i->x[d_r2 + 1] - i->x[d_r2]) + (i->h[d_r2 + 2] - i->h[d_r2]) / (i->x[d_r2 + 2] - i->x[d_r2]));
						if (dy1 < 0.04 && dy2 < 0.04)break;
						if (dy1 > dy2)
						{
							d_r1--;
						}
						else
						{
							d_r2++;
						}
					}
					if (abs(i->x[d_r1] - i->x[d_r2]) <= 3)
					{
						int d_r1e = d_r1;
						int d_r2e = d_r2;
						while (1)
						{
							if (i->h[d_r2e - 1] + 1 < i->h[d_r2] || d_r2e == gr)break;
							d_r2e--;
							if (abs((i->h[d_r2e - 1] - i->h[d_r2e]) / (i->x[d_r2e - 1] - i->x[d_r2e])) > 0.2 && abs((i->h[d_r2e + 1] - i->h[d_r2e]) / (i->x[d_r2e + 1] - i->x[d_r2e])) < 0.1)
							{
								d_r2 = d_r2e;
							}
						}
						while (1)
						{
							if (i->h[d_r1e + 1] + 1 < i->h[d_r1] || d_r1e == i_r)break;
							if (d_r1e < i->x.size() - 2)
							{
								d_r1e++;
							}
							else
							{
								break;
							}
							if (abs((i->h[d_r1e + 1] - i->h[d_r1e]) / (i->x[d_r1e + 1] - i->x[d_r1e])) > 0.2 && abs((i->h[d_r1e - 1] - i->h[d_r1e]) / (i->x[d_r1e - 1] - i->x[d_r1e])) < 0.1)
							{
								d_r1 = d_r1e;
							}
						}
					}
				}
			}
		}
		if (d_r1 >= 0)
		{
			fileout << abs(i->x[d_r1] - i->x[d_r2]) << ",";
		}
		else
		{
			fileout << "0" << ",";
		}
		if (r_r1 >= 0)
		{
			fileout << abs(i->x[r_r1] - i->x[r_r2]) << "," << i->a[r_r1] << ",";
		}
		else
		{
			fileout << "0" << "," << "" << ",";
		}
		if (d_r0 >= 0 && i->h[d_r0] > i->h[gr])
		{
			fileout << i->h[d_r0] << ",";
		}
		else
		{
			fileout << i->h[gr] << ",";
		}
		if (gr >= 0)
		{
			fileout << i->h[gr] << ",";
		}
		else
		{
			fileout << "" << ",";
		}

		fileout << mes << endl;
	}
	filein.close();
	fileout.close();
}