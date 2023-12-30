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
//指令基类//

class deleteCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	deleteCmd(string contentIn):command(contentIn){}
};
//删除内容指令//

class addCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	addCmd(string contentIn):command(contentIn){}
};
//增加词汇指令//

class switchCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	switchCmd(string contentIn):command(contentIn){}
};
//切换自动清除模式指令//

class favoriateCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	favoriateCmd(string contentIn):command(contentIn){}
};
//显示收藏夹指令//

class clearCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	clearCmd(string contentIn):command(contentIn){}
};
//清空对话面板指令//

class helpCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	helpCmd(string contentIn):command(contentIn){}
};
//显示帮助信息指令//

class selectCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	selectCmd(string contentIn):command(contentIn){}
};
//词汇加入收藏夹指令//

class searchCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	searchCmd(string contentIn):command(contentIn){}
};
//搜索指令//

class saveCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	saveCmd(string contentIn):command(contentIn){}
};
//保存指令

class quitCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	quitCmd(string contentIn):command(contentIn){}
};
//退出程序指令//

class confirmCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	confirmCmd(string contentIn) :command(contentIn) {}
};
//确认指令//

class countCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	countCmd(string contentIn) :command(contentIn) {}
};
//查看总数指令//

class ambiguityCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	ambiguityCmd(string contentIn) :command(contentIn) {}
};
//歧义处理指令,不面向用户//

command* analyseCommand(string userCommand);
static bool charEqual(char c1, char c2);
string operationGuess(string partialCmd);
command* stringToCmd(string fullCmd,string content);
commandPair lexicalAnalyser(string commandIn);
bool sendSubCommand(bool strict,string expectedCmd, bool executive = true);
bool sendSubCommand(string expectedCmd,bool executed = true);