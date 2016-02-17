#include "../Connection.h"

#include <iostream>
#include <vector>

//
// NOTE: This tested a private member function and will no longer compile
// 	 with the current implementation.
//

using namespace std;

int main()
{
	Connection test_connection("12.12.12.12", 8888);
	vector<int> numbers = test_connection.parse_ip("255.255.255.255");
	for (int num : numbers) {
		cout << num << endl;
	}

	return 0;
}
