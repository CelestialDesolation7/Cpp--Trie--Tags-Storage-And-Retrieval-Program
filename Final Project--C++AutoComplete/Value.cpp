#include "Command.h"
#include "NodeAndTrie.h"

string command::operationClass = "command";
string helpCmd::operationClass = "help";
string deleteCmd::operationClass = "delete";
string addCmd::operationClass = "add";
string switchCmd::operationClass = "switch";
string favoriateCmd::operationClass = "showFavoriate";
string selectCmd::operationClass = "select";
string searchCmd::operationClass = "search";
string saveCmd::operationClass = "save";
string quitCmd::operationClass = "quit";
string confirmCmd::operationClass = "confirm";
string clearCmd::operationClass = "clear";
string countCmd::operationClass = "count";
string ambiguityCmd::operationClass = "ambiquity";

vector<string> allCommand = {
"help" ,"delete" ,"add" ,
"switch" ,"favoriate" ,
"select" ,"search" ,"save" ,"quit" ,
"confirm" ,"clear" ,"count" };			//所有指令的列表

vector<string> searchResult;			//用于临时存储搜索结果用于展示
map<string, string>tagAndTrans;			//标签与翻译映射表
vector<string> favoriateList;			//收藏夹容器
vector<changeUnit> changeRecord;		//更改目录容器
int resMinimumSeqNumber = 1;		    //最小序列号,临时存储搜索结果编号
int resMaximumSeqNumber = 0;		    //最大序列号,临时存储搜索结果编号
vector<string> record;					//历史记录存储容器实例
trie mainTrie;							//英文Tag存储树
trie commandTrie;						//指令存储树
trie zhTransTrie;						//中文翻译存储树,由于char类型限制可能无法实现
bool autoClear = false;				    //是否处于自动清除模式
bool haveCmdPassedIn = false;		    //是否有被前向传递至底层的待处理指令
string cmdPassedIn;						//存储传入指令内容
bool askToQuit = false;				    //用户是否要求退出
vector<string> cmdSearchRes;			//存储搜索到的指令