#include "NodeAndTrie.h"

//Node类的实现
node* node::findChild(char c) {
	auto targetChild = next.find(c);
	if (targetChild == next.end())return nullptr;
	return (*targetChild).second;
} //查找到内容为指定字符的子节点

char node::readContent() {
	return nodeContent;
}//访问当前节点的字符内容

node::node(char inputContent, bool isEnd, int layerIn,node* parentNode) {
	layer = layerIn;
	isEndOfWord = isEnd;
	nodeContent = inputContent;
	childCount = 0;
	map<char, node*> next();
	parent = parentNode;
}//为insert准备的有参构造函数

node* node::whereKey(char key) {
	for (auto nextpair : next) {
		if (nextpair.first == key)return nextpair.second;
	}
	return nullptr;
}

void node::markEnd() {
	this->isEndOfWord = 1;
}

//trie类的实现
int trie::insert(string wordIn) {
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) {
			node* temp=new node(c,0,current->layer+1,current);
			current->next.insert(make_pair(c,temp));
			current = temp;
		}
	}
	//循环结束,这代表current指向了当前单词末尾所在节点,对其标记
	current->markEnd();
	count++;
	return count;
}//插入词汇函数

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


