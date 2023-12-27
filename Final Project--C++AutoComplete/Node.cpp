#include "NodeAndTrie.h"

///////////////////////////////////////////////////////////////
//Node类的实现/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

node* node::findChild(char c) {
	auto targetChild = next.find(c);
	if (targetChild == next.end())
		return nullptr;
	return (*targetChild).second;
} //查找到内容为指定字符的子节点

char node::readContent() const{
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

node::node() {
	isEndOfWord = 0;
	childCount = 0;
	layer = 0;
	nodeContent = '0';
	parent = nullptr;
}
//默认构造函数构造root节点

node* node::whereKey(char key) {
	for (auto &nextpair : next) 
		//习惯:对复杂数据类型进行遍历且不进行修改时使用引用
		//以避免牵扯到多个复制构造函数引发错误或浪费
	{
		if (nextpair.first == key)
			return nextpair.second;
	}
	return nullptr;
}
//查找符合要求的子节点位置,返回其指针

void node::markEnd() {
	this->isEndOfWord = 1;
}
//某个节点将自身标记为结尾的函数

void node::layerClassify()
{
	auto iterTemp = enCatalog.find(layer);
	if (iterTemp != enCatalog.end())
	{
		iterTemp->second.push_back(this);
		return;
		//已经存在了层群的话就直接向其中插入
	};
	//如果出现了新层则新建一个层群,插入新建node,再将该层群插入层群目录
	auto newLayerGroup = new layerGroup;
	newLayerGroup->push_back(this);
	enCatalog.insert(make_pair(layer, *newLayerGroup));
	trie::maxLayer = layer;
}
//根据node构造时的层数决定是不是要新建一个vector来容纳

void node::markNotEnd()
{
	if (isEndOfWord == 1)
		isEndOfWord = 0;
}
//某个节点将自身重新修改为非端节点的函数