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
	string condition[2];//ˮƽ��Ƭ��������0����ֱ��Ƭ��������1,�������������ƴ�ɵ��ַ���
	int hcon_list_len;
	condition_info hcon_list[10];//ˮƽ��Ƭ���������б������������㴦��
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
	int type;//0�Ƿ�Ƭ 1��union 2��join 3�Ǹ���conditionѡ��Ԫ�� 4��ͶӰȡ���� -1��ʾ����ڵ���ɾ��
	string str;//���ڵ������
	int child[maxsite];//���ӽڵ�ָ�룬û����Ϊ-1,child[0]��ʾ������
	int fa;//���ڵ�ָ��
	int depth;
};
struct query_tree
{
	int table_num;//�ܹ��ж��ٸ���
	map<string, int> schema_pos;//���������ֵ��б���λ��
	map<string, int> table_pos;//�������������б���λ��
	treenode node[maxtreenode];
	int root = -1;//���ڵ�
	int num = 0;//��ǰ�ڵ���
};

void init_schema();
//�����ֵ
int maxint(int a, int b);
double max(double a, double b);
//�ж�һ���ַ����Ƿ�Ϊ����
bool isVar(string s);
//ȷ������Ϊs�ı������ֵ�λ��
int loc(string s, query_tree &o_tree);
//������������
void insert_table_list(string table_list, query_tree &o_tree);
//�ҵ�tree[i]������
int get_fa(query_tree &tree, int i);
//�Ѳ�ѯ�������뵽����
void insert_condition(string condition_list, query_tree &o_tree);
//��schema�б���λ����Ϣ���ŵ�����
void insert_schema(query_tree &o_tree, schema &sch);
//��ȡ���з�Ƭ��Ϣ����ԭʼ�Ĳ�ѯ��
query_tree get_original_tree(string s);
//��������ļ�
void print_tree(query_tree tree);
//�������Ʋ����������Ż�
void get_basic_opt_tree(query_tree &tree, int level);
#endif
