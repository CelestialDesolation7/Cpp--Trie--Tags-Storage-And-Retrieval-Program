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
//指令基类

class deleteCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	deleteCmd(string contentIn):command(contentIn){}
};
//删除内容指令

class addCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	addCmd(string contentIn):command(contentIn){}
};
//增加词汇指令

class recordCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	recordCmd(string contentIn):command(contentIn){}
};
//词汇加入收藏夹指令

class showFavoriateCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	showFavoriateCmd(string contentIn):command(contentIn){}
};
//显示收藏夹指令

class clearFavoriateCmd :public showFavoriateCmd {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	clearFavoriateCmd(string contentIn):showFavoriateCmd(contentIn){}
};
//清空收藏夹指令(showHistoryCmd的子类)

class clearScreenCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	clearScreenCmd(string contentIn):command(contentIn){}
};
//清空对话面板指令

class helpCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	helpCmd(string contentIn):command(contentIn){}
};
//显示帮助信息指令

class wildcardCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	wildcardCmd(string contentIn):command(contentIn){}
};
//显示通配符指令

class searchCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	searchCmd(string contentIn):command(contentIn){}
};
//搜索指令

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
//放弃保存指令

class confirmCmd :public command {
public:
	void execute()override;
	static string operationClass;
	string readClass() { return operationClass; }

	confirmCmd(string contentIn) :command(contentIn) {}
};
//确认指令

class 

command* analyseCommand(string userCommand);
bool operationEqual(string str1, string str2);
static bool charEqual(char c1, char c2);

string command::operationClass = "command";
string helpCmd::operationClass = "help";
string deleteCmd::operationClass = "delete";
string addCmd::operationClass = "add";
string recordCmd::operationClass = "record";
string showFavoriateCmd::operationClass = "showFavoriate";
string clearFavoriateCmd::operationClass = "clearFavoriate";
string wildcardCmd::operationClass = "wildcard";
string searchCmd::operationClass = "search";
string saveCmd::operationClass = "save";
string quitCmd::operationClass = "quit";
string confirmCmd::operationClass = "confirm";
