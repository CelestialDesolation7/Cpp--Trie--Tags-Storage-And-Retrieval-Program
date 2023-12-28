#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <utility>
#include <sstream>
#include <filesystem>
#include "History.h"

using namespace std;

class node {
private:
	char nodeContent; //����
	bool isEndOfWord; //��β���
public:
	int layer; //����
	map<char, node*> next; //�ӽڵ��
	char readContent()const;
	node* parent;
	int childCount; //�ӽڵ���

	node();
	node(char inputContent, bool isEnd, int layerIn,node* parentNode);
	node* findChild(char c);
	node* whereKey(char key); 
	//����ģ�黯˼��:�������һ���ж��Ƿ��������ӽڵ�ĺ���
	void markEnd();
	//Ϊ��insert��ǽ�β�ڵ�����
	void layerClassify();
	//����layerֵ��node���з���
	void markNotEnd();
};

class trie {
private:
	node root;
public:
	static int maxLayer;
	int count;//�ʻ���

	node* baseSearch(string keyword,node* rootIn);
	void layerSearch(string keyword,int layerIn);
	void deepSearch(string keyword);
	string readResult(node* edge);
	int insert(string wordIn);
	bool remove(string Deleted);
	void userRemove(string keyword);
	trie();
};

/////////////////////////////////////////////////////
//���ͱ���///////////////////////////////////////////
/////////////////////////////////////////////////////

using layerGroup = vector<node*>;
using groupCatalog = map<int, layerGroup>;
using catalogEle = pair<int, layerGroup>;
using changeUnit = pair<string, string>;
using tagTransPair = pair<string, string>;

////////////////////////////////////////////////////////
//ȫ������//////////////////////////////////////////////
////////////////////////////////////////////////////////

vector<string> searchResult;//������ʱ�洢�����������չʾ
map<string, string>tagAndTrans;
groupCatalog enCatalog;
vector<string> favoriateList;
vector<changeUnit> changeRecord;
history record;
trie mainTrie;
trie commandTrie;

/////////////////////////////////////////////////
//����չʾ����///////////////////////////////////
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
//�ֵ��ȡ���޸ĺ���///////////////////////////////////
///////////////////////////////////////////////////////

void readDictionary(ifstream& dictionary, trie trie);
void saveChange();
void readMultiDict(string pathIn,trie trie);

//////////////////////////////////////////////////////////
//�ļ�·������////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define mainPath "dictionary.txt"
#define pathToFile "D:\Project\Final Project--C++AutoComplete\Final Project--C++AutoComplete\Dictionary"
#define stdextension ".txt"

//////////////////////////////////////////////////////////
//�����û�����////////////////////////////////////////////
//////////////////////////////////////////////////////////

void userAddWord(string fullWord,string trans,trie trie);
void userDeleteWord(string toDelete,trie trie);

//////////////////////////////////////////////////////////
//�쳣����////////////////////////////////////////////////
//////////////////////////////////////////////////////////
