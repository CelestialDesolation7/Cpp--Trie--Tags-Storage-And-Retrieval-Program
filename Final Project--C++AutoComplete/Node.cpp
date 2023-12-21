#include "NodeAndTrie.h"

//Node���ʵ��
node* node::findChild(char c) {
	auto targetChild = next.find(c);
	if (targetChild == next.end())return nullptr;
	return (*targetChild).second;
} //���ҵ�����Ϊָ���ַ����ӽڵ�

char node::readContent() {
	return nodeContent;
}//���ʵ�ǰ�ڵ���ַ�����

node::node(char inputContent, bool isEnd, int layerIn,node* parentNode) {
	layer = layerIn;
	isEndOfWord = isEnd;
	nodeContent = inputContent;
	childCount = 0;
	map<char, node*> next();
	parent = parentNode;
}//Ϊinsert׼�����вι��캯��

node* node::whereKey(char key) {
	for (auto nextpair : next) {
		if (nextpair.first == key)return nextpair.second;
	}
	return nullptr;
}

void node::markEnd() {
	this->isEndOfWord = 1;
}

//trie���ʵ��
int trie::insert(string wordIn) {
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) {
			node* temp=new node(c,0,current->layer+1,current);
			current->next.insert(make_pair(c,temp));
			current = temp;
		}
	}
	//ѭ������,�����currentָ���˵�ǰ����ĩβ���ڽڵ�,������
	current->markEnd();
	count++;
	return count;
}//����ʻ㺯��

void trie::remove(string Deleted)
{
}
void trie::baseSearch(string keyword,node* rootIn)
{
}
void trie::layerSearch(string keyword)
{
}
void trie::deepSearch(string keyword)
{
}
trie::trie()
{
	root = node();
	count = 0;
	maxLayer = 0;
}


