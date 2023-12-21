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
	layerClassify();
}//为insert准备的有参构造函数

//查找符合要求的子节点
node* node::whereKey(char key) {
	for (auto nextpair : next) {
		if (nextpair.first == key)return nextpair.second;
	}
	return nullptr;
}

void node::markEnd() {
	this->isEndOfWord = 1;
}

void node::layerClassify()
{
	auto iterTemp = enCatalog.find(layer);
	if (iterTemp != enCatalog.end())
	{
		iterTemp->second.push_back(this);
		return;//已经存在了层群的话就直接向其中插入
	};
	//如果出现了新层则新建一个层群,插入新建node,再将该层群插入层群目录
	auto newLayerGroup = new layerGroup;
	newLayerGroup->push_back(this);
	enCatalog.insert(make_pair(layer, *newLayerGroup));

}
//根据node构造时的层数决定是不是要新建一个vector来容纳

//trie类的实现

//插入词汇函数
int trie::insert(string wordIn) {
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) {
			node* temp=new node(c,0,current->layer+1,current);
			current->next.insert(make_pair(c,temp));
			current = temp;
			//如果当前节点没有已存在的所需子节点,则新建一个节点,将其与主Trie结构相连并将current注意力指针移动到其位置
		}
		else {
			current = current->whereKey(c);
			//如果有已存在的所需节点,则直接移动注意力指针,进入下次循环
		}
	}
	//循环结束,这代表current指向了当前单词末尾所在节点,对其标记
	current->markEnd();
	count++;
	return count;
}

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


