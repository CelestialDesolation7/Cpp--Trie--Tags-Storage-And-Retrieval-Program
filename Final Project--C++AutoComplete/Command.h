#pragma once
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>

using namespace std;
using commandPair = pair<string, string>;

class command {
public:
	virtual void execute() = 0;
	string content;
	static string operationClass;
	virtual string readClass() { return operationClass; }

	command(string contentIn):content(contentIn){}
};
//ָ�����//

class deleteCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	deleteCmd(string contentIn):command(contentIn){}
};
//ɾ������ָ��//

class addCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	addCmd(string contentIn):command(contentIn){}
};
//���Ӵʻ�ָ��//

class switchCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	switchCmd(string contentIn):command(contentIn){}
};
//�л��Զ����ģʽָ��//

class favoriateCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	favoriateCmd(string contentIn):command(contentIn){}
};
//��ʾ�ղؼ�ָ��//

class clearCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	clearCmd(string contentIn):command(contentIn){}
};
//��նԻ����ָ��//

class helpCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	helpCmd(string contentIn):command(contentIn){}
};
//��ʾ������Ϣָ��//

class selectCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	selectCmd(string contentIn):command(contentIn){}
};
//�ʻ�����ղؼ�ָ��//

class searchCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	searchCmd(string contentIn):command(contentIn){}
};
//����ָ��//

class saveCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	saveCmd(string contentIn):command(contentIn){}
};
//����ָ��

class quitCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	quitCmd(string contentIn):command(contentIn){}
};
//�˳�����ָ��//

class confirmCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	confirmCmd(string contentIn) :command(contentIn) {}
};
//ȷ��ָ��//

class countCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	countCmd(string contentIn) :command(contentIn) {}
};
//�鿴����ָ��//

class ambiguityCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	ambiguityCmd(string contentIn) :command(contentIn) {}
};
//���崦��ָ��,�������û�//

command* analyseCommand(string userCommand);
static bool charEqual(char c1, char c2);
string operationGuess(string partialCmd);
command* stringToCmd(string fullCmd,string content);
commandPair lexicalAnalyser(string commandIn);
bool sendSubCommand(bool strict,string expectedCmd, bool executive = true);
bool sendSubCommand(string expectedCmd,bool executed = true);