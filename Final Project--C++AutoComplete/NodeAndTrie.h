#pragma once
#include <map>
#include <utility>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

////////////////////////////////////////////////////////
//前向引用声明//////////////////////////////////////////
////////////////////////////////////////////////////////

class trie;
class node;

/////////////////////////////////////////////////////
//类型别名///////////////////////////////////////////
/////////////////////////////////////////////////////

using layerGroup = vector<node*>;
using changeUnit = pair<string, string>;
using tagTransPair = pair<string, string>;

////////////////////////////////////////////////////////
//全局容器//////////////////////////////////////////////
////////////////////////////////////////////////////////

extern vector<string> searchResult;    //用于临时存储搜索结果用于展示
extern map<string, string>tagAndTrans; //标签与翻译映射表
extern vector<string> favoriateList;   //收藏夹容器
extern vector<changeUnit> changeRecord;//更改目录容器
extern int resMinimumSeqNumber;		   //最小序列号,临时存储搜索结果编号
extern int resMaximumSeqNumber;		   //最大序列号,临时存储搜索结果编号
extern vector<string> record;		   //历史记录存储容器实例
extern trie mainTrie;				   //英文Tag存储树
extern trie commandTrie;			   //指令存储树
extern trie zhTransTrie;			   //中文翻译存储树,由于char类型限制可能无法实现
extern bool autoClear;				   //是否处于自动清除模式
extern bool haveCmdPassedIn;		   //是否有被前向传递至底层的待处理指令
extern string cmdPassedIn;			   //存储传入指令内容
extern bool askToQuit;				   //用户是否要求退出
extern vector<string> allCommand;	   //所有指令
extern vector<string> cmdSearchRes;	   //存储搜索到的指令

//////////////////////////////////////////////////////////
//节点类//////////////////////////////////////////////////
//////////////////////////////////////////////////////////

class node {
private:
	char nodeContent; //内容
public:
	int layer; //层数
	node* parent;
	map<char, node*> next; //子节点表
	bool isEndOfWord; //结尾标记
	vector<node*> allChild;

	//状态检定思想:建立处于对象操作环境中时的常时状态变化需求监测行为模式
	node();
	node(char inputContent, bool isEnd, int layerIn,node* parentNode);
	node* findChild(char c);
	node* whereKey(char key); 
	//功能模块化思想:单独设计一个判断是否有所需子节点的函数
	void markEnd();
	//为了insert标记结尾节点而设计
	void markNotEnd();
	int childCount; //子节点数
	char readContent()const;
};

//////////////////////////////////////////////////////////
//字典树类////////////////////////////////////////////////
//////////////////////////////////////////////////////////

class trie {
private:
	node root;
public:
	int maxLayer = 0;
	int count;//词汇数
	map<int, layerGroup> layerCatalog; //深度值到对应深度节点群映射的表

	vector<node*> baseSearch(string keyword,node* rootIn);
	void layerSearch(string keyword,int layerIn, vector<string>& searchResultIn = searchResult);
	void deepSearch(string keyword);
	string readResult(node* edge);
	int insert(string wordIn);
	bool remove(string Deleted);
	void trieRemove(string keyword);
	trie();
	void layerClassify(node* nodeIn);
	
	//根据layer值对node进行分组
};

/////////////////////////////////////////////////
//数据展示函数///////////////////////////////////
/////////////////////////////////////////////////

void showResult();
void addToFavoriate(string keyword);
string showTrans(string tag);

///////////////////////////////////////////////////////
//字典读取与修改函数///////////////////////////////////
///////////////////////////////////////////////////////

void readDictionary(ifstream& dictionary, trie& trie);
void saveChange();
void readMultiDict(string pathIn,trie& trie);
bool checkDictCount(string pathIn);

//////////////////////////////////////////////////////////
//文件路径定义////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define mainPath "dictionary\\dictionary.txt"
#define pathToFile "D:\\Project\\Final Project--C++AutoComplete\\Final Project--C++AutoComplete\\Dictionary"
#define stdextension ".txt"

//////////////////////////////////////////////////////////
//面向用户函数////////////////////////////////////////////
//////////////////////////////////////////////////////////

void innerAddWord(string fullWord,string trans,trie& trie);
void innerDeleteWord(string fullWord,trie& trie);
bool askConfirm();
void showChange();

//////////////////////////////////////////////////////////
//异常定义////////////////////////////////////////////////
//////////////////////////////////////////////////////////