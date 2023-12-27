#include "NodeAndTrie.h"

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
//(有文本输出)

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
	ofstream dictionaryTemp(mainPath, ios_base::trunc);
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
		throw(runtime_error("读取错误:指定目录下不存在有效文件."));
	}
	for (const auto& eachEntry : iteratorIn) {
		//end()全局函数接收上述目录时返回尾后迭代器
		if (eachEntry.is_regular_file()) {
			ifstream fileNow(eachEntry.path());
			readDictionary(fileNow, trie);
		}
	}
}
//进行多字典文件整合化读取的函数

