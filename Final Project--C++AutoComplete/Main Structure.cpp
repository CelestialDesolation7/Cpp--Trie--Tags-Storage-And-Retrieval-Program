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
		std::cerr << "无法打开文件,请检查dictionary.txt是否与本exe文件位于同一目录后重启程序." << endl;
		return 1;
	}
	cout << "请稍等,正在构建字典" << endl;
	readDictionary(dictionary, mainTrie);
	cout << "字典构建完成,请输入您要搜索的内容.";
}