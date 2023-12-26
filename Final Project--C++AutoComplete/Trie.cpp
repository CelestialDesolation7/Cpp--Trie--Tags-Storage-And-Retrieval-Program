#include "NodeAndTrie.h"

//////////////////////////////////////////////////////////////////////////
//trie类的实现////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

int trie::insert(string wordIn) {
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) 
		{
			node* temp=new node(c,0,current->layer+1,current);
			current->next.insert(make_pair(c,temp));
			current->markNotEnd();
			//修改为非端点
			current = temp;
			//如果当前节点没有已存在的所需子节点,则新建一个节点,将其与主Trie结构相连并将current注意力指针移动到其位置
		}
		else 
		{
			current = current->whereKey(c);
			//如果有已存在的所需节点,则直接移动注意力指针,进入下次循环
		}
	}
	//循环结束,这代表current指向了当前单词末尾所在节点,对其标记
	current->markEnd();
	count++;
	return count;
}
//插入单词函数

bool trie::remove(string deleted)
{
	auto tempPtr = baseSearch(deleted, &this->root);
	if (tempPtr == nullptr)
		return 0;
	node* nextToDelete = tempPtr->parent;
	while (tempPtr->childCount == 0) {

		if (tempPtr != &root)
			//关键:避免删除根节点导致字典树损毁
			delete tempPtr;
		else return 1;

		tempPtr = nextToDelete;
		nextToDelete = nextToDelete->parent;
	}
	return 1;
}
//基本移除函数.需要注意:本函数仅允许用户输入完整的关键词再删除

void trie::userRemove(string keyword)
{
	bool success = remove(keyword);
	if (success) {
		cout << "标签 " << keyword << " 已被成功移除." << endl;
		count--;
	}
	else cout << "没有在词库中找到标签 " << keyword << " 请检查您的输入是否正确." << endl;
}
//面向用户的移除函数
//(有文本输出)

node* trie::baseSearch(string keyword,node* rootIn)
{
	node* current = rootIn;
	for (char c : keyword) {
		auto temp = current->whereKey(c);
		if (temp == nullptr)
			return nullptr;
		current = temp;
	}
	return current;
}
//基本搜索函数

void trie::layerSearch(string keyword,int layerIn)
{
	auto itertemp = enCatalog.find(layerIn);
	if (itertemp == enCatalog.end())
		return;
	//如果找不到符合要求的层则直接不搜索
	for (auto tempNodePtr : itertemp->second) 
	{
		string tempResult=readResult(baseSearch(keyword, tempNodePtr));
		if(!tempResult.empty())
		searchResult.push_back(tempResult);
	}
	//对指定层的每个节点进行基本搜索(baseSearch)并将结果发送至结果存储区
}
//层搜索函数

void trie::deepSearch(string keyword)
{
	searchResult.clear();
	for (int layerNow = 0; layerNow <= maxLayer; layerNow++) 
	{
		layerSearch(keyword, layerNow);
	}
}
//全树深度搜索的实现策略:对所有的层进行layerSearch

string trie::readResult(node* edge)
{
	string result;
	node* current = edge;
	if (edge == nullptr)
		return result;
	//如果上级查找函数返回的结果是空指针(即没有找到符合要求的端),则直接返回空字符串
	while (current != &root) 
	{
		result.push_back(current->readContent());
		current = current->parent;
	}
	//如果上级查找函数返回了有意义的指针,则开始读取
	return result;
}
//读取搜索结果

trie::trie()
{
	root = node();
	count = 0;
	maxLayer = 0;
}
//构造树种子(初始字典树)