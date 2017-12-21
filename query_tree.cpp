#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "query_tree.h"

using namespace std;

schema sch;

//SAL(title char(20) primary key, sal float not null)
//EMP(eno char(20) primary key, ename char(20) not null, title char(20))
//JOB(jno char(20) primary key, jname char(20) not null, budget float not null, loc char(20) not null)
//ASG(eno char(20), jno char(20), resp char(20) not null, dur int not null)
void init_schema()
{
	sch.table_num = 4;

	sch.table[1].table_name = "sal";	sch.table[2].table_name = "emp";
	sch.table[3].table_name = "job";	sch.table[4].table_name = "asg";
	
	sch.table[1].site_num = 1;	sch.table[1].type = -1;
	sch.table[1].site[1].condition[0] = "null";
	sch.table[1].col_num = 2;
	sch.table[1].col_name[1] = "title"; sch.table[1].col_name[2] = "sal";

	sch.table[2].site_num = 4;	sch.table[2].type = 0;
	sch.table[2].site[1].condition[0] = "eno<'E1000'&title<'N'";		sch.table[2].site[2].condition[0] = "eno<'E1000'&title>='N'";
	sch.table[2].site[3].condition[0] = "eno>='E1000'&title<'N'";		sch.table[2].site[4].condition[0] = "eno>='E1000'&title>='N'";
	//��Ƭ����
	sch.table[2].site[1].hcon_list_len = 2;	sch.table[2].site[2].hcon_list_len = 2;
	sch.table[2].site[3].hcon_list_len = 2; sch.table[2].site[4].hcon_list_len = 2;
	sch.table[2].site[1].hcon_list[1].attr = "eno";	  sch.table[2].site[1].hcon_list[1].op = "<";  sch.table[2].site[1].hcon_list[1].section = "'E1000'";
	sch.table[2].site[1].hcon_list[2].attr = "title"; sch.table[2].site[1].hcon_list[2].op = "<";  sch.table[2].site[1].hcon_list[2].section = "'N'";
	sch.table[2].site[2].hcon_list[1].attr = "eno";   sch.table[2].site[2].hcon_list[1].op = "<";  sch.table[2].site[2].hcon_list[1].section = "'E1000'";
	sch.table[2].site[2].hcon_list[2].attr = "title"; sch.table[2].site[2].hcon_list[2].op = ">="; sch.table[2].site[2].hcon_list[2].section = "'N'";
	sch.table[2].site[3].hcon_list[1].attr = "eno";   sch.table[2].site[3].hcon_list[1].op = ">="; sch.table[2].site[3].hcon_list[1].section = "'E1000'";
	sch.table[2].site[3].hcon_list[2].attr = "title"; sch.table[2].site[3].hcon_list[2].op = "<";  sch.table[2].site[3].hcon_list[2].section = "'N'";
	sch.table[2].site[4].hcon_list[1].attr = "eno";   sch.table[2].site[4].hcon_list[1].op = ">="; sch.table[2].site[4].hcon_list[1].section = "'E1000'";
	sch.table[2].site[4].hcon_list[2].attr = "title"; sch.table[2].site[4].hcon_list[2].op = ">="; sch.table[2].site[4].hcon_list[2].section = "'N'";
	//�������Ϣ
	sch.table[2].col_num = 3;
	sch.table[2].col_name[1] = "eno";	sch.table[2].col_name[2] = "ename";	sch.table[2].col_name[3] = "title";

	sch.table[3].site_num = 4;	sch.table[3].type = 2;
	sch.table[3].site[1].condition[0] = "jno<'J0500'";	sch.table[3].site[1].condition[1] = "jno,jname,budget";
	sch.table[3].site[2].condition[0] = "jno<'J0500'";	sch.table[3].site[2].condition[1] = "jno,loc";
	sch.table[3].site[3].condition[0] = "jno>='J0500'";	sch.table[3].site[3].condition[1] = "jno,jname,budget";
	sch.table[3].site[4].condition[0] = "jno>='J0500'";	sch.table[3].site[4].condition[1] = "jno,loc";
	//��Ƭ����
	sch.table[3].site[1].hcon_list_len = 1;	sch.table[3].site[2].hcon_list_len = 1;
	sch.table[3].site[3].hcon_list_len = 1; sch.table[3].site[4].hcon_list_len = 1;
	sch.table[3].site[1].hcon_list[1].attr = "jno";   sch.table[3].site[1].hcon_list[1].op = "<";   sch.table[3].site[1].hcon_list[1].section = "'J0500'";
	sch.table[3].site[2].hcon_list[1].attr = "jno";   sch.table[3].site[2].hcon_list[1].op = "<";   sch.table[3].site[2].hcon_list[1].section = "'J0500'";
	sch.table[3].site[3].hcon_list[1].attr = "jno";   sch.table[3].site[3].hcon_list[1].op = ">=";  sch.table[3].site[3].hcon_list[1].section = "'J0500'";
	sch.table[3].site[4].hcon_list[1].attr = "jno";   sch.table[3].site[4].hcon_list[1].op = ">=";  sch.table[3].site[4].hcon_list[1].section = "'J0500'";
	//�������Ϣ
	sch.table[3].col_num = 4;
	sch.table[3].col_name[1] = "jno";	sch.table[3].col_name[2] = "jname";	sch.table[3].col_name[3] = "budget";	sch.table[3].col_name[4] = "loc";

	sch.table[4].site_num = 4;	sch.table[4].type = 0;
	sch.table[4].site[1].condition[0] = "eno<'E1000'&jno<'J0500'";		sch.table[4].site[2].condition[0] = "eno<'E1000'&jno>='J0500'";
	sch.table[4].site[3].condition[0] = "eno>='E1000'&jno<'J0500'";		sch.table[4].site[4].condition[0] = "eno>='E1000'&jno>='J0500'";
	//��Ƭ����
	sch.table[4].site[1].hcon_list_len = 2;	sch.table[4].site[2].hcon_list_len = 2;
	sch.table[4].site[3].hcon_list_len = 2; sch.table[4].site[4].hcon_list_len = 2;
	sch.table[4].site[1].hcon_list[1].attr = "eno";	  sch.table[4].site[1].hcon_list[1].op = "<";  sch.table[4].site[1].hcon_list[1].section = "'E1000'";
	sch.table[4].site[1].hcon_list[2].attr = "jno";   sch.table[4].site[1].hcon_list[2].op = "<";  sch.table[4].site[1].hcon_list[2].section = "'J0500'";
	sch.table[4].site[2].hcon_list[1].attr = "eno";   sch.table[4].site[2].hcon_list[1].op = "<";  sch.table[4].site[2].hcon_list[1].section = "'E1000'";
	sch.table[4].site[2].hcon_list[2].attr = "jno";   sch.table[4].site[2].hcon_list[2].op = ">="; sch.table[4].site[2].hcon_list[2].section = "'J0500'";
	sch.table[4].site[3].hcon_list[1].attr = "eno";   sch.table[4].site[3].hcon_list[1].op = ">="; sch.table[4].site[3].hcon_list[1].section = "'E1000'";
	sch.table[4].site[3].hcon_list[2].attr = "jno";   sch.table[4].site[3].hcon_list[2].op = "<";  sch.table[4].site[3].hcon_list[2].section = "'J0500'";
	sch.table[4].site[4].hcon_list[1].attr = "eno";   sch.table[4].site[4].hcon_list[1].op = ">="; sch.table[4].site[4].hcon_list[1].section = "'E1000'";
	sch.table[4].site[4].hcon_list[2].attr = "jno";   sch.table[4].site[4].hcon_list[2].op = ">="; sch.table[4].site[4].hcon_list[2].section = "'J0500'";
	//�������Ϣ
	sch.table[4].col_num = 4;
	sch.table[4].col_name[1] = "eno";	sch.table[4].col_name[2] = "jno";	sch.table[4].col_name[3] = "resp";	sch.table[4].col_name[4] = "dur";

}


//�����ֵ
int maxint(int a, int b)
{
	if (a > b) return a;
	else return b;
}
double max(double a, double b)
{
	if (a > b) return a;
	else return b;
}
//�ж�һ���ַ����Ƿ�Ϊ����
bool isVar(string s)
{	//���ַ���
	if (s.substr(0, 1) == "\"" || s.substr(0, 1) == "'") return false;
	//������
	if (s.substr(0, 1) >= "0" && s.substr(0, 1) <= "9") return false;
	return true;
}

int loc(string s, query_tree &o_tree)
{
	int pos_dot = s.find(".");//�ҵ��ַ�"."��λ�ã�֮ǰ���Ǳ������
	if (pos_dot > 0)
	{
		string name = s.substr(0, pos_dot);
		//cout << name << endl;
		return o_tree.table_pos[name];
		
	}
	else
	{
		return o_tree.table_pos[s];
	}
	return -1;

}

//�����������
void insert_table_list(string table_list, query_tree &o_tree)
{
	int st = 0;
	string table_name = "";
	while (true)
	{
		int pos = table_list.find(",", st);

		if (pos < 0)
		{
			pos = table_list.length();
			table_name = table_list.substr(st, pos-st);
			pos = -1;
		}
		else
		{
			table_name = table_list.substr(st, pos-st);
			st = pos + 1;
		}
		//cout << table_name << endl;
		//����table_name
		o_tree.node[++o_tree.num].type = 0;
		o_tree.node[o_tree.num].str = table_name;
		o_tree.node[o_tree.num].fa = -1;
		o_tree.node[o_tree.num].child[0] = 0;
		o_tree.table_pos[table_name] = o_tree.num;
		o_tree.table_num = o_tree.num;

		if (pos < 0) break;
	}

}
//�ҵ�tree[i]������
int get_fa(query_tree &tree, int i)
{	while (tree.node[i].fa!=-1)
	{
		i = tree.node[i].fa;
	}
	return i;
}
//�Ѳ�ѯ�������뵽����
void insert_condition(string condition_list, query_tree &o_tree)
{
	int st = 0;
	string condition = "";
	while (true)
	{
		int pos1 = condition_list.find("(", st);
		int pos2 = condition_list.find(")", st);

		if (pos1 < 0) 
		{
			break;
		}
		else
		{
			condition = condition_list.substr(pos1+1, pos2 - pos1 - 1);
			st = pos2 + 1;
		}
		//cout << condition << endl;
		//�õ�һ��condition����������
		//�ж��ǲ���һ�����ӣ����߶��Ǳ����Ļ���������
		//ȷ���Ƚϲ�����λ��
		int pos_op = maxint(condition.find("=", 0), maxint(condition.find(">", 0), condition.find("<", 0)));
		pos_op = maxint(pos_op, maxint(condition.find(">=", 0), maxint(condition.find("<=", 0), condition.find("<>", 0))));
		//�ж����������ǲ��Ǳ���
		string str1 = condition.substr(0, pos_op);//����ַ���
		string str2 = condition.substr(pos_op+1, condition.length() - pos_op);//�Ҳ��ַ���
		if (isVar(str1) && isVar(str2))
		{	//���Ǳ�����Ϊ����
			int pos_l = loc(str1, o_tree), pos_r = loc(str2, o_tree);//ȷ�����ұ��������������е�λ��
			int fa1 = get_fa(o_tree, pos_l), fa2 = get_fa(o_tree, pos_r);
			//���join�ڵ�
			o_tree.node[++o_tree.num].type = 2;
			o_tree.node[o_tree.num].str = condition;
			o_tree.node[o_tree.num].fa = -1;
			o_tree.node[o_tree.num].child[0] = 2;
			o_tree.node[o_tree.num].child[1] = fa1;	o_tree.node[o_tree.num].child[2] = fa2;
			//�����ӽڵ�ĸ�ָ��
			o_tree.node[fa1].fa = o_tree.num;			o_tree.node[fa2].fa = o_tree.num;

			//cout << get_fa(o_tree, pos_l) << " " << get_fa(o_tree, pos_r) << endl;
		}
		else
		{	//����Ϊ������������ʱ���б��Ѿ���һ���������ȣ������������嵽�������ȵ�ͷ��
			int fa = get_fa(o_tree, 1);//���ȡ��һ���ڵ�����Ⱦ��ǹ�������
			//cout << "fa is:" << fa << endl;
			//������������
			o_tree.node[++o_tree.num].type = 3;
			o_tree.node[o_tree.num].str = condition;
			o_tree.node[o_tree.num].fa = -1;
			o_tree.node[o_tree.num].child[0] = 1; o_tree.node[o_tree.num].child[1] = fa;
			o_tree.node[fa].fa = o_tree.num;
		}
	}

}
//��schema�б��λ����Ϣ���ŵ�����
void insert_schema(query_tree &o_tree, schema &sch)
{
	for (int i = 1; i <= sch.table_num; i++)
	{
		o_tree.schema_pos[sch.table[i].table_name] = i;
	}
}
//��ȡ���з�Ƭ��Ϣ����ԭʼ�Ĳ�ѯ��
query_tree get_original_tree(string s)
{
	query_tree o_tree;
	//����Ҫ��ѯ���ȷ�������
	string sql = s;
	sql.erase(0, 7);//ɾ��select
	int pos1 = sql.find("from");
	int pos2 = sql.find(" ", pos1+5);
	//cout << pos1 << sql << endl;
	string table_list = sql.substr(pos1+5, pos2-pos1-5);
	insert_table_list(table_list, o_tree);
	//cout << table_list << endl;

	//����ѯ������������
	pos2 = sql.find("where")+6;
	string condition = sql.substr(pos2, sql.length() - pos2);
	//cout << condition << endl;
	insert_condition(condition, o_tree);

	//��ͶӰ������������
	string select = sql.substr(0, pos1-1);
	//cout << pos1<<select << endl;
	int fa = get_fa(o_tree, 1);//���ȡ��һ���ڵ�����Ⱦ��ǹ�������
	o_tree.node[++o_tree.num].type = 4;
	o_tree.node[o_tree.num].str = select;
	o_tree.node[o_tree.num].fa = -1;
	o_tree.node[o_tree.num].child[0] = 1; o_tree.node[o_tree.num].child[1] = fa;
	o_tree.node[fa].fa = o_tree.num;
	
	o_tree.root = o_tree.num;
	//��schema��Ϣ���뵽����
	insert_schema(o_tree, sch);
	//�����б���Ϊ��Ƭ
	int i = 1;
	while (o_tree.node[i].type == 0)
	{	int s_pos = o_tree.schema_pos[o_tree.node[i].str];
		if (sch.table[s_pos].site_num > 1)
		{	//ˮƽ��Ƭֱ�Ӳ��վ���union
			if (sch.table[s_pos].type == 0)
			{	o_tree.node[i].type = 1;	o_tree.node[i].str = "";
				o_tree.node[i].child[0] = sch.table[s_pos].site_num;
				for (int j = 1; j <= sch.table[s_pos].site_num; j++)
				{	o_tree.node[++o_tree.num].type = 0;
					o_tree.node[o_tree.num].fa = i;
					o_tree.node[o_tree.num].child[0] = 0;
					o_tree.node[i].child[j] = o_tree.num;
					o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
				}
			}
			//��ֱ��Ƭ���վ�������
			if (sch.table[s_pos].type == 1)
			{	for (int j = 1; j <= sch.table[s_pos].site_num; j++)
				{	//�Ȱѷ�Ƭ����
					o_tree.node[++o_tree.num].type = 0;
					o_tree.node[o_tree.num].child[0] = 0;
					o_tree.node[o_tree.num].fa = -1;
					o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
				}
				//�Գ������������Ƭ��������
				int en = o_tree.num;
				for (int st = o_tree.num - sch.table[s_pos].site_num + 1;st < en-1;st++)
				{	//ȡ�����ڵ������
					int fa1 = get_fa(o_tree, st);  int fa2 = get_fa(o_tree, st+1);
					//�½�һ��join�ڵ�
					o_tree.node[++o_tree.num].type = 2;
					o_tree.node[o_tree.num].child[0] = 2;
					o_tree.node[o_tree.num].child[1] = fa1;
					o_tree.node[o_tree.num].child[2] = fa2;
				}
				//����������ڵ�join�����ڵĽڵ���
				int fa1 = get_fa(o_tree, en - 1); int fa2 = get_fa(o_tree, en);
				o_tree.node[i].type = 2; 
				o_tree.node[i].child[0] = 2; 
				o_tree.node[o_tree.num].child[1] = fa1;
				o_tree.node[o_tree.num].child[2] = fa2;
			}
			//��Ϸ�Ƭ���Ƚ�ˮƽ������ͬ�������ӣ�Ȼ������
			if (sch.table[s_pos].type == 2)
			{	string attr[maxsite];//�������ڷ�Ƭ���Լ����б�Ҳ���Ǵ�ֱ��Ƭ����
				string cond[maxsite];//����ˮƽ��Ƭ�б�
				int pos[maxsite];//�����Ƭ�����е�λ��
				int r = sch.table[s_pos].site_num;
				for (int j = 1; j <= sch.table[s_pos].site_num; j++)
				{	//�Ȱѷ�Ƭ����
					o_tree.node[++o_tree.num].type = 0;
					o_tree.node[o_tree.num].child[0] = 0;
					o_tree.node[o_tree.num].fa = -1;
					o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
					attr[j] = sch.table[s_pos].site[j].condition[1];
					cond[j] = sch.table[s_pos].site[j].condition[0];
					pos[j] = o_tree.num;
				}
				for (int k = 1;k <= r;k++) cout << pos[k] << " " << attr[k] << " " << cond[k] << endl;
				cout << endl;
				int en = o_tree.num;
				
				for (int j = 1;j <= r;j++)
				{	//�������û��������ͬ�ķ�Ƭ����ǰ����������ͬ�ģ���union��Ҳ����ȡ���һ����Ƭ����union
					bool can_union = false, last = true;
					for (int k = 1;k < j;k++)
						if (attr[j].compare(attr[k]) == 0) can_union = true;
					for (int k = j + 1; k <= r;k++)
						if (attr[j].compare(attr[k]) == 0) last = false;
					if (can_union && last)
					{   cout << j << endl;
						//�ȴ���һ��union�ڵ�
						o_tree.node[++o_tree.num].type = 1;
						o_tree.node[o_tree.num].child[0] = 0;
						o_tree.node[o_tree.num].fa = -1;
						//����union��union����
						for (int k = 1; k <= j;k++)
						{
							if (attr[j].compare(attr[k]) == 0)
							{
								o_tree.node[o_tree.num].child[++o_tree.node[o_tree.num].child[0]] = pos[k];
								o_tree.node[pos[k]].fa = o_tree.num;
							}
						}
						//union֮��ɾ��,ֻ����һ����Ƭ����
						for (int k = 1; k < j;k++)
						{
							if (attr[j].compare(attr[k]) == 0)
							{
								for (int l = k; l < r;l++)
								{
									attr[l] = attr[l + 1];
									pos[l] = pos[l + 1];
									cond[l] = cond[l + 1];
								}
								j--; r--;
							}
						}
						for (int k = 1;k <= r;k++) cout << pos[k] << " " << attr[k] << " " << cond[k] << endl;
						cout << endl;
					}
				}
			
				
				//�ҿ���join�ķ�Ƭ��������һ����������ͬ���Ѿ�union�������з�Ƭjoin
				for (int j=1;j<r-2;j++)
				{	//ȡ�����ڵ������
					int fa1 = get_fa(o_tree, pos[j]);  int fa2 = get_fa(o_tree, pos[j+1]);
					//�½�һ��join�ڵ�
					o_tree.node[++o_tree.num].type = 2;
					o_tree.node[o_tree.num].child[0] = 2;
					o_tree.node[o_tree.num].child[1] = fa1; o_tree.node[fa1].fa = o_tree.num;
					o_tree.node[o_tree.num].child[2] = fa2; o_tree.node[fa2].fa = o_tree.num;
				}
						
				//����������ڵ�join�����ڵĽڵ���
				int fa1 = get_fa(o_tree, pos[r-1]); int fa2 = get_fa(o_tree, pos[r]);
						
				o_tree.node[i].type = 2;
				o_tree.node[i].child[0] = 2;
				o_tree.node[i].child[1] = fa1; o_tree.node[fa1].fa = i;
				o_tree.node[i].child[2] = fa2; o_tree.node[fa2].fa = i;
				o_tree.node[i].str = "";
			}
			
		}
		i++;
	}
	cout << "fuck\n";
	return o_tree;
	
}
//��������ļ�
void print_tree(query_tree tree)
{
	ofstream out("tree.txt");
	int q[maxtreenode], dep[maxtreenode], l = 1, r = 1;
	int root = tree.root;
	q[l] = root; dep[l] = 1;
	while (l<=r)
	{
		out << q[l] << " " << tree.node[q[l]].type << " " << tree.node[q[l]].fa << " " << tree.node[q[l]].child[0];
		if (tree.node[q[l]].child[0]!=0) out << " ";
		for (int j = 1;j <= tree.node[q[l]].child[0];j++)
		{	out << tree.node[q[l]].child[j];
			q[++r] = tree.node[q[l]].child[j];
			dep[r] = dep[l] + 1;
			if (j != tree.node[q[l]].child[0]) out << " ";
		}
		out << " " << dep[l];
		out << "/" << tree.node[q[l]].str;
		out << endl;
		l++;
	}
	out.close();
}

//�жϲ�ѯ�������ַ���condition�����Ƭ�Ƿ�ƥ��
bool match_condition_frag(string condition, treenode &x, query_tree &tree)
{	//��ʱֻдAND���������һ��������ֻ��һ������
	//ȷ���Ƚϲ�����λ��
	int pos_op = maxint(condition.find("=", 0), maxint(condition.find(">", 0), condition.find("<", 0)));
	pos_op = maxint(pos_op, maxint(condition.find(">=", 0), maxint(condition.find("<=", 0), condition.find("<>", 0))));
	//�ҵ�.��λ�ã��ѱ���ȥ��
	int pos_dot = condition.find(".", 0);
	//��ȡ����ѯ����������
	string attr = "";
	if (pos_dot < 0) attr = condition.substr(0, pos_op);		
	else attr = condition.substr(pos_dot + 1, pos_op - pos_dot - 1);
	//��ȡtree.node[x]�ı����ͷ�Ƭ���
	int pos_colon = x.str.find(":");
	string name = ""; int site = 0;
	if (pos_colon < 0)
	{	name = x.str;
		site = 1;
	}
	else
	{	int len = x.str.length();
		name = x.str.substr(0, pos_colon);
		site = atoi(x.str.substr(pos_colon + 1, len - pos_colon - 1).c_str());
	}
	//ȷ�������Ƭ��û���������
	int sch_pos = tree.schema_pos[name];
	//cout << sch_pos << " " <<name <<endl;
	//ˮƽ�Ͳ���Ƭ���Ҷ�Ӧ�ı��Ƿ��и�����
	if (sch.table[sch_pos].type == -1 || sch.table[sch_pos].type == 0)
	{
		bool flag = false;
		for (int i = 1; i <= sch.table[sch_pos].col_num; i++)
		{
			if (sch.table[sch_pos].col_name[i].compare(attr) == 0)
			{
				flag = true;
			}
		}
		if (!flag) return false;
	}
	else
	{	//����ֱ��Ƭ��Ϣ���Ƿ��и�����
		cout << "find " << attr << endl;
		int pos = sch.table[sch_pos].site[site].condition[1].find(attr);
		if (pos >= 0)
		{
			cout << sch.table[sch_pos].site[site].condition[1] << " "<<pos << endl;
			return true;
		}
		else return false;
	}
	return true;
}

bool intersect(string op, string section, condition_info condition)
{	//=
	if (op.compare("=") == 0)
	{	if (condition.op.compare("=") == 0)
		{	if (section.compare(condition.section) == 0) return true;
		}
		else if (condition.op.compare(">") == 0)
		{	if (section.compare(condition.section) > 0) return true;
		}
		else if (condition.op.compare("<") == 0)
		{	if (section.compare(condition.section) < 0) return true;
		}
		else if (condition.op.compare(">=") == 0)
		{	if (section.compare(condition.section) >= 0) return true;
		}
		else if (condition.op.compare("<=") == 0)
		{	if (section.compare(condition.section) <= 0) return true;
		}
		else if (condition.op.compare("<>") == 0)
		{	if (section.compare(condition.section) != 0) return true;
		}
	}
	//>
	else if (op.compare(">") == 0)
	{	if (condition.op.compare("=") == 0)
		{	if (section.compare(condition.section) < 0) return true;
		}
		else if (condition.op.compare(">") == 0)
		{	return true;
		}
		else if (condition.op.compare("<") == 0)
		{	if (section.compare(condition.section) < 0) return true;
		}
		else if (condition.op.compare(">=") == 0)
		{	return true;
		}
		else if (condition.op.compare("<=") == 0)
		{	if (section.compare(condition.section) < 0) return true;
		}
		else if (condition.op.compare("<>") == 0)
		{	return true;
		}
	}
	//>=
	if (op.compare(">=") == 0)
	{	if (condition.op.compare("=") == 0)
		{	if (section.compare(condition.section) <= 0) return true;
		}
		else if (condition.op.compare(">") == 0)
		{	return true;
		}
		else if (condition.op.compare("<") == 0)
		{	if (section.compare(condition.section) < 0) return true;
		}
		else if (condition.op.compare(">=") == 0)
		{	return true;
		}
		else if (condition.op.compare("<=") == 0)
		{	if (section.compare(condition.section) <= 0) return true;
		}
		else if (condition.op.compare("<>") == 0)
		{	return true;
		}
	}
	//<
	if (op.compare("<") == 0)
	{	if (condition.op.compare("=") == 0)
		{	if (section.compare(condition.section) > 0) return true;
		}
		else if (condition.op.compare(">") == 0)
		{	if (section.compare(condition.section) > 0) return true;
		}
		else if (condition.op.compare("<") == 0)
		{	return true;
		}
		else if (condition.op.compare(">=") == 0)
		{	if (section.compare(condition.section) > 0) return true;
		}
		else if (condition.op.compare("<=") == 0)
		{	return true;
		}
		else if (condition.op.compare("<>") == 0)
		{	return true;
		}

	}
	//<=
	if (op.compare("<=") == 0)
	{	if (condition.op.compare("=") == 0)
		{	if (section.compare(condition.section) >= 0) return true;
		}
		else if (condition.op.compare(">") == 0)
		{	if (section.compare(condition.section) > 0) return true;
		}
		else if (condition.op.compare("<") == 0)
		{	return true;
		}
		else if (condition.op.compare(">=") == 0)
		{	if (section.compare(condition.section) >= 0) return true;
		}
		else if (condition.op.compare("<=") == 0)
		{	return true;
		}
		else if (condition.op.compare("<>") == 0)
		{	return true;
		}
	}
	//<>
	if (op.compare("<>") == 0)
	{	if (condition.op.compare("=") == 0)
		{	if (section.compare(condition.section) != 0) return true;
		}
		return true;
	}
	return false;
}

bool condition_intersect(string condition, treenode &x, query_tree &tree)
{	//ȷ���Ƚϲ�����λ�� �� �Ƚϲ�����
	int pos_op = maxint(condition.find("=", 0), maxint(condition.find(">", 0), condition.find("<", 0)));
	pos_op = maxint(pos_op, maxint(condition.find(">=", 0), maxint(condition.find("<=", 0), condition.find("<>", 0))));
	//�����ڵ����ֵ�ÿ���һ��
	string op; int temp; string section;
	temp = condition.find("=", 0);  if (temp >= 0) {
		op = "="; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find(">", 0);  if (temp >= 0) {
		op = ">"; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find("<", 0);  if (temp >= 0) {
		op = "<"; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find(">=", 0); if (temp >= 0) {
		op = ">="; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	temp = condition.find("<=", 0); if (temp >= 0) {
		op = "<="; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	temp = condition.find("<>", 0); if (temp >= 0) {
		op = "<>"; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	cout << op << " " << section << endl;
	//�ҵ�.��λ�ã��ѱ���ȥ��
	int pos_dot = condition.find(".", 0);
	//��ȡ����ѯ����������
	string attr = "";
	if (pos_dot < 0) attr = condition.substr(0, pos_op);
	else attr = condition.substr(pos_dot + 1, pos_op - pos_dot - 1);
	//��ȡtree.node[x]�ı����ͷ�Ƭ���
	int pos_colon = x.str.find(":");
	string name = ""; int site = 0;
	if (pos_colon < 0)
	{
		name = x.str;
		site = 1;
	}
	else
	{
		int len = x.str.length();
		name = x.str.substr(0, pos_colon);
		site = atoi(x.str.substr(pos_colon + 1, len - pos_colon - 1).c_str());
	}
	//����ȷ�������Ƭ������û���������
	int sch_pos = tree.schema_pos[name];
	//ˮƽ��Ƭ
	if (sch.table[sch_pos].type == 0)
	{	//��Ƭ�������������
		if (sch.table[sch_pos].site[site].condition[0].find(attr) >= 0)
		{	//����������ԣ��ж������Ƿ��ཻ
			cout << "�ж��Ƿ��㽶" << endl;
			bool flag = true;
			for (int i = 1;i <= sch.table[sch_pos].site[site].hcon_list_len;i++)
			{	//��Ϊֻ��AND�����Բ�ѯ����ֻ��һ����Ȼ���ѯ����������Ҫ��ÿ��������ͬ�ķ�Ƭ������Ҫ�н��
				if (attr.compare(sch.table[sch_pos].site[site].hcon_list[i].attr) == 0)
				{	//������ͬ�����Ƿ��ཻ
					cout << "compare " << op << " "<<section<<" "<< sch.table[sch_pos].site[site].hcon_list[i].op << " "<< sch.table[sch_pos].site[site].hcon_list[i].section<< endl;
					if (!intersect(op, section, sch.table[sch_pos].site[site].hcon_list[i])) flag = false;
				}
			}
			return flag;
		}
		//������ܴ��ڽ��
		else return true;
	}
	//��Ϸ�Ƭ
	else if (sch.table[sch_pos].type == 2)
	{	//���ȴ�ֱ��Ƭ���������������
		cout << "FUCK!!!!!!" << endl;
		int pos = sch.table[sch_pos].site[site].condition[1].find(attr);
		if (pos >= 0)
		//Ȼ���ˮƽ��Ƭһ���ж��Ƿ��н���
		{	//��Ƭ�������������
			if (sch.table[sch_pos].site[site].condition[0].find(attr) >= 0)
			{	cout << "�ж��Ƿ��㽶" << endl;
				bool flag = true;
				for (int i = 1;i <= sch.table[sch_pos].site[site].hcon_list_len;i++)
				{	//��Ϊֻ��AND�����Բ�ѯ����ֻ��һ����Ȼ���ѯ����������Ҫ��ÿ��������ͬ�ķ�Ƭ������Ҫ�н��
					if (attr.compare(sch.table[sch_pos].site[site].hcon_list[i].attr) == 0)
					{	//������ͬ�����Ƿ��ཻ
						cout << "compare " << op << " " << section << " " << sch.table[sch_pos].site[site].hcon_list[i].op << " " << sch.table[sch_pos].site[site].hcon_list[i].section << endl;
						if (!intersect(op, section, sch.table[sch_pos].site[site].hcon_list[i])) flag = false;
					}
				}
				return flag;
			}
			//������ܴ��ڽ��
			else return true;
		}
		else return false;
	}
	return true;
}
//��node����ڵ㸴�Ƶ�tree[x]�ĸ��ڵ㴦��ͬʱ����ָ��
void copy_node(query_tree &tree, int x, treenode &node)
{	tree.node[++tree.num] = node;
	int child_pos;
	for (int i = 1;i <= tree.node[tree.node[x].fa].child[0];i++)
	{	if (tree.node[tree.node[x].fa].child[i] == x) child_pos = i;
	}
	//����ָ��
	tree.node[tree.num].fa = tree.node[x].fa;
	tree.node[tree.node[x].fa].child[child_pos] = tree.num;
	tree.node[tree.num].child[0] = 1;
	tree.node[tree.num].child[1] = x;
	tree.node[x].fa = tree.num;
}
//ɾ�����е�һ���ڵ㣬ͬʱ����ָ��
void delete_node(query_tree &tree, int x)
{	int child_pos;
	for (int i = 1;i <= tree.node[tree.node[x].fa].child[0];i++)
	{	if (tree.node[tree.node[x].fa].child[i] == x) child_pos = i;
	}
	//���¸��ڵ�Ķ����б�
	for (int i = child_pos; i < tree.node[tree.node[x].fa].child[0]; i++)
	{	tree.node[tree.node[x].fa].child[i] = tree.node[tree.node[x].fa].child[i + 1];
	}
	tree.node[tree.node[x].fa].child[0]--;
	//�������ڵ��ж��ӣ���ֻ����һ�����ӣ���������ڵ㲻��ɾ��
	if (tree.node[x].child[0] == 1)
	{	tree.node[tree.node[x].fa].child[++tree.node[tree.node[x].fa].child[0]] = tree.node[x].child[1];
		tree.node[tree.node[x].child[1]].fa = tree.node[x].fa;
	}
	//ɾ������ڵ�
	tree.node[x].type = -1;
}

void push_condition_down(query_tree &tree)
{	//��ѯ��������
	int en = tree.num;
	//��Ƭ�б�
	int q[maxtreenode], r = 0;
	for (int i = 1;i <= en;i++)
	{	if (tree.node[i].type == 0)
		{	q[++r] = i;
		}
	}
	for (int i = 1;i <= en;i++)
	{	if (tree.node[i].type == 3) //��������������
		{	//�ж��Ƿ�Ҫ���뵽��Ƭ��
			for (int j = 1;j <= r;j++)
			{	//�жϲ�ѯ���������ԣ���Ƭ�Ƿ�ӵ��
				if (q[j] == -1) continue;
				cout << tree.node[i].str << " " << tree.node[q[j]].str << endl;
				if (match_condition_frag(tree.node[i].str, tree.node[q[j]], tree))
				{	//��ֱ��Ƭ���߲���Ƭ�����������ʵ�Ϳ���ֱ�Ӳ�����
					if (tree.node[i].type == 1 || tree.node[i].type == -1)
					{	cout << tree.node[i].str << " ���� " << tree.node[q[j]].str << endl;
						copy_node(tree, q[j], tree.node[i]);
					}
					//��������������Ե�����£���ѯ�����������Ƭ���Ƿ��н����Ҳ���ǲ�ѯ�����Ƿ����Ƭ�����н���
					else
					{	if (condition_intersect(tree.node[i].str, tree.node[q[j]], tree))
						{	cout << "�������Ƭƥ�䣬����" << endl;
							copy_node(tree, q[j], tree.node[i]);
						}
						else
						{	cout << "�������Ƭ��ƥ�䣬ɾ����һ֦" << endl;
							int to_del = q[j];
							//�Ե�����һֱɾ��union
							while (tree.node[to_del].type != 1)
							{	delete_node(tree, to_del);
								to_del = tree.node[to_del].fa;
							}
							q[j] = -1;
							//���ɾ��unionֻ��һ�������ˣ���unionҲɾ��
							if (tree.node[to_del].child[0] == 1) delete_node(tree, to_del);
						}
					}
				}
				//û�о�ʲô������
				else
				{	cout << "ʲô������" << endl;
				}
			}
			//���꽫�����ѯ����ɾ��
			delete_node(tree, i);
		}
	}

}

//�������Ʋ����������Ż�
void get_basic_opt_tree(query_tree &tree)
{	//��һ��������������
	push_condition_down(tree);
	//�ڶ�������ͶӰ��������

	//�������������Ӳ�������

	
}
