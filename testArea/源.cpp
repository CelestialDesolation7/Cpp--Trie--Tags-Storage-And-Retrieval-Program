#include <string>
#include <iostream>
using namespace std;

void clearSpaceSuffix(string& str)
{
	for (auto strIter = str.rbegin(); strIter != str.rend(); strIter++) {
		if (*strIter == ' ')str.erase(strIter.base() - 1);
		else return;
	}
}

int main() {
	string test = "���ǲ����ı�   ";
	cout << "aaaaa" << test << "aaaaa"<<endl;
	clearSpaceSuffix(test);
	cout << "aaaaa" << test << "aaaaa" << endl;
	return 0;
}