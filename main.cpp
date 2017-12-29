#include <string>
#include <iostream>
#include <fstream>
#include "query_tree.h"

using namespace std;

int main()
{
	string input = "select eno,jno,title,loc from emp,job,sal,asg where (emp.title=sal.title) and (emp.eno=asg.eno) and (job.jno=asg.jno) and (jno<='J0400') and (title<'N')";
	init_schema();
	query_tree original_tree = get_original_tree(input);
	cout << "original tree build complete\n";
	get_basic_opt_tree(original_tree, 3);//使用前3种优化
	cout << "basic optimize tree complete\n";
	print_tree(original_tree);
	system("pause");
	return 0;
}