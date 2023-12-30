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
//ǰ����������//////////////////////////////////////////
////////////////////////////////////////////////////////

class trie;
class node;

/////////////////////////////////////////////////////
//���ͱ���///////////////////////////////////////////
/////////////////////////////////////////////////////

using layerGroup = vector<node*>;
using changeUnit = pair<string, string>;
using tagTransPair = pair<string, string>;

////////////////////////////////////////////////////////
//ȫ������//////////////////////////////////////////////
////////////////////////////////////////////////////////

extern vector<string> searchResult;    //������ʱ�洢�����������չʾ
extern map<string, string>tagAndTrans; //��ǩ�뷭��ӳ���
extern vector<string> favoriateList;   //�ղؼ�����
extern vector<changeUnit> changeRecord;//����Ŀ¼����
extern int resMinimumSeqNumber;		   //��С���к�,��ʱ�洢����������
extern int resMaximumSeqNumber;		   //������к�,��ʱ�洢����������
extern vector<string> record;		   //��ʷ��¼�洢����ʵ��
extern trie mainTrie;				   //Ӣ��Tag�洢��
extern trie commandTrie;			   //ָ��洢��
extern trie zhTransTrie;			   //���ķ���洢��,����char�������ƿ����޷�ʵ��
extern bool autoClear;				   //�Ƿ����Զ����ģʽ
extern bool haveCmdPassedIn;		   //�Ƿ��б�ǰ�򴫵����ײ�Ĵ�����ָ��
extern string cmdPassedIn;			   //�洢����ָ������
extern bool askToQuit;				   //�û��Ƿ�Ҫ���˳�
extern vector<string> allCommand;	   //����ָ��
extern vector<string> cmdSearchRes;	   //�洢��������ָ��

//////////////////////////////////////////////////////////
//�ڵ���//////////////////////////////////////////////////
//////////////////////////////////////////////////////////

class node {
private:
	char nodeContent; //����
public:
	int layer; //����
	node* parent;
	map<char, node*> next; //�ӽڵ��
	bool isEndOfWord; //��β���
	vector<node*> allChild;

	//״̬�춨˼��:�������ڶ������������ʱ�ĳ�ʱ״̬�仯��������Ϊģʽ
	node();
	node(char inputContent, bool isEnd, int layerIn,node* parentNode);
	node* findChild(char c);
	node* whereKey(char key); 
	//����ģ�黯˼��:�������һ���ж��Ƿ��������ӽڵ�ĺ���
	void markEnd();
	//Ϊ��insert��ǽ�β�ڵ�����
	void markNotEnd();
	int childCount; //�ӽڵ���
	char readContent()const;
};

//////////////////////////////////////////////////////////
//�ֵ�����////////////////////////////////////////////////
//////////////////////////////////////////////////////////

class trie {
private:
	node root;
public:
	int maxLayer = 0;
	int count;//�ʻ���
	map<int, layerGroup> layerCatalog; //���ֵ����Ӧ��Ƚڵ�Ⱥӳ��ı�

	vector<node*> baseSearch(string keyword,node* rootIn);
	void layerSearch(string keyword,int layerIn, vector<string>& searchResultIn = searchResult);
	void deepSearch(string keyword);
	string readResult(node* edge);
	int insert(string wordIn);
	bool remove(string Deleted);
	void trieRemove(string keyword);
	trie();
	void layerClassify(node* nodeIn);
	
	//����layerֵ��node���з���
};

/////////////////////////////////////////////////
//����չʾ����///////////////////////////////////
/////////////////////////////////////////////////

void showResult();
void addToFavoriate(string keyword);
string showTrans(string tag);

///////////////////////////////////////////////////////
//�ֵ��ȡ���޸ĺ���///////////////////////////////////
///////////////////////////////////////////////////////

void readDictionary(ifstream& dictionary, trie& trie);
void saveChange();
void readMultiDict(string pathIn,trie& trie);
bool checkDictCount(string pathIn);

//////////////////////////////////////////////////////////
//�ļ�·������////////////////////////////////////////////
//////////////////////////////////////////////////////////

#define mainPath "dictionary\\dictionary.txt"
#define pathToFile "D:\\Project\\Final Project--C++AutoComplete\\Final Project--C++AutoComplete\\Dictionary"
#define stdextension ".txt"

//////////////////////////////////////////////////////////
//�����û�����////////////////////////////////////////////
//////////////////////////////////////////////////////////

void innerAddWord(string fullWord,string trans,trie& trie);
void innerDeleteWord(string fullWord,trie& trie);
bool askConfirm();
void showChange();

//////////////////////////////////////////////////////////
//�쳣����////////////////////////////////////////////////
//////////////////////////////////////////////////////////