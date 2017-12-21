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
	//分片条件
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
	//表的列信息
	sch.table[2].col_num = 3;
	sch.table[2].col_name[1] = "eno";	sch.table[2].col_name[2] = "ename";	sch.table[2].col_name[3] = "title";

	sch.table[3].site_num = 4;	sch.table[3].type = 2;
	sch.table[3].site[1].condition[0] = "jno<'J0500'";	sch.table[3].site[1].condition[1] = "jno,jname,budget";
	sch.table[3].site[2].condition[0] = "jno<'J0500'";	sch.table[3].site[2].condition[1] = "jno,loc";
	sch.table[3].site[3].condition[0] = "jno>='J0500'";	sch.table[3].site[3].condition[1] = "jno,jname,budget";
	sch.table[3].site[4].condition[0] = "jno>='J0500'";	sch.table[3].site[4].condition[1] = "jno,loc";
	//分片条件
	sch.table[3].site[1].hcon_list_len = 1;	sch.table[3].site[2].hcon_list_len = 1;
	sch.table[3].site[3].hcon_list_len = 1; sch.table[3].site[4].hcon_list_len = 1;
	sch.table[3].site[1].hcon_list[1].attr = "jno";   sch.table[3].site[1].hcon_list[1].op = "<";   sch.table[3].site[1].hcon_list[1].section = "'J0500'";
	sch.table[3].site[2].hcon_list[1].attr = "jno";   sch.table[3].site[2].hcon_list[1].op = "<";   sch.table[3].site[2].hcon_list[1].section = "'J0500'";
	sch.table[3].site[3].hcon_list[1].attr = "jno";   sch.table[3].site[3].hcon_list[1].op = ">=";  sch.table[3].site[3].hcon_list[1].section = "'J0500'";
	sch.table[3].site[4].hcon_list[1].attr = "jno";   sch.table[3].site[4].hcon_list[1].op = ">=";  sch.table[3].site[4].hcon_list[1].section = "'J0500'";
	//表的列信息
	sch.table[3].col_num = 4;
	sch.table[3].col_name[1] = "jno";	sch.table[3].col_name[2] = "jname";	sch.table[3].col_name[3] = "budget";	sch.table[3].col_name[4] = "loc";

	sch.table[4].site_num = 4;	sch.table[4].type = 0;
	sch.table[4].site[1].condition[0] = "eno<'E1000'&jno<'J0500'";		sch.table[4].site[2].condition[0] = "eno<'E1000'&jno>='J0500'";
	sch.table[4].site[3].condition[0] = "eno>='E1000'&jno<'J0500'";		sch.table[4].site[4].condition[0] = "eno>='E1000'&jno>='J0500'";
	//分片条件
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
	//表的列信息
	sch.table[4].col_num = 4;
	sch.table[4].col_name[1] = "eno";	sch.table[4].col_name[2] = "jno";	sch.table[4].col_name[3] = "resp";	sch.table[4].col_name[4] = "dur";

}


//求最大值
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
//判断一个字符串是否为变量
bool isVar(string s)
{	//是字符串
	if (s.substr(0, 1) == "\"" || s.substr(0, 1) == "'") return false;
	//是数字
	if (s.substr(0, 1) >= "0" && s.substr(0, 1) <= "9") return false;
	return true;
}

int loc(string s, query_tree &o_tree)
{
	int pos_dot = s.find(".");//找到字符"."的位置，之前就是表的名字
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

//将表插入树中
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
		//插入table_name
		o_tree.node[++o_tree.num].type = 0;
		o_tree.node[o_tree.num].str = table_name;
		o_tree.node[o_tree.num].fa = -1;
		o_tree.node[o_tree.num].child[0] = 0;
		o_tree.table_pos[table_name] = o_tree.num;
		o_tree.table_num = o_tree.num;

		if (pos < 0) break;
	}

}
//找到tree[i]的祖先
int get_fa(query_tree &tree, int i)
{	while (tree.node[i].fa!=-1)
	{
		i = tree.node[i].fa;
	}
	return i;
}
//把查询条件插入到树中
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
		//得到一条condition，插入树中
		//判断是不是一个连接，两边都是变量的话就是连接
		//确定比较操作符位置
		int pos_op = maxint(condition.find("=", 0), maxint(condition.find(">", 0), condition.find("<", 0)));
		pos_op = maxint(pos_op, maxint(condition.find(">=", 0), maxint(condition.find("<=", 0), condition.find("<>", 0))));
		//判断左右两侧是不是变量
		string str1 = condition.substr(0, pos_op);//左侧字符串
		string str2 = condition.substr(pos_op+1, condition.length() - pos_op);//右侧字符串
		if (isVar(str1) && isVar(str2))
		{	//都是变量则为连接
			int pos_l = loc(str1, o_tree), pos_r = loc(str2, o_tree);//确定左右变量的祖先在树中的位置
			int fa1 = get_fa(o_tree, pos_l), fa2 = get_fa(o_tree, pos_r);
			//添加join节点
			o_tree.node[++o_tree.num].type = 2;
			o_tree.node[o_tree.num].str = condition;
			o_tree.node[o_tree.num].fa = -1;
			o_tree.node[o_tree.num].child[0] = 2;
			o_tree.node[o_tree.num].child[1] = fa1;	o_tree.node[o_tree.num].child[2] = fa2;
			//更改子节点的父指针
			o_tree.node[fa1].fa = o_tree.num;			o_tree.node[fa2].fa = o_tree.num;

			//cout << get_fa(o_tree, pos_l) << " " << get_fa(o_tree, pos_r) << endl;
		}
		else
		{	//否则为条件操作，此时所有表已经有一个公共祖先，将条件操作插到公共祖先的头上
			int fa = get_fa(o_tree, 1);//随便取第一个节点的祖先就是公共祖先
			//cout << "fa is:" << fa << endl;
			//插入条件操作
			o_tree.node[++o_tree.num].type = 3;
			o_tree.node[o_tree.num].str = condition;
			o_tree.node[o_tree.num].fa = -1;
			o_tree.node[o_tree.num].child[0] = 1; o_tree.node[o_tree.num].child[1] = fa;
			o_tree.node[fa].fa = o_tree.num;
		}
	}

}
//把schema中表的位置信息，放到树中
void insert_schema(query_tree &o_tree, schema &sch)
{
	for (int i = 1; i <= sch.table_num; i++)
	{
		o_tree.schema_pos[sch.table[i].table_name] = i;
	}
}
//获取带有分片信息的最原始的查询树
query_tree get_original_tree(string s)
{
	query_tree o_tree;
	//将需要查询表先放入树中
	string sql = s;
	sql.erase(0, 7);//删掉select
	int pos1 = sql.find("from");
	int pos2 = sql.find(" ", pos1+5);
	//cout << pos1 << sql << endl;
	string table_list = sql.substr(pos1+5, pos2-pos1-5);
	insert_table_list(table_list, o_tree);
	//cout << table_list << endl;

	//将查询条件部署到树中
	pos2 = sql.find("where")+6;
	string condition = sql.substr(pos2, sql.length() - pos2);
	//cout << condition << endl;
	insert_condition(condition, o_tree);

	//将投影操作部署到树中
	string select = sql.substr(0, pos1-1);
	//cout << pos1<<select << endl;
	int fa = get_fa(o_tree, 1);//随便取第一个节点的祖先就是公共祖先
	o_tree.node[++o_tree.num].type = 4;
	o_tree.node[o_tree.num].str = select;
	o_tree.node[o_tree.num].fa = -1;
	o_tree.node[o_tree.num].child[0] = 1; o_tree.node[o_tree.num].child[1] = fa;
	o_tree.node[fa].fa = o_tree.num;
	
	o_tree.root = o_tree.num;
	//把schema信息放入到树中
	insert_schema(o_tree, sch);
	//将所有表拆分为分片
	int i = 1;
	while (o_tree.node[i].type == 0)
	{	int s_pos = o_tree.schema_pos[o_tree.node[i].str];
		if (sch.table[s_pos].site_num > 1)
		{	//水平分片直接拆成站点的union
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
			//垂直分片拆成站点的连接
			if (sch.table[s_pos].type == 1)
			{	for (int j = 1; j <= sch.table[s_pos].site_num; j++)
				{	//先把分片插入
					o_tree.node[++o_tree.num].type = 0;
					o_tree.node[o_tree.num].child[0] = 0;
					o_tree.node[o_tree.num].fa = -1;
					o_tree.node[o_tree.num].str = sch.table[s_pos].table_name + ":" + to_string(j);
				}
				//对除了最后两个分片两两连接
				int en = o_tree.num;
				for (int st = o_tree.num - sch.table[s_pos].site_num + 1;st < en-1;st++)
				{	//取两个节点的祖先
					int fa1 = get_fa(o_tree, st);  int fa2 = get_fa(o_tree, st+1);
					//新建一个join节点
					o_tree.node[++o_tree.num].type = 2;
					o_tree.node[o_tree.num].child[0] = 2;
					o_tree.node[o_tree.num].child[1] = fa1;
					o_tree.node[o_tree.num].child[2] = fa2;
				}
				//将最后两个节点join到现在的节点上
				int fa1 = get_fa(o_tree, en - 1); int fa2 = get_fa(o_tree, en);
				o_tree.node[i].type = 2; 
				o_tree.node[i].child[0] = 2; 
				o_tree.node[o_tree.num].child[1] = fa1;
				o_tree.node[o_tree.num].child[2] = fa2;
			}
			//混合分片，先将水平条件相同的做连接，然后做并
			if (sch.table[s_pos].type == 2)
			{	string attr[maxsite];//保存现在分片属性集的列表，也就是垂直分片条件
				string cond[maxsite];//保存水平分片列表
				int pos[maxsite];//保存分片在树中的位置
				int r = sch.table[s_pos].site_num;
				for (int j = 1; j <= sch.table[s_pos].site_num; j++)
				{	//先把分片插入
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
				{	//如果后面没有属性相同的分片，且前面有属性相同的，则union，也就是取最后一个分片来做union
					bool can_union = false, last = true;
					for (int k = 1;k < j;k++)
						if (attr[j].compare(attr[k]) == 0) can_union = true;
					for (int k = j + 1; k <= r;k++)
						if (attr[j].compare(attr[k]) == 0) last = false;
					if (can_union && last)
					{   cout << j << endl;
						//先创造一个union节点
						o_tree.node[++o_tree.num].type = 1;
						o_tree.node[o_tree.num].child[0] = 0;
						o_tree.node[o_tree.num].fa = -1;
						//将能union的union进来
						for (int k = 1; k <= j;k++)
						{
							if (attr[j].compare(attr[k]) == 0)
							{
								o_tree.node[o_tree.num].child[++o_tree.node[o_tree.num].child[0]] = pos[k];
								o_tree.node[pos[k]].fa = o_tree.num;
							}
						}
						//union之后删除,只保留一个分片即可
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
			
				
				//找可以join的分片，经过上一步，属性相同的已经union，将所有分片join
				for (int j=1;j<r-2;j++)
				{	//取两个节点的祖先
					int fa1 = get_fa(o_tree, pos[j]);  int fa2 = get_fa(o_tree, pos[j+1]);
					//新建一个join节点
					o_tree.node[++o_tree.num].type = 2;
					o_tree.node[o_tree.num].child[0] = 2;
					o_tree.node[o_tree.num].child[1] = fa1; o_tree.node[fa1].fa = o_tree.num;
					o_tree.node[o_tree.num].child[2] = fa2; o_tree.node[fa2].fa = o_tree.num;
				}
						
				//将最后两个节点join到现在的节点上
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
//输出树到文件
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

//判断查询条件的字符串condition，与分片是否匹配
bool match_condition_frag(string condition, treenode &x, query_tree &tree)
{	//暂时只写AND的情况，即一个括号里只有一个条件
	//确定比较操作符位置
	int pos_op = maxint(condition.find("=", 0), maxint(condition.find(">", 0), condition.find("<", 0)));
	pos_op = maxint(pos_op, maxint(condition.find(">=", 0), maxint(condition.find("<=", 0), condition.find("<>", 0))));
	//找到.的位置，把表名去掉
	int pos_dot = condition.find(".", 0);
	//提取出查询条件的属性
	string attr = "";
	if (pos_dot < 0) attr = condition.substr(0, pos_op);		
	else attr = condition.substr(pos_dot + 1, pos_op - pos_dot - 1);
	//提取tree.node[x]的表名和分片序号
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
	//确定这个分片有没有这个属性
	int sch_pos = tree.schema_pos[name];
	//cout << sch_pos << " " <<name <<endl;
	//水平和不分片查找对应的表是否有该属性
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
	{	//看垂直分片信息上是否有该属性
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
{	//确定比较操作符位置 和 比较操作符
	int pos_op = maxint(condition.find("=", 0), maxint(condition.find(">", 0), condition.find("<", 0)));
	pos_op = maxint(pos_op, maxint(condition.find(">=", 0), maxint(condition.find("<=", 0), condition.find("<>", 0))));
	//不等于的情况值得考虑一下
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
	//找到.的位置，把表名去掉
	int pos_dot = condition.find(".", 0);
	//提取出查询条件的属性
	string attr = "";
	if (pos_dot < 0) attr = condition.substr(0, pos_op);
	else attr = condition.substr(pos_dot + 1, pos_op - pos_dot - 1);
	//提取tree.node[x]的表名和分片序号
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
	//首先确定这个分片条件有没有这个属性
	int sch_pos = tree.schema_pos[name];
	//水平分片
	if (sch.table[sch_pos].type == 0)
	{	//分片条件有这个属性
		if (sch.table[sch_pos].site[site].condition[0].find(attr) >= 0)
		{	//则有这个属性，判断区间是否相交
			cout << "判断是否香蕉" << endl;
			bool flag = true;
			for (int i = 1;i <= sch.table[sch_pos].site[site].hcon_list_len;i++)
			{	//因为只有AND，所以查询条件只有一个，然后查询条件的区间要与每个属性相同的分片条件都要有结果
				if (attr.compare(sch.table[sch_pos].site[site].hcon_list[i].attr) == 0)
				{	//属性相同，看是否相交
					cout << "compare " << op << " "<<section<<" "<< sch.table[sch_pos].site[site].hcon_list[i].op << " "<< sch.table[sch_pos].site[site].hcon_list[i].section<< endl;
					if (!intersect(op, section, sch.table[sch_pos].site[site].hcon_list[i])) flag = false;
				}
			}
			return flag;
		}
		//否则可能存在结果
		else return true;
	}
	//混合分片
	else if (sch.table[sch_pos].type == 2)
	{	//首先垂直分片条件得有这个属性
		cout << "FUCK!!!!!!" << endl;
		int pos = sch.table[sch_pos].site[site].condition[1].find(attr);
		if (pos >= 0)
		//然后和水平分片一样判断是否有交集
		{	//分片条件有这个属性
			if (sch.table[sch_pos].site[site].condition[0].find(attr) >= 0)
			{	cout << "判断是否香蕉" << endl;
				bool flag = true;
				for (int i = 1;i <= sch.table[sch_pos].site[site].hcon_list_len;i++)
				{	//因为只有AND，所以查询条件只有一个，然后查询条件的区间要与每个属性相同的分片条件都要有结果
					if (attr.compare(sch.table[sch_pos].site[site].hcon_list[i].attr) == 0)
					{	//属性相同，看是否相交
						cout << "compare " << op << " " << section << " " << sch.table[sch_pos].site[site].hcon_list[i].op << " " << sch.table[sch_pos].site[site].hcon_list[i].section << endl;
						if (!intersect(op, section, sch.table[sch_pos].site[site].hcon_list[i])) flag = false;
					}
				}
				return flag;
			}
			//否则可能存在结果
			else return true;
		}
		else return false;
	}
	return true;
}
//将node这个节点复制到tree[x]的父节点处，同时更新指针
void copy_node(query_tree &tree, int x, treenode &node)
{	tree.node[++tree.num] = node;
	int child_pos;
	for (int i = 1;i <= tree.node[tree.node[x].fa].child[0];i++)
	{	if (tree.node[tree.node[x].fa].child[i] == x) child_pos = i;
	}
	//更新指针
	tree.node[tree.num].fa = tree.node[x].fa;
	tree.node[tree.node[x].fa].child[child_pos] = tree.num;
	tree.node[tree.num].child[0] = 1;
	tree.node[tree.num].child[1] = x;
	tree.node[x].fa = tree.num;
}
//删除树中的一个节点，同时更新指针
void delete_node(query_tree &tree, int x)
{	int child_pos;
	for (int i = 1;i <= tree.node[tree.node[x].fa].child[0];i++)
	{	if (tree.node[tree.node[x].fa].child[i] == x) child_pos = i;
	}
	//更新父节点的儿子列表
	for (int i = child_pos; i < tree.node[tree.node[x].fa].child[0]; i++)
	{	tree.node[tree.node[x].fa].child[i] = tree.node[tree.node[x].fa].child[i + 1];
	}
	tree.node[tree.node[x].fa].child[0]--;
	//如果这个节点有儿子，则只能有一个儿子，否则这个节点不能删除
	if (tree.node[x].child[0] == 1)
	{	tree.node[tree.node[x].fa].child[++tree.node[tree.node[x].fa].child[0]] = tree.node[x].child[1];
		tree.node[tree.node[x].child[1]].fa = tree.node[x].fa;
	}
	//删掉这个节点
	tree.node[x].type = -1;
}

void push_condition_down(query_tree &tree)
{	//查询条件下推
	int en = tree.num;
	//分片列表
	int q[maxtreenode], r = 0;
	for (int i = 1;i <= en;i++)
	{	if (tree.node[i].type == 0)
		{	q[++r] = i;
		}
	}
	for (int i = 1;i <= en;i++)
	{	if (tree.node[i].type == 3) //遇到条件就下推
		{	//判断是否要插入到分片上
			for (int j = 1;j <= r;j++)
			{	//判断查询条件的属性，分片是否拥有
				if (q[j] == -1) continue;
				cout << tree.node[i].str << " " << tree.node[q[j]].str << endl;
				if (match_condition_frag(tree.node[i].str, tree.node[q[j]], tree))
				{	//垂直分片或者不分片有这个属性其实就可以直接插入了
					if (tree.node[i].type == 1 || tree.node[i].type == -1)
					{	cout << tree.node[i].str << " 插入 " << tree.node[q[j]].str << endl;
						copy_node(tree, q[j], tree.node[i]);
					}
					//否则在有这个属性的情况下，查询条件在这个分片上是否有结果，也就是查询条件是否与分片条件有交集
					else
					{	if (condition_intersect(tree.node[i].str, tree.node[q[j]], tree))
						{	cout << "条件与分片匹配，插入" << endl;
							copy_node(tree, q[j], tree.node[i]);
						}
						else
						{	cout << "条件与分片不匹配，删除这一枝" << endl;
							int to_del = q[j];
							//自底向上一直删到union
							while (tree.node[to_del].type != 1)
							{	delete_node(tree, to_del);
								to_del = tree.node[to_del].fa;
							}
							q[j] = -1;
							//如果删的union只有一个儿子了，把union也删了
							if (tree.node[to_del].child[0] == 1) delete_node(tree, to_del);
						}
					}
				}
				//没有就什么都不做
				else
				{	cout << "什么都不做" << endl;
				}
			}
			//推完将这个查询条件删除
			delete_node(tree, i);
		}
	}

}

//上退下移操作，基础优化
void get_basic_opt_tree(query_tree &tree)
{	//第一步，将条件下推
	push_condition_down(tree);
	//第二步，将投影操作下推

	//第三步，将连接操作下推

	
}
