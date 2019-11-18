#include<iostream>
#include "bintree.hpp"
using namespace std;

int main() {
	BinTree<char, int> bin;
	bin['c'] = 42;
	bin['a'] = 9054;
	bin['s'] = 57;
	bin['s'] = 87;
	bin['i'] = 90;
	bin['e'] = 54;

	bin.erase('e');
	bin.erase('i');

	for (auto &i : bin) {
		cout << i << ' ';
	}
	cout << endl;
}
