#include "Command.h"
#include "NodeAndTrie.h"

static bool charEqual(char c1, char c2) {
	return tolower(c1) == tolower(c2);
}

bool operationEqual(string str1, string str2)
{
	auto charEqual = [](char c1, char c2) {return tolower(c1) == tolower(c2); };
	return equal(str1.begin(),str1.end(),str2.begin(),charEqual);
}
//大小写不敏感的字符串相等判断
//尝试使用了Lambda表达式
//尚未完成不完全输入的匹配

command* analyseCommand(string userCommand)
{
	string operation;
	string content;
	istringstream temp(userCommand);
	temp >> operation;
	getline(temp, content);

	if(operation.empty())
		return nullptr;
	else if (operationEqual(operation,"help"))
		return new helpCmd(content); //展示帮助列表
	else if (operationEqual(operation, "delete"))
		return new deleteCmd(content); //删除指令
	else if (operationEqual(operation, "add"))
		return new addCmd(content);
	else if (operationEqual(operation, "record"))
		return new recordCmd(content);
	else if (operationEqual(operation, "favoriate"))
		return new showFavoriateCmd(content);
	else if (operationEqual(operation, "clear"))
		return new clearScreenCmd(content);
	else if (operationEqual(operation, "wildcard"))
		return new wildcardCmd(content);
	else if (operationEqual(operation, "search"))
		return new searchCmd(content);
	else if (operationEqual(operation, "save"))
		return new saveCmd(content);
	else if (operationEqual(operation, "quit"))
		return new quitCmd(content);
	else 
		return nullptr;
}

void clearFavoriateCmd::execute()
{
	favoriateList.clear();
	cout << "收藏夹已成功清空" << endl;
}
//清空收藏夹指令已完成

void deleteCmd::execute()
{
	if (this->content.empty())
	{
		cout << "您没有输入想要删除的Tag.请重试.\n";
	}
	else {
		cout << "您确定要删除 " << this->content << " 这个词吗?您随后仍然可以在退出程序时放弃更改.\n"
			 << "如果确定,请使用confirm指令," << "否则输入任何其他内容.\n";
		string ifConfirm;
		getline(cin, ifConfirm);
		command* temp = analyseCommand(ifConfirm);
		if (temp != nullptr && temp->readClass() != "confirm")
		{
			mainTrie.userRemove(this->content);
			cout << "删除已成功.当前剩余 " << mainTrie.count << " 个词汇\n";
		}
		else { cout << "已放弃删除.\n";}
	}
}
//删除指令已完成

void addCmd::execute()
{
	if (this->content.empty())
	{
		cout << "您没有输入想要添加的Tag.请重试.\n";
	}
	else {
		cout << "您确定要添加 " << this->content << " 这个词吗?您随后仍然可以在退出程序时放弃更改.\n"
			<< "如果确定,请使用confirm指令," << "否则输入任何其他内容.\n";
		string ifConfirm;
		getline(cin, ifConfirm);
		command* temp= analyseCommand(ifConfirm);
		if (temp!=nullptr && temp->readClass() != "confirm")
		{
			int countNow = mainTrie.insert(this->content);
			cout << "添加已成功.当前共有 " << countNow << " 个词汇\n";
		}
		else { cout << "已放弃添加.\n"; }
	}
}
//添加指令已完成

void recordCmd::execute()
{
}

void showFavoriateCmd::execute()
{
}

void clearScreenCmd::execute()
{

}

void helpCmd::execute()
{
	cout << "=====================================================================\n"
		 << "                              指令列表                            \n"
		 << "search-----查找包含关键词的Tag   delete----删除输入的Tag		 \n"
		 << "add--------增加一个新词汇        record----收藏编号对应的搜索结果\n"
		 << "clear------清空当前对话窗口      help------查看指令列表         \n"
		 << "favoriate--展示收藏夹            wildcard--查看通配符搜索介绍\n"
		 << "save-------保存对词库的修改      quit------退出程序\n"
		 << "confirm----确认指令              count-----查看当前词汇总数\n"
		 << "=====================================================================\n"
		 << "                              使用说明                            \n"
		 << "  前四个指令均需要输入由您指定的内容,例如搜索的关键词,要删除的是什么.\n"
		 << "其余指令均不需要在指令名称后输入内容,即使您输入了内容也不会产生作用.\n"
		 << "您可以输入不完整的指令,如\"con\",程序会自动识别为confirm.但是需要注意\n"
		 << "当输入前缀(如\"c\")与多个指令匹配时程序无法猜中您的意思,您需要重新输入\n"
		 << "指令和您指定的内容之间以空格分割,一个就好,但是更多空格程序也能正常识别\n"
		 << "该程序支持您一次输入多个关键词,也支持通配符的使用."
		 << "======================================================================\n";
}
//帮助指令

void wildcardCmd::execute()
{
}

void searchCmd::execute()
{
}

void saveCmd::execute()
{
}

void quitCmd::execute()
{
}

void confirmCmd::execute(){

}
