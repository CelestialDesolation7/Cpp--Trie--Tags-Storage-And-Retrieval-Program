#include "NodeAndTrie.h"

//Node类的实现
node* node::findChild(char c) {
	auto targetChild = next.find(c);
	if (targetChild == next.end())
		return nullptr;
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
	for (auto nextpair : next) 
	{
		if (nextpair.first == key)
			return nextpair.second;
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

//trie类的实现

//插入词汇函数
int trie::insert(string wordIn) {
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) 
		{
			node* temp=new node(c,0,current->layer+1,current);
			current->next.insert(make_pair(c,temp));
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

void trie::remove(string Deleted)
{
}

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
	
}

node* trie::deepSearch(string keyword)
{
}

//读取搜索结果
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

trie::trie()
{
	root = node();
	count = 0;
	maxLayer = 0;
}

//全局函数
void showResult() 
{
	if (searchResult.empty())
	{
		cout << "很抱歉,词库中没有与您的输入匹配的Tag" << endl;
		return;
	}
	cout << "根据您输入的关键词,给出如下补全建议\n";
	stable_sort(searchResult.begin(), searchResult.end());
	int seqNumber=1;
	for (string s : searchResult) {
		cout <<"第"<<seqNumber<<"个建议" <<"      " << s << endl;
		seqNumber++;
	}
	cout << "如果希望保存某个搜索记录,请输入其对应数字并按Enter" << endl;
	cout << "(第NaN个建议      请不要总是试图输入非法内容试图引发程序崩溃,写判断用户输入是否合法的代码真的很无聊!)" << endl;
	
}
