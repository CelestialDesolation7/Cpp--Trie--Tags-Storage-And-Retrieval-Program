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

};

class trie {
private:
	node root;
	int maxLayer;
	int count;//�ʻ���
public:
	int insert(string wordIn);
	void remove(string Deleted);

	void baseSearch(string keyword,node* rootIn);
	void layerSearch(string keyword);
	void deepSearch(string keyword);

	trie();

};