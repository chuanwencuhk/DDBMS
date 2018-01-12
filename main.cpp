#include <string>
#include <iostream>
#include <fstream>
#include "query_tree.h"

using namespace std;

int main()
{
	string input = "select customer.name,book.title,publisher.name,orders.quantity from customer,book,publisher,orders where (customer.customer_id=orders.customer_id) and (book.book_id=orders.book_id) and (book.publisher_id=publisher.publisher_id) and (customer.customer_id>308000) and (book.copies>100) and (orders.quantity>1) and (publisher.nation='PRC')";
	init_schema();
	query_tree original_tree = get_original_tree(input);
	cout << "original tree build complete\n";
	get_basic_opt_tree(original_tree, 3);//使用前3种优化
	cout << "basic optimize tree complete\n";
	print_tree(original_tree);
	system("pause");
	return 0;
}