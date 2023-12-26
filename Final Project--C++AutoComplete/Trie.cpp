#include "NodeAndTrie.h"

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
//(���ı����)

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