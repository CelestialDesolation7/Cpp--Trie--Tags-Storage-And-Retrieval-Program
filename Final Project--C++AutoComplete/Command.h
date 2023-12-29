#pragma once
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class command {
public:
	virtual void execute() = 0;
	string content;
	static string operationClass;
	virtual string readClass() { return operationClass; }

	command(string contentIn):content(contentIn){}
};
//ָ�����

class deleteCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	deleteCmd(string contentIn):command(contentIn){}
};
//ɾ������ָ��

class addCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	addCmd(string contentIn):command(contentIn){}
};
//���Ӵʻ�ָ��

class recordCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	recordCmd(string contentIn):command(contentIn){}
};
//�ʻ�����ղؼ�ָ��

class showFavoriateCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	showFavoriateCmd(string contentIn):command(contentIn){}
};
//��ʾ�ղؼ�ָ��

class clearFavoriateCmd :public showFavoriateCmd {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	clearFavoriateCmd(string contentIn):showFavoriateCmd(contentIn){}
};
//����ղؼ�ָ��(showHistoryCmd������)

class clearScreenCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	clearScreenCmd(string contentIn):command(contentIn){}
};
//��նԻ����ָ��

class helpCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	helpCmd(string contentIn):command(contentIn){}
};
//��ʾ������Ϣָ��

class wildcardCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	wildcardCmd(string contentIn):command(contentIn){}
};
//��ʾͨ���ָ��

class searchCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	searchCmd(string contentIn):command(contentIn){}
};
//����ָ��

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
//��������ָ��

class confirmCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	confirmCmd(string contentIn) :command(contentIn) {}
};
//ȷ��ָ��

command* analyseCommand(string userCommand);
bool operationEqual(string str1, string str2);
static bool charEqual(char c1, char c2);