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
	char nodeContent; //����
	bool isEndOfWord; //��β���
	int childCount; //�ӽڵ���
	//string translation; //���ķ���
public:
	int layer; //����
	map<char, node*> next; //�ӽڵ��
	char readContent();
	node* parent;

	node();
	node(char inputContent, bool isEnd, int layerIn,node* parentNode);
	node* findChild(char c);
	node* whereKey(char key); 
	//����ģ�黯˼��:�������һ���ж��Ƿ��������ӽڵ�ĺ���
	void markEnd();
	//Ϊ��insert��ǽ�β�ڵ�����
	void layerClassify();
	//����layerֵ��node���з���

};

class trie {
private:
	node root;
	int count;//�ʻ���
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