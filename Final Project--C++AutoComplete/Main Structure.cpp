#include "NodeAndTrie.h"
#include "History.h"
#include "Command.h"
#include <stdlib.h>

int main(){
	system("color 0A");
	cout << "���������ȶ���ɢ��ǩ���������ϵͳ(Tags Store and Retrieve System for Stable Diffusion)\n"
	     << "Copyleft (c) OLEAM 2024-" << "-All left reserved.\n\n"
		 << "==============================================================\n\n"
		 << "  ��ӭʹ�ñ�Tag����ϵͳ.��ϵͳ��OLEAM��˾�ṩ.ף����ͼ���.  \n\n"
		 << "==============================================================\n";
	cout << "���Ե�,���ڹ����ֵ�" << endl;
	
	ifstream dictionary(mainPath);

	if (!dictionary.is_open()) {
		std::cerr << "�޷����ļ�,�����ֵ��ļ��Ƿ��뱾exe�ļ�λ��ͬһĿ¼����������." << endl;
		return 1;
		cin.get();
	}
	readDictionary(dictionary, mainTrie);
	cout << "�ֵ乹�����,���������Կ�ʼʹ��.�����Ҫ����ָ��,��ʹ��helpָ��." << endl
		<< "�˴�,\"ʹ��ָ��\"ָ��������ָ���ı���Enter��" << endl;
	dictionary.close();
	string userCommand;
	while (true) {
		getline(cin, userCommand);
		auto analysed = analyseCommand(userCommand);
		if (analysed != nullptr) {
			analysed->execute();
			userCommand.clear();
			delete analysed;
		}
		else { cout << "δ֪��ָ��.�����Ƿ��������.\n"; }
	}
	return 0;
}