#include "NodeAndTrie.h"

//Node类的实现
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

///////////////////////////////////////////////////////////////////////////
//全局函数/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

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
		cout <<"第"<<seqNumber<<"个建议" <<"      " << s
			 << "      " << showTrans(s) << endl;
		seqNumber++;
	}
	resMaximumSeqNumber = seqNumber - 1;
	cout << "如果希望保存某个搜索记录,请输入其对应数字并按Enter" << endl;
	cout << "(第NaN个建议      请不要总是试图输入非法内容试图引发程序崩溃,写判断用户输入是否合法的代码真的很无聊!)" << endl;
	
}

void addToFavoriate(string keyword){
	favoriateList.push_back(keyword);
}
//将词汇加入收藏夹

void selectResult(int seqNumber) {
gate0:
	if (!isdigit(seqNumber) && seqNumber > 0 && seqNumber >= resMinimumSeqNumber && seqNumber <= resMaximumSeqNumber)
	{
		cout << "非法输入.请输入正整数" << endl;
		goto gate0;
		favoriateList.push_back(searchResult[seqNumber - 1]);
	}
}
//选择搜索结果
// (有文本输出)
// (未完成)

void clearFavoriate()
{
	favoriateList.clear();
}
//清空收藏夹

void showFavoriate()
{
	stable_sort(favoriateList.begin(), favoriateList.end());
}
//(未完成)

void readDictionary(ifstream& dictionary,trie trie)
{
	string temp, english, zhtrans;
	while (getline(dictionary, temp)) 
	{
		istringstream rawLine(temp);
		getline(rawLine, english, '\t');
		getline(rawLine, zhtrans);
		tagAndTrans.insert(make_pair(english, zhtrans));
		trie.insert(english);
	}
}
//将字典中的内容按行读入

void userAddWord(string fullWord,string trans,trie trie)
{
	trie.insert(fullWord);
	changeRecord.push_back(make_pair(fullWord, "添加"));
	tagAndTrans.insert(make_pair(fullWord, trans));
	cout << "标签 " << fullWord << " 已被加入词库" << endl;
}
//面向用户的删除函数
//(有文本输入)

string showTrans(string tag)
{
	auto temp = tagAndTrans.find(tag);
	if (temp == tagAndTrans.end())
		return "没有中文翻译";
	return temp->second;
}
//获得一个Tag的翻译

void userDeleteWord(string toDelete,trie trie){
	if (trie.remove(toDelete))
	{
		cout << "词汇 " << toDelete << " 已成功删除" << endl;
		changeRecord.push_back(make_pair(toDelete, "删除"));
		tagAndTrans.erase(toDelete);
	}
	else cout << "删除失败,词库中不存在这个词,请检查输入正确性" << endl;
}
//删除词汇函数
// (有文本输出)

void saveChange()
{
	ofstream dictionaryTemp(path, ios_base::trunc);
	for (auto &temp : tagAndTrans) {
		string lineTemp;
		lineTemp = temp.first + '\t' + temp.second+'\n';
		//以上将修改后的字典保存成行,准备在下方进行写入
		size_t byteCount = lineTemp.size() * sizeof(char);
		dictionaryTemp.write(lineTemp.data(), byteCount);
		//当前行写入完毕,进入下次写入
	}
	dictionaryTemp.close();
}
//保存修改函数