#include "NodeAndTrie.h"
#include "Command.h"

int main(){
	system("color 0A");
	cout << "���������ȶ���ɢ��ǩ���������ϵͳ(Tags Store and Retrieve System for Stable Diffusion)\n"
	     << "Copyleft (c) OLEAM 2024-" << "-All left reserved.\n\n"
		 << "==============================================================\n\n"
		 << "  ��ӭʹ�ñ�Tag����ϵͳ.��ϵͳ��OLEAM��˾�ṩ.ף����ͼ���.  \n\n"
		 << "==============================================================\n";
	cout << "���Ե�,���ڹ����ֵ�" << endl;
	
	try {
		readMultiDict(pathToFile, mainTrie);
	}
	catch (runtime_error &exception) {
		cerr << exception.what() << endl;
		return 1;
	}
	cout << "�ֵ乹�����,���������Կ�ʼʹ��.�����Ҫ����ָ��,��ʹ��helpָ��." << endl
		 << "�˴�,\"ʹ��ָ��\"ָ��������ָ���ı���Enter��" << endl;
	
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