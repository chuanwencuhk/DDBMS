#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "../include/query_tree.h"

using namespace std;

schema sch;

//SAL(title char(20) primary key, sal float not null)
//EMP(eno char(20) primary key, ename char(20) not null, title char(20))
//JOB(jno char(20) primary key, jname char(20) not null, budget float not null, loc char(20) not null)
//ASG(eno char(20), jno char(20), resp char(20) not null, dur int not null)
void init_schema()
{
	sch.table_num = 4;

	sch.table[1].table_name = "publisher";	sch.table[2].table_name = "book";
	sch.table[3].table_name = "customer";	sch.table[4].table_name = "orders";
	
	sch.table[1].site_num = 4;	sch.table[1].type = 0;
	sch.table[1].site[1].condition[0] = "publisher_id<104000&nation='PRC'";		sch.table[1].site[2].condition[0] = "publisher_id<104000&nation='USA'";
	sch.table[1].site[3].condition[0] = "publisher_id>=104000&nation='PRC'";		sch.table[1].site[4].condition[0] = "publisher_id>=104000&nation='USA'";
	//��Ƭ����
	sch.table[1].site[1].hcon_list_len = 2;	sch.table[1].site[2].hcon_list_len = 2;
	sch.table[1].site[3].hcon_list_len = 2; sch.table[1].site[4].hcon_list_len = 2;
	sch.table[1].site[1].hcon_list[1].attr = "publisher_id";	  sch.table[1].site[1].hcon_list[1].op = "<";  sch.table[1].site[1].hcon_list[1].section = "104000";
	sch.table[1].site[1].hcon_list[2].attr = "nation"; sch.table[1].site[1].hcon_list[2].op = "=";  sch.table[1].site[1].hcon_list[2].section = "'PRC'";
	sch.table[1].site[2].hcon_list[1].attr = "publisher_id";   sch.table[1].site[2].hcon_list[1].op = "<";  sch.table[1].site[2].hcon_list[1].section = "104000";
	sch.table[1].site[2].hcon_list[2].attr = "nation"; sch.table[1].site[2].hcon_list[2].op = "="; sch.table[1].site[2].hcon_list[2].section = "'USA'";
	sch.table[1].site[3].hcon_list[1].attr = "publisher_id";   sch.table[1].site[3].hcon_list[1].op = ">="; sch.table[1].site[3].hcon_list[1].section = "104000";
	sch.table[1].site[3].hcon_list[2].attr = "nation"; sch.table[1].site[3].hcon_list[2].op = "=";  sch.table[1].site[3].hcon_list[2].section = "'PRC'";
	sch.table[1].site[4].hcon_list[1].attr = "publisher_id";   sch.table[1].site[4].hcon_list[1].op = ">="; sch.table[1].site[4].hcon_list[1].section = "104000";
	sch.table[1].site[4].hcon_list[2].attr = "nation"; sch.table[1].site[4].hcon_list[2].op = "="; sch.table[1].site[4].hcon_list[2].section = "'USA'";
	//��������Ϣ
	sch.table[1].col_num = 3;
	sch.table[1].col_name[1] = "publisher_id";	sch.table[1].col_name[2] = "name";	sch.table[1].col_name[3] = "nation";

	sch.table[2].site_num = 3;	sch.table[2].type = 0;
	sch.table[2].site[1].condition[0] = "book_id<205000";		sch.table[2].site[2].condition[0] = "book_id>=205000&book_id<210000";
	sch.table[2].site[3].condition[0] = "book_id>=210000";	
	//��Ƭ����
	sch.table[2].site[1].hcon_list_len = 1;	sch.table[2].site[2].hcon_list_len = 2;
	sch.table[2].site[3].hcon_list_len = 1; 
	sch.table[2].site[1].hcon_list[1].attr = "book_id";	  sch.table[2].site[1].hcon_list[1].op = "<";  sch.table[2].site[1].hcon_list[1].section = "205000";
	sch.table[2].site[2].hcon_list[1].attr = "book_id";   sch.table[2].site[2].hcon_list[1].op = ">=";  sch.table[2].site[2].hcon_list[1].section = "205000";
	sch.table[2].site[2].hcon_list[2].attr = "book_id"; sch.table[2].site[2].hcon_list[2].op = "<"; sch.table[2].site[2].hcon_list[2].section = "210000";
	sch.table[2].site[3].hcon_list[1].attr = "book_id";   sch.table[2].site[3].hcon_list[1].op = ">="; sch.table[2].site[3].hcon_list[1].section = "210000";
	//��������Ϣ
	sch.table[2].col_num = 5;
	sch.table[2].col_name[1] = "book_id";	sch.table[2].col_name[2] = "title";	sch.table[2].col_name[3] = "authors";
	sch.table[2].col_name[4] = "publisher_id";	sch.table[2].col_name[5] = "copies";

	sch.table[3].site_num = 2;	sch.table[3].type = 1;
	sch.table[3].site[1].condition[1] = "customer_id,name";
	sch.table[3].site[2].condition[1] = "customer_id,rank";
	//��������Ϣ
	sch.table[3].col_num = 3;
	sch.table[3].col_name[1] = "customer_id";	sch.table[3].col_name[2] = "name";	sch.table[3].col_name[3] = "rank";	

	sch.table[4].site_num = 4;	sch.table[4].type = 0;
	sch.table[4].site[1].condition[0] = "customer_id<307000&book_id<215000";		sch.table[4].site[2].condition[0] = "customer_id<307000&book_id>=215000";
	sch.table[4].site[3].condition[0] = "customer_id>=307000&book_id<215000";		sch.table[4].site[4].condition[0] = "customer_id>=307000&book_id>=215000";
	//��Ƭ����
	sch.table[4].site[1].hcon_list_len = 2;	sch.table[4].site[2].hcon_list_len = 2;
	sch.table[4].site[3].hcon_list_len = 2; sch.table[4].site[4].hcon_list_len = 2;
	sch.table[4].site[1].hcon_list[1].attr = "customer_id";	  sch.table[4].site[1].hcon_list[1].op = "<";  sch.table[4].site[1].hcon_list[1].section = "307000";
	sch.table[4].site[1].hcon_list[2].attr = "book_id";   sch.table[4].site[1].hcon_list[2].op = "<";  sch.table[4].site[1].hcon_list[2].section = "215000";
	sch.table[4].site[2].hcon_list[1].attr = "customer_id";   sch.table[4].site[2].hcon_list[1].op = "<";  sch.table[4].site[2].hcon_list[1].section = "307000";
	sch.table[4].site[2].hcon_list[2].attr = "book_id";   sch.table[4].site[2].hcon_list[2].op = ">="; sch.table[4].site[2].hcon_list[2].section = "215000";
	sch.table[4].site[3].hcon_list[1].attr = "customer_id";   sch.table[4].site[3].hcon_list[1].op = ">="; sch.table[4].site[3].hcon_list[1].section = "307000";
	sch.table[4].site[3].hcon_list[2].attr = "book_id";   sch.table[4].site[3].hcon_list[2].op = "<";  sch.table[4].site[3].hcon_list[2].section = "215000";
	sch.table[4].site[4].hcon_list[1].attr = "customer_id";   sch.table[4].site[4].hcon_list[1].op = ">="; sch.table[4].site[4].hcon_list[1].section = "307000";
	sch.table[4].site[4].hcon_list[2].attr = "book_id";   sch.table[4].site[4].hcon_list[2].op = ">="; sch.table[4].site[4].hcon_list[2].section = "215000";
	//��������Ϣ
	sch.table[4].col_num = 3;
	sch.table[4].col_name[1] = "customer_id";	sch.table[4].col_name[2] = "book_id";	sch.table[4].col_name[3] = "quantity";	

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
	int pos_dot = s.find(".");//�ҵ��ַ�"."��λ�ã�֮ǰ���Ǳ�������
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

//������������
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
		int pos_op;
		string op; int temp; string section;
		temp = condition.find("=", 0);  if (temp >= 0) {
			op = "="; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
		}
		temp = condition.find(">", 0);  if (temp >= 0) {
			op = ">"; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
		}
		temp = condition.find("<", 0);  if (temp >= 0) {
			op = "<"; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1); 
		}
		temp = condition.find(">=", 0); if (temp >= 0) {
			op = ">="; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
		}
		temp = condition.find("<=", 0); if (temp >= 0) {
			op = "<="; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
		}
		temp = condition.find("<>", 0); if (temp >= 0) {
			op = "<>"; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
		}
		//�ж����������ǲ��Ǳ���
		string str1 = condition.substr(0, pos_op);//����ַ���
		string str2 = section;//�Ҳ��ַ���
		//cout << op << pos_op << endl;
		//cout << str1 << " " << str2 << endl;
		if (isVar(str1) && isVar(str2))
		{	//���Ǳ�����Ϊ����
			int pos_l = loc(str1, o_tree), pos_r = loc(str2, o_tree);//ȷ�����ұ��������������е�λ��
			int fa1 = get_fa(o_tree, pos_l), fa2 = get_fa(o_tree, pos_r);
			//����join�ڵ�
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
//��schema�б���λ����Ϣ���ŵ�����
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
	//return o_tree;
	//��schema��Ϣ���뵽����
	insert_schema(o_tree, sch);
	//�����б����Ϊ��Ƭ
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
			{
				
				for (int j = 1; j <= sch.table[s_pos].site_num; j++) 
				{	//�Ȱѷ�Ƭ����
					o_tree.node[++o_tree.num].type = 0;
					o_tree.node[o_tree.num].child[0] = 0;
					o_tree.node[o_tree.num].fa = -1;
					o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
				}
				//�Գ������������Ƭ��������
				int en = o_tree.num;
				if (sch.table[s_pos].site_num > 2)
				for (int st = o_tree.num - sch.table[s_pos].site_num + 1;st < en-1;st++)
				{	//ȡ�����ڵ������
					int fa1 = get_fa(o_tree, st);  int fa2 = get_fa(o_tree, st+1);
					//�½�һ��join�ڵ�
					o_tree.node[++o_tree.num].type = 2;
					o_tree.node[fa1].fa = o_tree.num; o_tree.node[fa2].fa = o_tree.num;
					o_tree.node[o_tree.num].child[0] = 2;
					o_tree.node[o_tree.num].child[1] = fa1;
					o_tree.node[o_tree.num].child[2] = fa2;
				}
				//����������ڵ�join�����ڵĽڵ���
				int fa1 = get_fa(o_tree, en - 1); int fa2 = get_fa(o_tree, en);
				o_tree.node[i].type = 2; 
				o_tree.node[fa1].fa = i; o_tree.node[fa2].fa = i;
				o_tree.node[i].child[0] = 2; 
				o_tree.node[i].child[1] = fa1;
				o_tree.node[i].child[2] = fa2;
				o_tree.node[i].str = "";
			}
			//��Ϸ�Ƭ���Ƚ�ˮƽ������ͬ�������ӣ�Ȼ������
			if (sch.table[s_pos].type == 2)
			{	string attr[maxsite];//�������ڷ�Ƭ���Լ����б���Ҳ���Ǵ�ֱ��Ƭ����
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
				//for (int k = 1;k <= r;k++) cout << pos[k] << " " << attr[k] << " " << cond[k] << endl;
				//cout << endl;
				int en = o_tree.num;
				
				for (int j = 1;j <= r;j++)
				{	//�������û��������ͬ�ķ�Ƭ����ǰ����������ͬ�ģ���union��Ҳ����ȡ���һ����Ƭ����union
					bool can_union = false, last = true;
					for (int k = 1;k < j;k++)
						if (attr[j].compare(attr[k]) == 0) can_union = true;
					for (int k = j + 1; k <= r;k++)
						if (attr[j].compare(attr[k]) == 0) last = false;
					if (can_union && last)
					{   //cout << j << endl;
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
						//for (int k = 1;k <= r;k++) cout << pos[k] << " " << attr[k] << " " << cond[k] << endl;
						//cout << endl;
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
	//cout << "fuck\n";
	return o_tree;
	
}
//��������ļ�
void print_tree(query_tree tree)
{
	ofstream out("tree.txt");
	int q[maxtreenode], dep[maxtreenode], l = 1, r = 1;
	int root = tree.root;
	out << tree.root << endl;
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
	int pos_op;
	string op; int temp; string section;
	temp = condition.find("=", 0);  if (temp >= 0) {
		op = "="; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find(">", 0);  if (temp >= 0) {
		op = ">"; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find("<", 0);  if (temp >= 0) {
		op = "<"; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find(">=", 0); if (temp >= 0) {
		op = ">="; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	temp = condition.find("<=", 0); if (temp >= 0) {
		op = "<="; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	temp = condition.find("<>", 0); if (temp >= 0) {
		op = "<>"; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	//�ҵ�.��λ�ã��ѱ���ȥ��
	int pos_dot = condition.find(".", 0);
	string table_name = condition.substr(0, pos_dot);
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
		//cout << "find " << site << attr << endl;
		int pos = sch.table[sch_pos].site[site].condition[1].find(attr);
		if (pos >= 0)
		{
			//cout << sch.table[sch_pos].site[site].condition[1] << " "<<pos << endl;
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
	int pos_op;
	string op; int temp; string section;
	temp = condition.find("=", 0);  if (temp >= 0) {
		op = "="; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find(">", 0);  if (temp >= 0) {
		op = ">"; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find("<", 0);  if (temp >= 0) {
		op = "<"; pos_op = temp; section = condition.substr(pos_op + 1, condition.length() - pos_op - 1);
	}
	temp = condition.find(">=", 0); if (temp >= 0) {
		op = ">="; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	temp = condition.find("<=", 0); if (temp >= 0) {
		op = "<="; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	temp = condition.find("<>", 0); if (temp >= 0) {
		op = "<>"; pos_op = temp; section = condition.substr(pos_op + 2, condition.length() - pos_op - 2);
	}
	//cout << op << " " << section << endl;
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
			//cout << "�ж��Ƿ��㽶" << endl;
			bool flag = true;
			for (int i = 1;i <= sch.table[sch_pos].site[site].hcon_list_len;i++)
			{	//��Ϊֻ��AND�����Բ�ѯ����ֻ��һ����Ȼ���ѯ����������Ҫ��ÿ��������ͬ�ķ�Ƭ������Ҫ�н��
				if (attr.compare(sch.table[sch_pos].site[site].hcon_list[i].attr) == 0)
				{	//������ͬ�����Ƿ��ཻ
					//cout << "compare " << op << " "<<section<<" "<< sch.table[sch_pos].site[site].hcon_list[i].op << " "<< sch.table[sch_pos].site[site].hcon_list[i].section<< endl;
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
		//cout << "FUCK!!!!!!" << endl;
		int pos = sch.table[sch_pos].site[site].condition[1].find(attr);
		if (pos >= 0)
		//Ȼ���ˮƽ��Ƭһ���ж��Ƿ��н���
		{	//��Ƭ�������������
			if (sch.table[sch_pos].site[site].condition[0].find(attr) >= 0)
			{	//cout << "�ж��Ƿ��㽶" << endl;
				bool flag = true;
				for (int i = 1;i <= sch.table[sch_pos].site[site].hcon_list_len;i++)
				{	//��Ϊֻ��AND�����Բ�ѯ����ֻ��һ����Ȼ���ѯ����������Ҫ��ÿ��������ͬ�ķ�Ƭ������Ҫ�н��
					if (attr.compare(sch.table[sch_pos].site[site].hcon_list[i].attr) == 0)
					{	//������ͬ�����Ƿ��ཻ
						//cout << "compare " << op << " " << section << " " << sch.table[sch_pos].site[site].hcon_list[i].op << " " << sch.table[sch_pos].site[site].hcon_list[i].section << endl;
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
	if (tree.node[x].fa != -1)
	{
		for (int i = 1;i <= tree.node[tree.node[x].fa].child[0];i++)
		{
			if (tree.node[tree.node[x].fa].child[i] == x) child_pos = i;
		}
		//���¸��ڵ�Ķ����б�
		for (int i = child_pos; i < tree.node[tree.node[x].fa].child[0]; i++)
		{
			tree.node[tree.node[x].fa].child[i] = tree.node[tree.node[x].fa].child[i + 1];
		}
		tree.node[tree.node[x].fa].child[0]--;
		//�������ڵ��ж��ӣ���ֻ����һ�����ӣ�����û�ж��ӷ�������ڵ㲻��ɾ��
		if (tree.node[x].child[0] == 1)
		{	tree.node[tree.node[x].fa].child[++tree.node[tree.node[x].fa].child[0]] = tree.node[x].child[1];
			tree.node[tree.node[x].child[1]].fa = tree.node[x].fa;
		}
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
		{	//��ȡ��Ƭ�����ͷ�Ƭ���
			//cout << "aaa\n";
			
			//�Ȱ������ı���ȥ��
			//string con = tree.node[i].str;
			int pos = tree.node[i].str.find(".");
			if (pos >= 0) tree.node[i].str = tree.node[i].str.substr(pos + 1, tree.node[i].str.length() - pos - 1);
			
			//�ж��Ƿ�Ҫ���뵽��Ƭ��
			for (int j = 1;j <= r;j++)
			{
				if (q[j] == -1) continue;
				string x = tree.node[q[j]].str;
				int pos_colon = x.find(":");
				string name = ""; int site = 0;
				if (pos_colon < 0)
				{
					name = x;
					site = 1;
				}
				else
				{
					int len = x.length();
					name = x.substr(0, pos_colon);
					site = atoi(x.substr(pos_colon + 1, len - pos_colon - 1).c_str());
				}
				//cout << name << site << endl;
				
				//cout << tree.node[i].str << " " << tree.node[q[j]].str << endl;
				//�жϲ�ѯ���������ԣ���Ƭ�Ƿ�ӵ��
				//cout << tree.node[i].str << tree.node[q[j]].str << endl;
				if (match_condition_frag(tree.node[i].str, tree.node[q[j]], tree))
				{	//��ֱ��Ƭ���߲���Ƭ�����������ʵ�Ϳ���ֱ�Ӳ�����
					if (sch.table[tree.schema_pos[name]].type == 1 || sch.table[tree.schema_pos[name]].type == -1)
					{	//cout << tree.node[i].str << " ���� " << tree.node[q[j]].str << endl;
						copy_node(tree, q[j], tree.node[i]);
					}
					//��������������Ե�����£���ѯ�����������Ƭ���Ƿ��н����Ҳ���ǲ�ѯ�����Ƿ����Ƭ�����н���
					else
					{	if (condition_intersect(tree.node[i].str, tree.node[q[j]], tree))
						{	//cout << "�������Ƭƥ�䣬����" << endl;
							copy_node(tree, q[j], tree.node[i]);
						}
						else
						{	//cout << "�������Ƭ��ƥ�䣬ɾ����һ֦" << endl;
							int to_del = q[j];
							//�Ե�����һֱɾ��union
							while (tree.node[to_del].type != 1)
							{	delete_node(tree, to_del);
								to_del = tree.node[to_del].fa;
							}
							q[j] = -1;//�����Ƭ��Ϊ��Ч��Ƭ
							//���ɾ��unionֻ��һ�������ˣ���unionҲɾ��
							if (tree.node[to_del].child[0] == 1) delete_node(tree, to_del);
						}
					}
				}
				//û�о�ʲô������
				else
				{
					
					//����Ǵ�ֱ��Ƭ������û��������ԣ�����ɾ����һ֦
					if (sch.table[tree.schema_pos[name]].type == 1 && false)
					{	//��ͶӰ���Բ�ֵ�attr
						string s = tree.node[tree.root].str, t;
						int attr_num = 0;
						string attr[20];
						int pos = s.find(",");
						while (pos >= 0)
						{
							t = s.substr(0, pos);
							s = s.substr(pos + 1, s.length() - pos - 1);
							pos = t.find(".");
							if (pos<0)	attr[++attr_num] = t;
							else attr[++attr_num] = t.substr(pos+1, t.length()- pos -1);
							//cout << attr[attr_num] << endl;
							pos = s.find(",");
						}
						t = s;
						pos = t.find(".");
						if (pos<0)	attr[++attr_num] = t;
						else attr[++attr_num] = t.substr(pos + 1, t.length() - pos - 1);
						//�������Ƭ�ò���ɾ��
						bool frag_has_attr = false;
						for (int k = 1;k <= attr_num;k++)
						{
							string tmp = attr[k];
							pos = sch.table[tree.schema_pos[name]].site[site].condition[1].find(tmp);
							if (pos >= 0) frag_has_attr = true;
						}
						if (!frag_has_attr)
						{
							cout << "aa\n";
							delete_node(tree, q[j]);
							if (tree.node[tree.node[q[j]].fa].type == 2) delete_node(tree, tree.node[q[j]].fa);
						}

						
					}
				}
			}
			//���꽫�����ѯ����ɾ��
			delete_node(tree, i);
		}
	}

}

void clear_frag(query_tree &tree)
{	for (int i=1;i<=tree.num;i++)
	{
		if (tree.node[i].type == 2 && tree.node[i].str.compare("")==0)
		{	//������Ƿ���Ҫɾ��
			bool l = false, r = false;
			int pos;
			pos = tree.node[tree.node[i].child[1]].str.find(",");
			if (pos >= 0) l = true;
			if (tree.node[tree.node[tree.node[i].child[1]].child[1]].type == 3) l = true;
			pos = tree.node[tree.node[i].child[2]].str.find(",");
			if (pos >= 0) r = true;
			if (tree.node[tree.node[tree.node[i].child[2]].child[1]].type == 3) r = true;
			if (l == false)
			{	//ɾ��������
				tree.node[i].child[1] = tree.node[i].child[2];
				tree.node[i].child[0] = 1;
				delete_node(tree, i);
			}
			else if (r == false)
			{	//ɾ��������
				tree.node[i].child[0] = 1;
				delete_node(tree, i);
			}
		}
	}
}

void push_select_down(query_tree &tree)
{
	if (tree.node[tree.root].str.compare("*") == 0)
	{	//cout << "��������\n";
	}
	else
	{	//��Ҫʹ��ͶӰ����
		string s = tree.node[tree.root].str,t;
		//��ͶӰ���Բ�ֵ�attr
		int attr_num = 0;
		string attr[20];
		int pos = s.find(",");
		while (pos >= 0)
		{
			t = s.substr(0, pos);
			s = s.substr(pos + 1, s.length() - pos - 1);
			pos = t.find(".");
			if (pos<0)	attr[++attr_num] = t;
			else attr[++attr_num] = t.substr(pos+1, t.length()- pos -1);
			//cout << attr[attr_num] << endl;
			
			
			pos = s.find(",");
		}
		t = s;
		pos = t.find(".");
		if (pos<0)	attr[++attr_num] = t;
		else attr[++attr_num] = t.substr(pos + 1, t.length() - pos - 1);
		//cout << attr[attr_num] << endl;

		int en = tree.num;
		//ɨ��ȫ����������Ƭ������select
		for (int i = 1;i <= en;i++)
		{
			if (tree.node[i].type == 0)
			{	//��ȡ��Ƭ�����ͷ�Ƭ���
				//cout << "aaa\n";
				string x = tree.node[i].str;
				int pos_colon = x.find(":");
				string name = ""; int site = 0;
				if (pos_colon < 0)
				{
					name = x;
					site = 1;
				}
				else
				{
					int len = x.length();
					name = x.substr(0, pos_colon);
					site = atoi(x.substr(pos_colon + 1, len - pos_colon - 1).c_str());
				}
				//cout << name << site << endl;
				//�Ե����Ͽ��÷�Ƭ��Ҫ��Щ����
				int frag_attr_num = 0; string frag_attr[20];
				int p = i;
				while (tree.node[p].fa != -1)
				{
					if (tree.node[p].type == 2)//����join��÷�ƬӦ�������������е����ԣ���������еĻ�
					{
						string tmp = tree.node[p].str;
						if (tmp.compare("") == 0)
						{	//��Ƭ֮������ӣ�ȡ������Ƭ�Ĺ������ԣ���ʵ���Ƿ�Ƭ�����еĵ�һ������
							tmp = sch.table[tree.schema_pos[name]].site[site].condition[1];
							pos = tmp.find(",");
							tmp = tmp.substr(0, pos);
							//cout << tmp << endl;
						}
						else
						{   //����ȡ����.���������
							pos = tmp.find(".");
							tmp = tmp.substr(pos + 1, tmp.length() - pos - 1);
							pos = tmp.find(".");
							tmp = tmp.substr(pos + 1, tmp.length() - pos - 1);
							//cout << tmp << endl;
							//tmp��Ϊ��Ҫ�жϵ�����
						}
						//�ж�tmp�Ƿ�Ӧ�ü���
						bool frag_has_attr = false;//��Ƭ�Ƿ����������
						if (sch.table[tree.schema_pos[name]].type == 0 || sch.table[tree.schema_pos[name]].type == -1)
						{	//ˮƽ��Ƭ�Ͳ���Ƭ����Ӧ�ı��Ƿ�������
							for (int j = 1;j <= sch.table[tree.schema_pos[name]].col_num;j++)
								if (tmp.compare(sch.table[tree.schema_pos[name]].col_name[j]) == 0) frag_has_attr = true;
						}
						else
						{	//��ֱ��Ƭ�ͻ�Ϸ�Ƭ����Ƭ�������Ƿ���
							pos = sch.table[tree.schema_pos[name]].site[site].condition[1].find(tmp);
							if (pos >= 0) frag_has_attr = true;
						}
						if (frag_has_attr)
						{	//��������Բ��һ�δ����
							frag_has_attr = false;
							for (int j = 1;j <= frag_attr_num;j++)
								if (tmp.compare(frag_attr[j]) == 0) frag_has_attr = true;
							if (!frag_has_attr)
							{
								frag_attr[++frag_attr_num] = tmp;
								//cout << "add" << tmp << endl;
							}
						}

						//����������ǰ�������
						tmp = tree.node[p].str;
						if (tmp.compare("") == 0)
						{	//��Ƭ֮������ӣ�ȡ������Ƭ�Ĺ������ԣ���ʵ���Ƿ�Ƭ�����еĵ�һ������
							tmp = sch.table[tree.schema_pos[name]].site[site].condition[1];
							pos = tmp.find(",");
							tmp = tmp.substr(0, pos);
							//cout << tmp << endl;
						}
						else
						{   
							pos = tmp.find(".");
							tmp = tmp.substr(pos + 1, tmp.length() - pos - 1);
							//cout << tmp << endl;
							pos = tmp.find("=");
							tmp = tmp.substr(0, pos);
							//cout << tmp << endl;
							//tmp��Ϊ��Ҫ�жϵ�����
						}
						//�ж�tmp�Ƿ�Ӧ�ü���
						frag_has_attr = false;//��Ƭ�Ƿ����������
						if (sch.table[tree.schema_pos[name]].type == 0 || sch.table[tree.schema_pos[name]].type == -1)
						{	//ˮƽ��Ƭ�Ͳ���Ƭ����Ӧ�ı��Ƿ�������
							for (int j = 1;j <= sch.table[tree.schema_pos[name]].col_num;j++)
								if (tmp.compare(sch.table[tree.schema_pos[name]].col_name[j]) == 0) frag_has_attr = true;
						}
						else
						{	//��ֱ��Ƭ�ͻ�Ϸ�Ƭ����Ƭ�������Ƿ���
							pos = sch.table[tree.schema_pos[name]].site[site].condition[1].find(tmp);
							if (pos >= 0) frag_has_attr = true;
						}
						if (frag_has_attr)
						{	//��������Բ��һ�δ����
							frag_has_attr = false;
							for (int j = 1;j <= frag_attr_num;j++)
								if (tmp.compare(frag_attr[j]) == 0) frag_has_attr = true;
							if (!frag_has_attr)
							{
								frag_attr[++frag_attr_num] = tmp;
								//cout << "add" << tmp << endl;
							}
						}
					}
					//cout << "aaa\n" << endl;
					p = tree.node[p].fa;
				}
				//����ͶӰ�е����ԣ�������ԵĻ�
				for (int j = 1;j <= attr_num;j++)
				{
					bool frag_has_attr = false;
					string tmp = attr[j];
					if (sch.table[tree.schema_pos[name]].type == 0 || sch.table[tree.schema_pos[name]].type == -1)
					{	//ˮƽ��Ƭ�Ͳ���Ƭ����Ӧ�ı��Ƿ�������
						for (int j = 1;j <= sch.table[tree.schema_pos[name]].col_num;j++)
							if (tmp.compare(sch.table[tree.schema_pos[name]].col_name[j]) == 0) frag_has_attr = true;
					}
					else
					{	//��ֱ��Ƭ�ͻ�Ϸ�Ƭ����Ƭ�������Ƿ���
						pos = sch.table[tree.schema_pos[name]].site[site].condition[1].find(tmp);
						if (pos >= 0) frag_has_attr = true;
					}
					if (frag_has_attr)
					{	//��������Բ��һ�δ����
						frag_has_attr = false;
						for (int j = 1;j <= frag_attr_num;j++)
							if (tmp.compare(frag_attr[j]) == 0) frag_has_attr = true;
						if (!frag_has_attr) frag_attr[++frag_attr_num] = tmp;
					}
				}
				//����һ��ͶӰ�ڵ�
				tree.node[++tree.num].type = 4;
				tree.node[tree.num].str = "";
				//��Ѱ���ͶӰӦ�ò����λ��
				pos = i;
				while (tree.node[pos].fa != -1)
				{	//�嵽����ѡ���������Ϸ�
					if (tree.node[tree.node[pos].fa].type == 3) pos = tree.node[pos].fa;
					else break;
				}
				//cout << pos << " " << tree.node[tree.node[pos].fa].type << endl;
				tree.node[tree.num].child[0] = 1; tree.node[tree.num].child[1] = pos;
				tree.node[tree.num].fa = tree.node[pos].fa;
				for (int j = 1;j <= tree.node[tree.node[pos].fa].child[0];j++)
					if (tree.node[tree.node[pos].fa].child[j] == pos) tree.node[tree.node[pos].fa].child[j] = tree.num;
				tree.node[pos].fa = tree.num;
				for (int j = 1;j <= frag_attr_num;j++) 
					if (j==1) tree.node[tree.num].str += frag_attr[j];
					else tree.node[tree.num].str += ","+frag_attr[j];
				
			}
		}
		clear_frag(tree);
	}
	
	//���������ͶӰ����ɾ��
	/*tree.node[tree.root].type = -1;
	tree.node[tree.node[tree.root].child[1]].fa = -1;
	tree.root = tree.node[tree.root].child[1];
	*/
	
}


//��x��ʼ���ݹ鸴��x�������е����ṹ���뵽����fa�ڵ�֮��
void copy_branch(query_tree &tree, int x, int fa)
{	//�������Ƴ����Ľڵ�
	tree.node[++tree.num].type = tree.node[x].type;
	tree.node[tree.num].child[0] = 0;
	tree.node[tree.num].fa = fa;
	tree.node[tree.num].str = tree.node[x].str;
	//���ӵ�fa��
	tree.node[fa].child[++tree.node[fa].child[0]] = tree.num;

	int newnode = tree.num;
	for (int i = 1;i <= tree.node[x].child[0];i++)
		copy_branch(tree, tree.node[x].child[i], newnode);
}

//ͳ�ƴ�x��ʼ�����������ṹ�ж��ٽڵ�
int count_branch(query_tree &tree, int x)
{
	int sum = 1;
	for (int i = 1;i <= tree.node[x].child[0];i++) sum += count_branch(tree, tree.node[x].child[i]);
	return sum;
}


int dfs_push(query_tree &tree, int x)
{	//����ڵ�����ҷ�֧��Ŀ
	int l = 0, r = 0 ,sum = 0;
	//join׼������
	if (tree.node[x].type == 2)
	{
		l = dfs_push(tree, tree.node[x].child[1]);
		r = dfs_push(tree, tree.node[x].child[2]);
		if (l == 1 && r == 1)
		{
			//cout << x<<"û��Ҫ����\n";
			sum = 1;
		}
		else
		{	
			//cout << x<<" "<<l << " " << r << "��Ҫ����\n";
			//����join
			int q[100], num = 0, newjoin;//������join��ͷ�ڵ�
			int lroot = tree.node[x].child[1], rroot = tree.node[x].child[2];
			//�ж����Ƿ����㹻�Ŀռ����join����
			int l_branch, r_branch, node_to_add = 0;
			for (int i = 1;i <= l;i++)
			for (int j = 1;j <= r;j++)
			{
				if (l == 1) l_branch = count_branch(tree, lroot);
				else l_branch = count_branch(tree, tree.node[lroot].child[i]);

				if (r == 1) r_branch = count_branch(tree, rroot);
				else r_branch = count_branch(tree, tree.node[rroot].child[j]);
				
				node_to_add += (1 + l_branch + r_branch);
			}
			bool can_push = true;
			if (tree.num + node_to_add > maxtreenode) 
			{	//����Ľڵ����������Ĵ�С
				can_push = false; cout << x << tree.node[x].str << "����" << node_to_add << "���ڵ㣬�������Ĵ�С"<<endl;
			}
			if (l*r > maxsite - 1)
			{	//����ķ�֧������������֧
				can_push = false; cout << x << tree.node[x].str << "����" << node_to_add << "����֧������������֧" << endl;
			}
			if (can_push)
			{
				for (int i = 1;i <= l;i++)
					for (int j = 1;j <= r;j++)
					{
						//����һ����x��ͬ��join�ڵ�
						tree.node[++tree.num].type = tree.node[x].type;
						tree.node[tree.num].fa = x;
						tree.node[tree.num].str = tree.node[x].str;
						tree.node[tree.num].child[0] = 0;
						newjoin = tree.num;
						if (l == 1) copy_branch(tree, lroot, newjoin);
						else copy_branch(tree, tree.node[lroot].child[i], newjoin);

						if (r == 1) copy_branch(tree, rroot, newjoin);
						else copy_branch(tree, tree.node[rroot].child[j], newjoin);
						q[++num] = newjoin;

					}
				//���½���join�ڵ����ӵ�x��
				tree.node[x].child[0] = 0;
				for (int i = 1;i <= num;i++)
				{
					++tree.node[x].child[0];
					tree.node[x].child[i] = q[i];
				}
				tree.node[x].str = "";
				tree.node[x].type = 1;
				sum = num;
			}
			else sum = 1;
		}
		
	}
	else
	{
		for (int i = 1;i <= tree.node[x].child[0];i++)
		{	
			sum += dfs_push(tree, tree.node[x].child[i]);
		}
	}

	if (tree.node[x].child[0]==0) return 1;
	else return sum;
}

bool join_frag(query_tree &tree, string frag1, string frag2)
{	//��ȡfrag1,frag2�ı����ͷ�Ƭ���
	int pos_colon = frag1.find(":");
	string name1 = ""; int site1 = 0;
	if (pos_colon < 0)
	{
		name1 = frag1;
		site1 = 1;
	}
	else
	{
		int len = frag1.length();
		name1 = frag1.substr(0, pos_colon);
		site1 = atoi(frag1.substr(pos_colon + 1, len - pos_colon - 1).c_str());
	}
	pos_colon = frag2.find(":");
	string name2 = ""; int site2 = 0;
	if (pos_colon < 0)
	{
		name2 = frag2;
		site2 = 1;
	}
	else
	{
		int len = frag2.length();
		name2 = frag2.substr(0, pos_colon);
		site2 = atoi(frag2.substr(pos_colon + 1, len - pos_colon - 1).c_str());
	}
	//�鿴�Ƿ��н��
	int pos1 = tree.schema_pos[name1], pos2 = tree.schema_pos[name2];
	if (sch.table[pos1].type == 0 || sch.table[pos1].type == 2)
	if (sch.table[pos2].type == 0 || sch.table[pos2].type == 2)
	{	//ֻ��ˮƽ���߻�ϲ���ͨ�������ж��Ƿ��н�������ͨ���������жϲ�����
		//cout << "�Ƚ�" << frag1 << " " << frag2 << endl;
		for (int i = 1;i <= sch.table[pos1].site[site1].hcon_list_len;i++)
		for (int j = 1;j <= sch.table[pos2].site[site2].hcon_list_len;j++)
		{	
			string a1 = sch.table[pos1].site[site1].hcon_list[i].attr, a2 = sch.table[pos2].site[site2].hcon_list[j].attr;
			//cout << a1 << " " << a2 << endl;
			if (a1.compare(a2) == 0)
			{	//������ͬʱ���������Ƿ��н���
				if (!intersect(sch.table[pos1].site[site1].hcon_list[i].op, sch.table[pos1].site[site1].hcon_list[i].section, sch.table[pos2].site[site2].hcon_list[j]))
				{
					return false;
				}
			}
			if (name1.compare("book")==0)
			if (a1.compare("id") == 0 && a2.compare("book_id") == 0)
			{
				if (!intersect(sch.table[pos1].site[site1].hcon_list[i].op, sch.table[pos1].site[site1].hcon_list[i].section, sch.table[pos2].site[site2].hcon_list[j]))
				{
					return false;
				}
			}
			if (name2.compare("book") == 0)
			if (a1.compare("book_id") == 0 && a2.compare("id") == 0)
			{
				if (!intersect(sch.table[pos1].site[site1].hcon_list[i].op, sch.table[pos1].site[site1].hcon_list[i].section, sch.table[pos2].site[site2].hcon_list[j]))
				{
					return false;
				}
			}
			if (name1.compare("customer") == 0)
			if (a1.compare("id") == 0 && a2.compare("customer_id") == 0)
			{
				if (!intersect(sch.table[pos1].site[site1].hcon_list[i].op, sch.table[pos1].site[site1].hcon_list[i].section, sch.table[pos2].site[site2].hcon_list[j]))
				{
					return false;
				}
			}
			if (name2.compare("customer") == 0)
			if (a1.compare("customer_id") == 0 && a2.compare("id") == 0)
			{
				if (!intersect(sch.table[pos1].site[site1].hcon_list[i].op, sch.table[pos1].site[site1].hcon_list[i].section, sch.table[pos2].site[site2].hcon_list[j]))
				{
					return false;
				}
			}
		}
	}
	return true;
}


string dfs_delete(query_tree &tree, int x)
{
	string str = ""; int child = 0;
	if (tree.node[x].type == 0) return tree.node[x].str;
	else
	{
		for (int i = 1;i <= tree.node[x].child[0];i++)
		{
			string tmp = dfs_delete(tree, tree.node[x].child[i]);
			if (tmp.compare("") == 0) continue;//��ɾ����֦������
			child++; 
			if (str.compare("") ==0) str += tmp;
			else str += " "+tmp;
		}
	}
	//cout << x << " " << str << endl;
	//����join�ķ�Ƭ����str�Ƿ��н����û��ɾ����һ֧
	if (tree.node[x].type == 2)
	{	//��ȡ��Ƭ����
		string tmp = str;
		string frag[100]; int num = 0;
		int pos = tmp.find(" ");
		while (pos >= 0)
		{
			frag[++num] = tmp.substr(0, pos);
			tmp = tmp.substr(pos+1, tmp.length()-pos-1);
			pos = tmp.find(" ");
			//cout << tmp << "��";
		}
		frag[++num] = tmp;
		
		//��������Ƭ�Ƿ��޽��
		bool have_res = true;
		for (int i = 1;i <= num;i++)
		for (int j = i + 1;j <= num;j++)
		{
			if (!join_frag(tree, frag[i], frag[j])) have_res = false;
		}
		if (!have_res || child <= 1)
		{	//ɾ������ڵ�
			//cout << "ɾ��" << x << " " << str << endl;
			tree.node[x].type = -1;
			str = "";
		}
	}
	return str;
}
//������ɾ���Ľڵ�
void clear_tree(query_tree &tree, int x)
{	for (int i=1;i<=tree.node[x].child[0];i++)
	{
		if (tree.node[tree.node[x].child[i]].type == -1)
		{
			for (int j = i;j <= tree.node[x].child[0] - 1;j++) tree.node[x].child[j] = tree.node[x].child[j + 1];
			tree.node[x].child[0]--;
			i--; continue;
		}
		clear_tree(tree, tree.node[x].child[i]);
	}
}

void push_join_down(query_tree &tree)
{	//������ȱ����������    
	dfs_push(tree, tree.root);
	//ɾ��û�н����ķ�֧
	dfs_delete(tree, tree.root);
	clear_tree(tree, tree.root);
}

//�������Ʋ����������Ż�
void get_basic_opt_tree(query_tree &tree, int level)
{	//��һ��������������
	if (level>=1) push_condition_down(tree);
	//�ڶ�������ͶӰ��������
	if (level>=2) push_select_down(tree);
	//�������������Ӳ�������
	if (level >= 3)
	{   push_join_down(tree);
	}
	
}
