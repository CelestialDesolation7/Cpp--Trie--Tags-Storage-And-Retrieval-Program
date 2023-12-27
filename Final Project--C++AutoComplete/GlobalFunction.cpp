#include "NodeAndTrie.h"

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
		cout <<"��"<<seqNumber<<"������" <<"      " << s
			 << "      " << showTrans(s) << endl;
		seqNumber++;
	}
	resMaximumSeqNumber = seqNumber - 1;
	cout << "���ϣ������ĳ��������¼,���������Ӧ���ֲ���Enter" << endl;
	cout << "(��NaN������      �벻Ҫ������ͼ����Ƿ�������ͼ�����������,д�ж��û������Ƿ�Ϸ��Ĵ�����ĺ�����!)" << endl;
	
}

void addToFavoriate(string keyword){
	favoriateList.push_back(keyword);
}
//���ʻ�����ղؼ�

void selectResult(int seqNumber) {
gate0:
	if (!isdigit(seqNumber) && seqNumber > 0 && seqNumber >= resMinimumSeqNumber && seqNumber <= resMaximumSeqNumber)
	{
		cout << "�Ƿ�����.������������" << endl;
		goto gate0;
		favoriateList.push_back(searchResult[seqNumber - 1]);
	}
}
//ѡ���������
// (���ı����)
// (δ���)

void clearFavoriate()
{
	favoriateList.clear();
}
//����ղؼ�

void showFavoriate()
{
	stable_sort(favoriateList.begin(), favoriateList.end());
}
//(δ���)

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
//���ֵ��е����ݰ��ж���

void userAddWord(string fullWord,string trans,trie trie)
{
	trie.insert(fullWord);
	changeRecord.push_back(make_pair(fullWord, "���"));
	tagAndTrans.insert(make_pair(fullWord, trans));
	cout << "��ǩ " << fullWord << " �ѱ�����ʿ�" << endl;
}
//�����û���ɾ������
//(���ı����)

string showTrans(string tag)
{
	auto temp = tagAndTrans.find(tag);
	if (temp == tagAndTrans.end())
		return "û�����ķ���";
	return temp->second;
}
//���һ��Tag�ķ���

void userDeleteWord(string toDelete,trie trie){
	if (trie.remove(toDelete))
	{
		cout << "�ʻ� " << toDelete << " �ѳɹ�ɾ��" << endl;
		changeRecord.push_back(make_pair(toDelete, "ɾ��"));
		tagAndTrans.erase(toDelete);
	}
	else cout << "ɾ��ʧ��,�ʿ��в����������,����������ȷ��" << endl;
}
//ɾ���ʻ㺯��
// (���ı����)

void saveChange()
{
	ofstream dictionaryTemp(mainPath, ios_base::trunc);
	for (auto &temp : tagAndTrans) {
		string lineTemp;
		lineTemp = temp.first + '\t' + temp.second+'\n';
		//���Ͻ��޸ĺ���ֵ䱣�����,׼�����·�����д��
		size_t byteCount = lineTemp.size() * sizeof(char);
		dictionaryTemp.write(lineTemp.data(), byteCount);
		//��ǰ��д�����,�����´�д��
	}
	dictionaryTemp.close();
}
//�����޸ĺ���

void readMultiDict(string pathIn,trie trie)
{
	filesystem::path folderPath = pathIn;
	filesystem::directory_iterator iteratorIn(pathIn);
	bool foundDict = 0;
	for (const auto& eachEntry : iteratorIn) {
		bool isDict = eachEntry.path().extension() == stdextension;
		if (eachEntry.is_regular_file() && isDict) {
			foundDict = 1;
			break;
		}
	}
	if (!foundDict) {
		throw(runtime_error("��ȡ����:ָ��Ŀ¼�²�������Ч�ļ�."));
	}
	for (const auto& eachEntry : iteratorIn) {
		//end()ȫ�ֺ�����������Ŀ¼ʱ����β�������
		if (eachEntry.is_regular_file()) {
			ifstream fileNow(eachEntry.path());
			readDictionary(fileNow, trie);
		}
	}
}
//���ж��ֵ��ļ����ϻ���ȡ�ĺ���

