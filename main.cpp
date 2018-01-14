#include <string>
#include <iostream>
#include <fstream>
#include "query_tree.h"

using namespace std;

int main()
{
	string input = "select customer.name,orders.quantity,book.title from customer,orders,book where (book.book_id=orders.book_id) and (customer.customer_id=orders.customer_id) and (customer.rank=1) and (book.copies>5000)";
	init_schema();
	query_tree original_tree = get_original_tree(input);
	cout << "original tree build complete\n";
	get_basic_opt_tree(original_tree, 3);//使用前3种优化
	cout << "basic optimize tree complete\n";
	print_tree(original_tree);
	system("pause");
	return 0;
}