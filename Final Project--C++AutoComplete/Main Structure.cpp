#include "NodeAndTrie.h"
#include "Command.h"
#include <cstdlib>

int main(){
	system("color 0A");
	cout << "正在启动稳定扩散标签保存与查找系统(Tags Storage and Retrieval System for Stable Diffusion)\n"
		<< "Copyleft (c) OLEAM 2024-" << "-All left reserved.\n\n"
		<< "=======================================================================\n\n"
		<< "       欢迎使用本Tag建议系统.本系统由OLEAM公司提供.祝您跑图愉快.       \n\n"
		<< "=======================================================================\n";
	cout << "请稍等,正在构建字典" << endl;
	
	
	try { readMultiDict(pathToFile, mainTrie); }
	catch (runtime_error& exception) {
		cerr << exception.what() << endl;
		return 1;
	}

	for (auto& temp : allCommand)
		commandTrie.insert(temp);
	cout << "字典构建完成,现在您可以开始使用.如果需要操作指导,请使用help指令." << endl
		 << "此处,\"使用指令\"指的是输入指令文本后按Enter键" << endl;
	
	string userCommand;
	while (true) {
		if (haveCmdPassedIn) {
			userCommand = cmdPassedIn;
			cmdPassedIn.clear();
			haveCmdPassedIn = false;
			//如果有上级传入指令则跳过从用户接收指令的步骤
		}
		else getline(cin, userCommand);

		auto analysed = analyseCommand(userCommand);
		if (autoClear)system("cls");
		if (analysed != nullptr) {
				analysed->execute();
				userCommand.clear();
				delete analysed;
		}
		else { cout << "未知的指令.请检查是否输入错误.\n"; }
		if (askToQuit)return 0;
	}
	return 0;
}