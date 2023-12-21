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
	layerClassify();
}//Ϊinsert׼�����вι��캯��

//���ҷ���Ҫ����ӽڵ�
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
		return;//�Ѿ������˲�Ⱥ�Ļ���ֱ�������в���
	};
	//����������²����½�һ����Ⱥ,�����½�node,�ٽ��ò�Ⱥ�����ȺĿ¼
	auto newLayerGroup = new layerGroup;
	newLayerGroup->push_back(this);
	enCatalog.insert(make_pair(layer, *newLayerGroup));

}
//����node����ʱ�Ĳ��������ǲ���Ҫ�½�һ��vector������

//trie���ʵ��

//����ʻ㺯��
int trie::insert(string wordIn) {
	node* current = &this->root;
	for (char c : wordIn) {
		if (current->whereKey(c) == nullptr) {
			node* temp=new node(c,0,current->layer+1,current);
			current->next.insert(make_pair(c,temp));
			current = temp;
			//�����ǰ�ڵ�û���Ѵ��ڵ������ӽڵ�,���½�һ���ڵ�,��������Trie�ṹ��������currentע����ָ���ƶ�����λ��
		}
		else {
			current = current->whereKey(c);
			//������Ѵ��ڵ�����ڵ�,��ֱ���ƶ�ע����ָ��,�����´�ѭ��
		}
	}
	//ѭ������,�����currentָ���˵�ǰ����ĩβ���ڽڵ�,������
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


