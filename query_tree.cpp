#include <iostream>
#include <fstream>
#include <string>
#include <map>
#define maxsite 4+1
#define maxcol 10
#define maxtreenode 100
#define max_table_num 10

using namespace std;


struct fragment
{
	string condition[2];
};

struct schema_node
{
	string table_name;
	int type;//0--horizontal 1--vertical 2--hybrid -1--no fragment
	int col_num;//�е�����
	string col_name[maxcol];
	int site_num;
	fragment site[maxsite];

};
struct schema
{
	int table_num;
	schema_node table[max_table_num];
};

struct treenode
{
	int type;//0�Ƿ�Ƭ 1��union 2��join 3�Ǹ���conditionѡ��Ԫ�� 4��ͶӰȡ����
	string str;//���ڵ������
	int child[maxsite];//���ӽڵ�ָ�룬û����Ϊ-1,child[0]��ʾ������
	int fa;//���ڵ�ָ��
	int depth;
};
struct query_tree
{
	int table_num;//�ܹ��ж��ٸ���
	map<string, int> schema_pos;//���������ֵ��б��λ��
	map<string, int> table_pos;//�������������б��λ��
	treenode node[maxtreenode];
	int root = -1;//���ڵ�
	int num = 0;//��ǰ�ڵ���
};

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
	sch.table[2].col_num = 3;
	sch.table[2].col_name[1] = "eno";	sch.table[2].col_name[2] = "ename";	sch.table[2].col_name[3] = "title";

	sch.table[3].site_num = 4;	sch.table[3].type = 2;
	sch.table[3].site[1].condition[0] = "jno<'J0500'";	sch.table[3].site[1].condition[1] = "jno,jname,budget";
	sch.table[3].site[2].condition[0] = "jno<'J0500'";	sch.table[3].site[2].condition[1] = "jno,loc";
	sch.table[3].site[3].condition[0] = "jno>='J0500'";	sch.table[3].site[3].condition[1] = "jno,jname,budget";
	sch.table[3].site[4].condition[0] = "jno>='J0500'";	sch.table[3].site[4].condition[1] = "jno,loc";
	sch.table[3].col_num = 4;
	sch.table[3].col_name[1] = "jno";	sch.table[3].col_name[2] = "jname";	sch.table[3].col_name[3] = "budget";	sch.table[3].col_name[4] = "loc";

	sch.table[4].site_num = 4;	sch.table[4].type = 0;
	sch.table[4].site[1].condition[0] = "eno<'E1000'&jno<'J0500'";		sch.table[4].site[2].condition[0] = "eno<'E1000'&jno>='J0500'";
	sch.table[4].site[3].condition[0] = "eno>='E1000'&jno<'J0500'";		sch.table[4].site[4].condition[0] = "eno>='E1000'&jno>='J0500'";
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

int get_fa(query_tree &tree, int i)
{	while (tree.node[i].fa!=-1)
	{
		i = tree.node[i].fa;
	}
	return i;
}

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

void init_schema(query_tree &o_tree, schema &sch)
{
	for (int i = 1; i <= sch.table_num; i++)
	{
		o_tree.schema_pos[sch.table[i].table_name] = i;
	}
}

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
	init_schema(o_tree, sch);
	//�����б���Ϊ��Ƭ
	int i = 1;
	while (o_tree.node[i].type == 0)
	{	int s_pos = o_tree.schema_pos[o_tree.node[i].str];
		//�����Ƭ�ˣ��Ȱ��������union
		if (sch.table[s_pos].site_num > 1)
		{
			o_tree.node[i].type = 1;	o_tree.node[i].str = "";
			o_tree.node[i].child[0] = sch.table[s_pos].site_num;
			for (int j = 1; j <= sch.table[s_pos].site_num; j++)
			{
				o_tree.node[++o_tree.num].type = 0;
				o_tree.node[o_tree.num].fa = i;
				o_tree.node[o_tree.num].child[0] = 0;
				o_tree.node[i].child[j] = o_tree.num;
				if (sch.table[s_pos].type == 0)	o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
				else if (sch.table[s_pos].type == 1)	o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
				else if (sch.table[s_pos].type == 2)
					o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
				else if (sch.table[s_pos].type == -1)//����Ƭ�����
					o_tree.node[o_tree.num].str = sch.table[s_pos].table_name;
			}
		}
		i++;
	}

	return o_tree;
}

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


int main()
{
	string input="select * from emp,job,sal,asg where (emp.title=sal.title) and (emp.eno=asg.eno) and (job.jno=asg.jno) and (emp.eno<'E0010')";
	init_schema();
	query_tree original_tree = get_original_tree(input);
	//cout << original_tree.num << endl;
	//cout << table_pos["job"] << endl;
	print_tree(original_tree);
	system("pause");
	return 0;
}