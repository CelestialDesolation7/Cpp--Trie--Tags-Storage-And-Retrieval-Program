#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <map>
#include <utility>

using namespace std;

class node {
private:
	char nodeContent; //内容
	bool isEndOfWord; //结尾标记
	int childCount; //子节点数
	//string translation; //中文翻译
public:
	int layer; //层数
	map<char, node*> next; //子节点表
	char readContent();
	node* parent;

	node();
	node(char inputContent, bool isEnd, int layerIn,node* parentNode);
	node* findChild(char c);
	node* whereKey(char key); 
	//功能模块化思想:单独设计一个判断是否有所需子节点的函数
	void markEnd();
	//为了insert标记结尾节点而设计
	void layerClassify();
	//根据layer值对node进行分组

};

class trie {
private:
	node root;
	int count;//词汇数
public:
	int insert(string wordIn);
	void remove(string Deleted);
	static int maxLayer;

	node* baseSearch(string keyword,node* rootIn);
	void layerSearch(string keyword,int layerIn);
	node* deepSearch(string keyword);
	string readResult(node* edge);

	trie();

};

using layerGroup = vector<node*>;
using groupCatalog = map<int, layerGroup>;
using catalogEle = pair<int, layerGroup>;

vector<string> searchResult;

groupCatalog enCatalog;

void showResult();

//test Github