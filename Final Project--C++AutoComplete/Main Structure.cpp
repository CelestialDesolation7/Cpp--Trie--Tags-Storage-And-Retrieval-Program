#include "NodeAndTrie.h"
#include "History.h"

int main(){
	cout << "Copyleft (c) megahard 2023" << endl << "All left reserved.\n";
	history record;
	trie mainTrie;
	ifstream dictionary(mainPath);

	if (!dictionary.is_open()) {
		std::cerr << "�޷����ļ�,����dictionary.txt�Ƿ��뱾exe�ļ�λ��ͬһĿ¼����������." << endl;
		return 1;
	}
	cout << "���Ե�,���ڹ����ֵ�" << endl;
	readDictionary(dictionary, mainTrie);
	cout << "�ֵ乹�����,��������Ҫ����������.";
	dictionary.close();
	
}