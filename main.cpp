#include <string>
#include <iostream>
#include <fstream>
#include "query_tree.h"

using namespace std;

int main()
{
	string input = "select customer_id,quantity from orders where (quantity<8)";
	init_schema();
	query_tree original_tree = get_original_tree(input);
	cout << "original tree build complete\n";
	get_basic_opt_tree(original_tree, 3);//使用前3种优化
	cout << "basic optimize tree complete\n";
	print_tree(original_tree);
	system("pause");
	return 0;
}