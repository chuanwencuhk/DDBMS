#ifndef QUERY_TREE_H
#define QUERY_TREE_H
#include <string>
#include <map>
using namespace std;
#define maxsite 100+1
#define maxcol 10
#define maxtreenode 1000
#define max_table_num 10

struct condition_info
{	string attr;
	string op;
	string section;
};

struct fragment
{
	string condition[2];//水平分片条件放在0，垂直分片条件放在1,这个是所有条件拼成的字符串
	int hcon_list_len;
	condition_info hcon_list[10];//水平分片的条件的列表存放在这里，方便处理
};

struct schema_node
{
	string table_name;
	int type;//0--horizontal 1--vertical 2--hybrid -1--no fragment
	int col_num;//列的数量
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
	int type;//0是分片 1是union 2是join 3是根据condition选择元组 4是投影取属性 -1表示这个节点已删除
	string str;//树节点的内容
	int child[maxsite];//儿子节点指针，没有则为-1,child[0]表示儿子数
	int fa;//父节点指针
	int depth;
};
struct query_tree
{
	int table_num;//总共有多少个表
	map<string, int> schema_pos;//保存数据字典中表的位置
	map<string, int> table_pos;//保存树的数组中表的位置
	treenode node[maxtreenode];
	int root = -1;//根节点
	int num = 0;//当前节点数
};

void init_schema();
//求最大值
int maxint(int a, int b);
double max(double a, double b);
//判断一个字符串是否为变量
bool isVar(string s);
//确定表名为s的表在树种的位置
int loc(string s, query_tree &o_tree);
//将表插入树中
void insert_table_list(string table_list, query_tree &o_tree);
//找到tree[i]的祖先
int get_fa(query_tree &tree, int i);
//把查询条件插入到树中
void insert_condition(string condition_list, query_tree &o_tree);
//把schema中表的位置信息，放到树中
void insert_schema(query_tree &o_tree, schema &sch);
//获取带有分片信息的最原始的查询树
query_tree get_original_tree(string s);
//输出树到文件
void print_tree(query_tree tree);
//上退下移操作，基础优化
void get_basic_opt_tree(query_tree &tree, int level);
#endif
