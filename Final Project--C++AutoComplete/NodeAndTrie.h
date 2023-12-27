#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <map>
#include <utility>
#include <sstream>
#include <filesystem>

using namespace std;

class node {
private:
	char nodeContent; //内容
	bool isEndOfWord; //结尾标记
public:
	int layer; //层数
	map<char, node*> next; //子节点表
	char readContent()const;
	node* parent;
	int childCount; //子节点数

	node();
	node(char inputContent, bool isEnd, int layerIn,node* parentNode);
	node* findChild(char c);
	node* whereKey(char key); 
	//功能模块化思想:单独设计一个判断是否有所需子节点的函数
	void markEnd();
	//为了insert标记结尾节点而设计
	void layerClassify();
	//根据layer值对node进行分组
	void markNotEnd();
};

class trie {
private:
	node root;
	int count;//词汇数
public:
	int insert(string wordIn);
	bool remove(string Deleted);
	void userRemove(string keyword);
	static int maxLayer;

	node* baseSearch(string keyword,node* rootIn);
	void layerSearch(string keyword,int layerIn);
	void deepSearch(string keyword);
	string readResult(node* edge);

	trie();
};

/////////////////////////////////////////////////////
//类型别名///////////////////////////////////////////
/////////////////////////////////////////////////////

using layerGroup = vector<node*>;
using groupCatalog = map<int, layerGroup>;
using catalogEle = pair<int, layerGroup>;
using changeUnit = pair<string, string>;
using tagTransPair = pair<string, string>;

////////////////////////////////////////////////////////
//全局容器//////////////////////////////////////////////
////////////////////////////////////////////////////////

vector<string> searchResult;
map<string, string>tagAndTrans;
groupCatalog enCatalog;
vector<string> favoriateList;
vector<changeUnit> changeRecord;

/////////////////////////////////////////////////
//数据展示函数///////////////////////////////////
/////////////////////////////////////////////////

void showResult();
void addToFavoriate(string keyword);
void selectResult(int seqNumber);
void clearFavoriate();
void showFavoriate();
int resMinimumSeqNumber = 1;
int resMaximumSeqNumber = 0;
string showTrans(string tag);

///////////////////////////////////////////////////////
//字典读取与修改函数///////////////////////////////////
///////////////////////////////////////////////////////

void readDictionary(ifstream& dictionary, trie trie);
void saveChange();
void readMultiDict(string pathIn,trie trie);

//////////////////////////////////////////////////////////
//特殊名词定义////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define mainPath "dictionary.txt"
#define pathToFile "D:\Project\Final Project--C++AutoComplete\Final Project--C++AutoComplete\Dictionary"
#define stdextension ".txt"

//////////////////////////////////////////////////////////
//面向用户函数////////////////////////////////////////////
//////////////////////////////////////////////////////////

void userAddWord(string fullWord,string trans,trie trie);
void userDeleteWord(string toDelete,trie trie);

//////////////////////////////////////////////////////////
//异常定义////////////////////////////////////////////////
//////////////////////////////////////////////////////////
