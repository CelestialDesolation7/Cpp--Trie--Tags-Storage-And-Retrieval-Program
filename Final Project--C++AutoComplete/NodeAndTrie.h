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

using namespace std;

class node {
private:
	char nodeContent; //����
	bool isEndOfWord; //��β���
public:
	int layer; //����
	map<char, node*> next; //�ӽڵ��
	char readContent();
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
	int count;//�ʻ���
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

using layerGroup = vector<node*>;
using groupCatalog = map<int, layerGroup>;
using catalogEle = pair<int, layerGroup>;

vector<string> searchResult;
map<string, string>tagAndTrans;
groupCatalog enCatalog;

void showResult();
void addToFavoriate(string keyword);
void selectResult(int seqNumber);
void clearFavoriate();
void showFavoriate();
int resMinimumSeqNumber = 1;
int resMaximumSeqNumber = 0;

void readDictionary(ifstream& dictionary,trie trie);
bool addWord(string fullWork);
void userAddWord(string fullWord);
bool deleteWord(string toDelete);
void userDeleteWord(string toDelete);

bool findTrans(string tag);
void showTrans(string tag);

vector<string> favoriateList;
