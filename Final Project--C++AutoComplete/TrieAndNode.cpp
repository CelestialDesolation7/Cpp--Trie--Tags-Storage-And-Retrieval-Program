#include "NodeAndTrie.h"
#include "Command.h"

//////////////////////////////////////////////////////////////////////////
//trie���ʵ��////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

int trie::insert(string wordIn) {
	bool newNodeCreated = false;
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) 
		{
			node* temp=new node(c,0,current->layer+1,current);
			if (!newNodeCreated)newNodeCreated = true;
			layerClassify(temp);
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
	if(newNodeCreated)count++;
	return count;
}
//���뵥�ʺ���

void trie::layerClassify(node* nodeIn)
{
	auto iterTemp = layerCatalog.find(nodeIn->layer);
	if (iterTemp != layerCatalog.end())
	{
		iterTemp->second.push_back(nodeIn);
		return;
		//�Ѿ������˲�Ⱥ�Ļ���ֱ�������в���
	};
	//����������²����½�һ����Ⱥ,�����½�node,�ٽ��ò�Ⱥ�����ȺĿ¼
	auto newLayerGroup = new layerGroup;
	newLayerGroup->push_back(nodeIn);
	layerCatalog.insert(make_pair(nodeIn->layer, *newLayerGroup));
	trie::maxLayer = nodeIn->layer;
}
//����node����ʱ�Ĳ��������ǲ���Ҫ�½�һ��vector������

bool trie::remove(string deleted)
{
	auto tempPtr = baseSearch(deleted, &this->root);
	if (tempPtr == nullptr)
		return 0;
	node* nextToDelete = tempPtr->parent;
	while (tempPtr->childCount == 0) {

		if (tempPtr != &root)
			//�ؼ�:����ɾ�����ڵ㵼���ֵ������
		{
			int layerNow = tempPtr->layer;
			//��¼��ɾ��̬�ڵ�Ĳ���
			auto layerGroupPairNow = this->layerCatalog.find(layerNow);
			//��¼��ɾ��̬�ڵ�Ĳ�����Ӧ��<����,��ڵ�Ⱥ�洢��>��Ԫ��
			auto& layerGroupNow = layerGroupPairNow->second;
			//��ȡָ��������Ԫ��ĵڶ���(����ڵ�Ⱥ�洢��)��������
			for (auto nodePtrIterator = layerGroupNow.begin(); nodePtrIterator < layerGroupNow.end();nodePtrIterator++) {
				//���������洢��,�ҵ����д洢��"ָ��ǰ��������--��ɾ��̬�ڵ�"��ָ��
				if (*nodePtrIterator == tempPtr)layerGroupNow.erase(nodePtrIterator);
				//����ָ��ɾ��,���ѭ����·
				break;
			}
			//��ʱ������������ָ��ָ��ǰ��������,����ָ������
			delete tempPtr;
			//��ɾ��̬ת��Ϊ��ɾ��̬
			if (layerGroupPairNow->second.empty())
				//���ǰ���Ĵ洢��,������Ƿ��Ѿ��ճ�
			{
				this->layerCatalog.erase(layerNow);
				maxLayer--;
			}	//����:�����ͼ��if���ִ�еĸ��ϲ����÷ֺŷָ��û���ô����ŷ�װ,���ᱨ��
				//�������һ����ڵ�Ⱥ�洢���ѿ�,����ɾ��������������
		}
		else return 1;

		tempPtr = nextToDelete;
		nextToDelete = nextToDelete->parent;
	}
	return 1;
}
//�����Ƴ�����.��Ҫע��:�������������û����������Ĺؼ�����ɾ��

void trie::trieRemove(string keyword)
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

void trie::layerSearch(string keyword,int layerIn, vector<string>& searchResultIn=searchResult)
{
	auto itertemp = layerCatalog.find(layerIn);
	if (itertemp == layerCatalog.end())
		return;
	//����Ҳ�������Ҫ��Ĳ���ֱ�Ӳ�����
	for (auto tempNodePtr : itertemp->second) 
	{
		string tempResult=readResult(baseSearch(keyword, tempNodePtr));
		if(!tempResult.empty())
		searchResultIn.push_back(tempResult);
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

///////////////////////////////////////////////////////////////
//Node���ʵ��/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

node* node::findChild(char c) {
	auto targetChild = next.find(c);
	if (targetChild == next.end())
		return nullptr;
	return (*targetChild).second;
} //���ҵ�����Ϊָ���ַ����ӽڵ�

char node::readContent() const {
	return nodeContent;
}//���ʵ�ǰ�ڵ���ַ�����

node::node(char inputContent, bool isEnd, int layerIn, node* parentNode) {
	layer = layerIn;
	isEndOfWord = isEnd;
	nodeContent = inputContent;
	childCount = 0;
	map<char, node*> next();
	parent = parentNode;
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
	for (auto& nextpair : next)
		//ϰ��:�Ը����������ͽ��б����Ҳ������޸�ʱʹ������
		//�Ա���ǣ����������ƹ��캯������������˷�
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

void node::markNotEnd()
{
	if (isEndOfWord == 1)
		isEndOfWord = 0;
}
//ĳ���ڵ㽫���������޸�Ϊ�Ƕ˽ڵ�ĺ���

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
	cout << "����������Ĺؼ���,�������²�ȫ����\n"
		 << "==========================================\n";
	stable_sort(searchResult.begin(), searchResult.end());
	int seqNumber = 1;
	for (string s : searchResult) {
		cout << "��" << seqNumber << "������" << "      " << s
			<< "      " << showTrans(s) << endl;
		seqNumber++;
	}
	cout << "==========================================\n";
	resMaximumSeqNumber = seqNumber - 1;
	cout << "���ϣ���ղ�ĳ��������¼,��ʹ��Selectָ��ڿո����������Ӧ����" << endl;
}
//չʾ�������

void addToFavoriate(string keyword) {
	favoriateList.push_back(keyword);
}
//���ʻ�����ղؼ�

void readDictionary(ifstream& dictionary, trie trie)
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
//���ֵ��е����ݰ��ж���

bool checkDictCount(string pathIn)
{
	int dictCount = 0;
	filesystem::path dictRepository(pathIn);
	for (auto& entry : filesystem::directory_iterator(dictRepository)) {
		if (entry.path().extension() == stdextension)
			dictCount++;
	}
	if (dictCount == 1)return true;
	return false;
}
//����ֵ��Ŀ¼���Ƿ������һ���ֵ��ļ�

void innerAddWord(string fullWord, string trans, trie trie)
{
	trie.insert(fullWord);
	changeRecord.push_back(make_pair(fullWord, "���"));
	tagAndTrans.insert(make_pair(fullWord, trans));
}
//�ڲ���Ӻ���

void innerDeleteWord(string fullWord, trie trie) {
	trie.trieRemove(fullWord);
	changeRecord.push_back(make_pair(fullWord, "ɾ��"));
	tagAndTrans.erase(fullWord);
}
//�ڲ�ɾ������

string showTrans(string tag)
{
	auto temp = tagAndTrans.find(tag);
	if (temp == tagAndTrans.end())
		return "û�����ķ���";
	return temp->second;
}
//���һ��Tag�ķ���

void saveChange()
{
	ofstream dictionaryTemp(mainPath, ios_base::trunc);
	for (auto& temp : tagAndTrans) {
		string lineTemp;
		lineTemp = temp.first + '\t' + temp.second + '\n';
		//���Ͻ��޸ĺ���ֵ䱣�����,׼�����·�����д��
		size_t byteCount = lineTemp.size() * sizeof(char);
		dictionaryTemp.write(lineTemp.data(), byteCount);
		//��ǰ��д�����,�����´�д��
	}
	dictionaryTemp.close();
}
//�����޸ĺ���

void readMultiDict(string pathIn, trie trie)
{
	filesystem::path folderPath = pathIn;
	filesystem::directory_iterator iteratorIn(pathIn);
	bool foundDict = 0;
	//����ѭ��ּ���ж��Ƿ������Ч�ļ�
	for (const auto& eachEntry : iteratorIn) {
		bool isDict = (eachEntry.path().extension() == stdextension);
		if (eachEntry.is_regular_file() && isDict) {
			foundDict = 1;
			break;
		}
	}
	if (!foundDict) {
		throw(runtime_error("��ȡ����:�ʿ�Ŀ¼�²�������Ч�ļ�."));
	}
	//����ѭ��ּ���ж��Ƿ������Ч�ļ�
	for (const auto& eachEntry : iteratorIn) {
		//end()ȫ�ֺ�����������Ŀ¼ʱ����β�������
		if (eachEntry.path().extension() == stdextension) {
			ifstream fileNow(eachEntry.path());
			readDictionary(fileNow, trie);
			fileNow.close();
		}
	}
}
//���ж��ֵ��ļ����ϻ���ȡ�ĺ���

void showChange() {
	for (auto& changeUnitNow : changeRecord) {
		cout << changeUnitNow.first <<"      "
			 << changeUnitNow.second << endl;
	}
}
//չʾ������ʷ��¼�ĺ���