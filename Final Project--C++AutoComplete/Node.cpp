#include "NodeAndTrie.h"

///////////////////////////////////////////////////////////////
//Node���ʵ��/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

node* node::findChild(char c) {
	auto targetChild = next.find(c);
	if (targetChild == next.end())
		return nullptr;
	return (*targetChild).second;
} //���ҵ�����Ϊָ���ַ����ӽڵ�

char node::readContent() const{
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
	for (auto &nextpair : next) 
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