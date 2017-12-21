#include <string>
#include <iostream>
#include <fstream>
#include "query_tree.h"

using namespace std;

int main()
{
	string input = "select * from emp,job,sal,asg where (emp.title=sal.title) and (emp.eno=asg.eno) and (job.jno=asg.jno) and (eno<'E0010') and (jno<'J0500')";
	init_schema();
	query_tree original_tree = get_original_tree(input);
	//get_basic_opt_tree(original_tree);
	//cout << original_tree.num << endl;
	//cout << table_pos["job"] << endl;
	cout << "original tree build complete\n";
	print_tree(original_tree);
	system("pause");
	return 0;
}