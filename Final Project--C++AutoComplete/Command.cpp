#include "Command.h"
#include "NodeAndTrie.h"


static bool charEqual(char c1, char c2) {
	return tolower(c1) == tolower(c2);
}
//大小写不敏感的字符相等判断

bool operationEqual(string str1, string str2)
{
	if (str1.empty())return false;
	auto stringToLower = [](string& str) {
		for (char& c : str) {c = tolower(c);}
	};
	stringToLower(str1);
	stringToLower(str2);
	if(str1==str2)
		return true;
	commandTrie.layerSearch(str1,0,cmdSearchRes);
	bool includeTarget = false;
	includeTarget = (find(cmdSearchRes.begin(), cmdSearchRes.end(), str2) != cmdSearchRes.end());
	if (cmdSearchRes.size() >= 1 && includeTarget) {
		cmdSearchRes.clear();
		return true; }
	else { 
		cmdSearchRes.clear();
		return false; }
}
//大小写不敏感的字符串相等判断
//尝试使用了Lambda表达式
//注意:此比较函数具有歧义环境倾向性

string operationGuess(string partialCmd) {
	string notfound;
	auto stringToLower = [](string& str) {
		for (char& c : str) { c = tolower(c); }
		};
	stringToLower(partialCmd);
	for (string temp : allCommand) {
		if (partialCmd == temp)return temp;
	}//如果用户输入完整指令则直接将其返回
	commandTrie.layerSearch(partialCmd, 0, cmdSearchRes);
	if (cmdSearchRes.size() == 0)
		return notfound;
	//如果没有查找到指令则返回空字符串
	if (cmdSearchRes.size() == 1)
		return cmdSearchRes[0];
	//查找到一个则返回猜测结果
	return "ambiguity";
	//上述两种情况不适用,则有多个匹配结果,返回歧义处理指令
}
//不完整指令自动补全函数
//具有歧义环境中立性

command* stringToCmd(string fullCmd,string content)
{
	if (fullCmd.empty())
		return nullptr;
	else if (fullCmd == "add")
		return new addCmd(content);
	else if (fullCmd == "clear")
		return new clearCmd(content);
	else if (fullCmd == "confirm")
		return new confirmCmd(content);
	else if (fullCmd == "count")
		return new countCmd(content);
	else if (fullCmd == "delete")
		return new deleteCmd(content);
	else if (fullCmd == "favoriate")
		return new favoriateCmd(content);
	else if (fullCmd == "help")
		return new helpCmd(content);
	else if (fullCmd == "quit")
		return new quitCmd(content);
	else if (fullCmd == "save")
		return new saveCmd(content);
	else if (fullCmd == "search")
		return new searchCmd(content);
	else if (fullCmd == "select")
		return new selectCmd(content);
	else if (fullCmd == "switch")
		return new switchCmd(content);
	else
		return nullptr;
}
//指令标识符向指令实例映射器
//内存泄露警告:任何调用该映射器的函数均需要做内存初始化处理

commandPair lexicalAnalyser(string commandIn){
	string operation;
	string content;
	istringstream temp(commandIn);
	temp >> operation;
	getline(temp>>ws, content);
	return commandPair(operation,content);
}
//将指令和内容分离并返回指令内容二元组的简单词法分析器

command* analyseCommand(string userCommand)
{
	string operation;
	string content;
	istringstream temp(userCommand);
	temp >> operation;
	getline(temp>>ws, content);
	operation = operationGuess(operation);
	cmdSearchRes.clear();
	return stringToCmd(operation, content);
}
//面向用户输入信息的指令词法分析器
//内存泄露警告:任何调用该映射器的函数均需要做内存初始化处理
//具有歧义环境中立性

bool askConfirm() {
	string ifConfirm;
	getline(cin, ifConfirm);
	auto temp = lexicalAnalyser(ifConfirm);
	if (operationEqual(temp.first, "confirm") && temp.second.empty())
		return true;
	else
		return false;
}
//解析confirm指令的函数.由于很多指令需要confirm确认故对其进行进一步封装化
//具有歧义环境倾向性

bool sendSubCommand(string expectedCmd, bool executive) {
	string userCommand;
	getline(cin, userCommand);
	auto temp = lexicalAnalyser(userCommand);

	if (operationEqual(temp.first, expectedCmd)) {
		if (executive) {
			auto cmdTemp = stringToCmd(expectedCmd, temp.second);
			cmdTemp->execute();
			delete cmdTemp;
		}
		return false;
	}
	else {
		haveCmdPassedIn = true;
		cmdPassedIn = userCommand;
		return true;
	}
}
//软判定指令转发器
//决定将用户输入的指令作为状态指令的后向分支指令处理,还是前向传递至底层解析器处理
//具有歧义环境倾向性

bool sendSubCommand(bool strict, string expectedCmd, bool executive) {
	string userCommand;
	getline(cin, userCommand);
	auto temp = analyseCommand(userCommand);
	if (temp->operationClass == expectedCmd) {
		if (executive)temp->execute();
		delete temp;
		return false;
	}
	haveCmdPassedIn = true;
	cmdPassedIn = userCommand;
	delete temp;
	return true;
}
//硬判定指令转发器
//具有歧义环境中立性

//////////////////////////////////////////////////////////////
//指令实现函数////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void deleteCmd::execute()
{
	if (this->content.empty())
	{
		cout << "您没有输入想要删除的Tag.请重试.\n";
	}
	else {
		cout << "您确定要删除 " << this->content << " 这个词吗?您随后仍然可以在退出程序时放弃更改.\n"
			 << "如果确定,请使用confirm指令," << "否则输入任何其他内容.\n";
		if (askConfirm())
		{
			innerDeleteWord(this->content, mainTrie);
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
		int chineseIndex = 0;
		bool havetrans = 0;
		string tag, trans;
		for (auto contentElement : this->content) {
			if (isalpha(contentElement) || isspace(contentElement))
				chineseIndex++;
			else break;
		}
		if (chineseIndex == 0)
			cout << "您仅输入了中文没有输入英文,或者将中英文的顺序写反了,请重试.\n";
		else {
			tag = this->content.substr(0, chineseIndex);
			havetrans = (!chineseIndex == this->content.size()-1);
			//如果第一个非英文字符索引不是字符串末尾位置索引
			if(!havetrans)
			trans = this->content.substr(chineseIndex);
		}
		cout << "您确定要添加 " << tag;

		if(havetrans)
			cout << " (" << trans << ") ";
		else cout << " (没有给出翻译) ";

		cout << " 这个词吗?\n您随后仍然可以在退出程序时放弃更改.\n"
			 << "如果确定,请使用confirm指令," << "否则输入任何其他内容.\n";

		if (askConfirm())
		{
			innerAddWord(tag, trans, mainTrie);
			cout << "添加已成功.当前共有 " << mainTrie.count << " 个词汇\n";
		}
		else { cout << "已放弃添加.\n"; }
	}
}
//添加指令已完成

void switchCmd::execute()
{
	if (autoClear == false)autoClear = true;
	else autoClear = false;
}
//切换模式指令已完成

void favoriateCmd::execute(){
	if (favoriateList.empty())
	{
		cout << "您的收藏夹中没有内容." << endl;
		return;
	}
	cout << "                 收藏夹\n"
		<< "==========================================\n";
	int seqNumber = 1;
	for (string s : searchResult) {
		cout << "第" << seqNumber << "个" << "      " << s
			<< "      " << showTrans(s) << endl;
		seqNumber++;
	}
	cout << "==========================================\n";
	cout << "此处使用clear指令可以清空收藏夹,使用其他任何指令继续.\n";
	if (!sendSubCommand(true, "clear", false)) {
		favoriateList.clear();
		cout << "收藏夹已经清空.\n";
		return;
	}
	return;
}
//收藏夹展示指令已完成

void clearCmd::execute()
{
	system("cls");
}
//手动清空对话记录指令已完成

void helpCmd::execute()
{
	cout << "=======================================================================\n"
		 << "                              指令列表                            \n"
		 << "search-----查找包含关键词的Tag       delete----删除输入的Tag		 \n"
		 << "add--------增加一个新词汇            select-----选择搜索结果加入收藏夹\n"
		 << "switch----切换清理窗口信息清理模式   help------查看指令列表         \n"
		 << "favoriate--展示收藏夹                clear-----清空对话记录或收藏夹\n"
		 << "save-------保存对词库的修改          quit------退出程序\n"
		 << "confirm----确认指令                  count-----查看当前词汇总数\n"
		 << "=======================================================================\n"
		 << "                              使用说明                            \n"
		 << "  前四个指令均需要输入由您指定的内容,例如搜索的关键词,要删除的是什么.\n"
		 << "其余指令均不需要在指令名称后输入内容,即使您输入了内容也不会产生作用.\n"
		 << "您可以输入不完整的指令,如\"con\",程序会自动识别为confirm.但是需要注意\n"
		 << "当输入前缀(如\"c\")与多个指令匹配时程序无法猜中您的意思,您需要重新输入\n"
		 << "指令和您指定的内容之间以空格分割,一个就好,但是更多空格程序也能正常识别\n"
		 << "该程序当前尚不支持您一次输入多个关键词,或通配符的使用.\n\n"
		 << "  在需要插入tag时,您可以选择性地给出对应的中文翻译.search,tag和中文之间\n"
		 << "以空格分隔,例如\"add apple 苹果\".您的英文tag本身可以包含空格,程序能够\n"
		 << "正确识别哪些是Tag哪些是中文翻译.您也可以不给出中文翻译.\n\n"
		 << "  switch指令的使用会使得对话历史信息在每次输入新指令时自动被清除.重复使\n"
		 << "用该指令会使得程序在自动清除模式与非自动清除模式间来回切换.\n\n"
		 << "  当程序正在展示收藏夹时使用clear指令后确认可以清空收藏夹.\n\n"
		 << "  由于存储中文需要使用宽字符类型wchar_t,原有程序不能与其兼容,需要编写一\n"
		 << "专门用于处理中文的字典,工作量太多,故程序当前尚不支持中文搜索.\n"
		 << "=======================================================================\n";
}
//帮助指令已完成

void selectCmd::execute()
{
	int selected = 0;
	if (resMaximumSeqNumber == 1) {
		string selectedOne = searchResult[0];
		favoriateList.push_back(selectedOne);
		cout << "选择的词汇 " << selectedOne << " (" << showTrans(selectedOne) << ") "
			<< "已被加入收藏夹.\n";
		return;
	}
	if (this->content.empty()) {
	  cout << "没有输入要选择的结果编号,指令无效." << endl;
	  return; 
	}
	for (char c : this->content) {
		if (!isdigit(c))
		{cout << "非法输入.请输入正整数" << endl;return;}
	}
	istringstream iss(this->content);
	iss >> selected;
	if (selected <= resMaximumSeqNumber)
	{
		string selectedOne = searchResult[selected - 1];
		favoriateList.push_back(selectedOne);
		cout << "选择的词汇 " << selectedOne << " (" << showTrans(selectedOne) << ") "
			 << "已被加入收藏夹.\n";
		return;
	}
	else { cout << "无效的数字,没有匹配的结果." << endl; return; }
}
//选择收藏指令已完成

void searchCmd::execute()
{
	resMaximumSeqNumber = 0;
	resMinimumSeqNumber = 1;
	searchResult.clear();
	if (content.empty()) {
		cout << "您没有输入要搜索的关键词.请重试.\n";
		return;
	}
	mainTrie.deepSearch(this->content);
	showResult();
}
//搜索指令已完成

void saveCmd::execute()
{
	cout << "正在进行保存..." << endl;
	filesystem::path dictRepository(pathToFile);
	if (!checkDictCount(pathToFile)) {
		for (auto& entry : filesystem::directory_iterator(dictRepository)) {
			if (entry.path().extension() == stdextension)
				remove(entry.path());
		}
	}
	saveChange();
	cout << "保存已完成.\n";
}
//保存指令已完成

void quitCmd::execute()
{
	if (changeRecord.empty()) {
		cout << "程序已经终止运行.感谢您的使用.\n";
		Sleep(1500);
		askToQuit = true;
		return;
	}
		cout << "您还有尚未保存的更改,内容如下:\n"
		<< "=======================================================================\n";
		showChange();
		cout << "=======================================================================\n"
			<< "是否要放弃这些更改?如果是,使用confirm指令.否则请使用save指令.\n"
			<< "如果想要继续操作而不退出,请输入任意其他内容.\n";
		if (!sendSubCommand("confirm")) {
			askToQuit = true; return;
		}
		if (!sendSubCommand("save")) {
			askToQuit = true; return;
		}
		else return;
}
//退出函数已完成

void confirmCmd::execute(){
	return;
}
//确定指令已完成

void countCmd::execute() {
	cout << "当前一共存储了 " << mainTrie.count << " 个词汇." << endl;
}
//查看总数指令已完成

void ambiguityCmd::execute() {
	cout << "输入指令有歧义,您的输入可能代表以下指令:\n";
	for (string temp : cmdSearchRes) {
		cout << temp << endl;
	}
	cmdSearchRes.clear();
	cout << "请重新输入.\n";
}
//歧义处理指令已完成