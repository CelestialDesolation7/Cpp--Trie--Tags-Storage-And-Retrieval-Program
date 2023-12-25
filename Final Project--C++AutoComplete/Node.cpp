#include "NodeAndTrie.h"

//Node���ʵ��
node* node::findChild(char c) {
	auto targetChild = next.find(c);
	if (targetChild == next.end())
		return nullptr;
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
	layerClassify();
}//Ϊinsert׼�����вι��캯��

node::node() {
	isEndOfWord = 0;
	childCount = 0;
	layer = 0;
	nodeContent = '0';
	parent = nullptr;
}
//Ĭ�Ϲ��캯������root�ڵ�

node* node::whereKey(char key) {
	for (auto nextpair : next) 
	{
		if (nextpair.first == key)
			return nextpair.second;
	}
	return nullptr;
}
//���ҷ���Ҫ����ӽڵ�λ��,������ָ��

void node::markEnd() {
	this->isEndOfWord = 1;
}
//ĳ���ڵ㽫������Ϊ��β�ĺ���

void node::layerClassify()
{
	auto iterTemp = enCatalog.find(layer);
	if (iterTemp != enCatalog.end())
	{
		iterTemp->second.push_back(this);
		return;
		//�Ѿ������˲�Ⱥ�Ļ���ֱ�������в���
	};
	//����������²����½�һ����Ⱥ,�����½�node,�ٽ��ò�Ⱥ�����ȺĿ¼
	auto newLayerGroup = new layerGroup;
	newLayerGroup->push_back(this);
	enCatalog.insert(make_pair(layer, *newLayerGroup));
	trie::maxLayer = layer;
}
//����node����ʱ�Ĳ��������ǲ���Ҫ�½�һ��vector������

void node::markNotEnd()
{
	if (isEndOfWord == 1)
		isEndOfWord = 0;
}
//ĳ���ڵ㽫���������޸�Ϊ�Ƕ˽ڵ�ĺ���

//////////////////////////////////////////////////////////////////////////
//trie���ʵ��////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

int trie::insert(string wordIn) {
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) 
		{
			node* temp=new node(c,0,current->layer+1,current);
			current->next.insert(make_pair(c,temp));
			current->markNotEnd();
			//�޸�Ϊ�Ƕ˵�
			current = temp;
			//�����ǰ�ڵ�û���Ѵ��ڵ������ӽڵ�,���½�һ���ڵ�,��������Trie�ṹ��������currentע����ָ���ƶ�����λ��
		}
		else 
		{
			current = current->whereKey(c);
			//������Ѵ��ڵ�����ڵ�,��ֱ���ƶ�ע����ָ��,�����´�ѭ��
		}
	}
	//ѭ������,�����currentָ���˵�ǰ����ĩβ���ڽڵ�,������
	current->markEnd();
	count++;
	return count;
}
//���뵥�ʺ���

bool trie::remove(string deleted)
{
	auto tempPtr = baseSearch(deleted, &this->root);
	if (tempPtr == nullptr)
		return 0;
	node* nextToDelete = tempPtr->parent;
	while (tempPtr->childCount == 0) {

		if (tempPtr != &root)
			//�ؼ�:����ɾ�����ڵ㵼���ֵ������
			delete tempPtr;
		else return 1;

		tempPtr = nextToDelete;
		nextToDelete = nextToDelete->parent;
	}
	return 1;
}
//�����Ƴ�����.��Ҫע��:�������������û����������Ĺؼ�����ɾ��

void trie::userRemove(string keyword)
{
	bool success = remove(keyword);
	if (success) {
		cout << "��ǩ " << keyword << " �ѱ��ɹ��Ƴ�." << endl;
		count--;
	}
	else cout << "û���ڴʿ����ҵ���ǩ " << keyword << " �������������Ƿ���ȷ." << endl;
}
//�����û����Ƴ�����

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
//������������

void trie::layerSearch(string keyword,int layerIn)
{
	auto itertemp = enCatalog.find(layerIn);
	if (itertemp == enCatalog.end())
		return;
	//����Ҳ�������Ҫ��Ĳ���ֱ�Ӳ�����
	for (auto tempNodePtr : itertemp->second) 
	{
		string tempResult=readResult(baseSearch(keyword, tempNodePtr));
		if(!tempResult.empty())
		searchResult.push_back(tempResult);
	}
	//��ָ�����ÿ���ڵ���л�������(baseSearch)�����������������洢��
}
//����������

void trie::deepSearch(string keyword)
{
	searchResult.clear();
	for (int layerNow = 0; layerNow <= maxLayer; layerNow++) 
	{
		layerSearch(keyword, layerNow);
	}
}
//ȫ�����������ʵ�ֲ���:�����еĲ����layerSearch

string trie::readResult(node* edge)
{
	string result;
	node* current = edge;
	if (edge == nullptr)
		return result;
	//����ϼ����Һ������صĽ���ǿ�ָ��(��û���ҵ�����Ҫ��Ķ�),��ֱ�ӷ��ؿ��ַ���
	while (current != &root) 
	{
		result.push_back(current->readContent());
		current = current->parent;
	}
	//����ϼ����Һ����������������ָ��,��ʼ��ȡ
	return result;
}
//��ȡ�������

trie::trie()
{
	root = node();
	count = 0;
	maxLayer = 0;
}
//����������(��ʼ�ֵ���)

///////////////////////////////////////////////////////////////////////////
//ȫ�ֺ���/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void showResult() 
{
	if (searchResult.empty())
	{
		cout << "�ܱ�Ǹ,�ʿ���û������������ƥ���Tag" << endl;
		return;
	}
	cout << "����������Ĺؼ���,�������²�ȫ����\n";
	stable_sort(searchResult.begin(), searchResult.end());
	int seqNumber=1;
	for (string s : searchResult) {
		cout <<"��"<<seqNumber<<"������" <<"      " << s << endl;
		seqNumber++;
	}
	resMaximumSeqNumber = seqNumber - 1;
	cout << "���ϣ������ĳ��������¼,���������Ӧ���ֲ���Enter" << endl;
	cout << "(��NaN������      �벻Ҫ������ͼ����Ƿ�������ͼ�����������,д�ж��û������Ƿ�Ϸ��Ĵ�����ĺ�����!)" << endl;
	
}

void addToFavoriate(string keyword){
	favoriateList.push_back(keyword);
}

void selectResult(int seqNumber) {
gate0:
	if (!isdigit(seqNumber) && seqNumber > 0 && seqNumber >= resMinimumSeqNumber && seqNumber <= resMaximumSeqNumber)
	{
		cout << "�Ƿ�����.������������" << endl;
		goto gate0;
		favoriateList.push_back(searchResult[seqNumber - 1]);
	}
}

void clearFavoriate()
{
	favoriateList.clear();
}
//����ղؼ�

void showFavoriate()
{
	stable_sort(favoriateList.begin(), favoriateList.end());
}
//δ���

void readDictionary(ifstream& dictionary,trie trie)
{
	while (dictionary.fail()){
		string temp,english,zhtrans;
		getline(dictionary, temp);
		istringstream rawLine(temp);
		getline(rawLine, english, '\t');
		getline(rawLine, zhtrans);
		tagAndTrans.insert(make_pair(english, zhtrans));
		trie.insert(english);
	} 
}
//���ֵ��е����ݰ��ж���

bool addWord(string fullWork)
{
	return false;
}

void userAddWord(string fullWord)
{
}

bool deleteWord(string toDelete)
{
	return false;
}

void userDeleteWord(string toDelete)
{
}

bool findTrans(string tag)
{
	return false;
}

void showTrans(string tag)
{
}




