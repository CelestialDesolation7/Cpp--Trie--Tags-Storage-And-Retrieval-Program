#include "NodeAndTrie.h"
#include "History.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

int main(){
	cout << "Copyleft (c) megahard 2023" << endl << "All left reserved.\n";
	history record;
	trie mainTrie;
	ifstream dictionary("dictionary.txt");

	if (!dictionary.is_open()) {
		std::cerr << "�޷����ļ�,����dictionary.txt�Ƿ��뱾exe�ļ�λ��ͬһĿ¼����������." << endl;
		return 1;
	}
	cout << "���Ե�,���ڹ����ֵ�" << endl;
	readDictionary(dictionary, mainTrie);
	cout << "�ֵ乹�����,��������Ҫ����������.";
}