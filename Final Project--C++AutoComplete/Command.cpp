#include "Command.h"
#include "NodeAndTrie.h"


static bool charEqual(char c1, char c2) {
	return tolower(c1) == tolower(c2);
}
//��Сд�����е��ַ�����ж�

bool operationEqual(string str1, string str2)
{
	if (str1.empty())return false;
	auto stringToLower = [](string& str) {
		for (char& c : str) {c = tolower(c);}
	};
	stringToLower(str1);
	stringToLower(str2);
	if(str1==str2)
		return true;
	commandTrie.layerSearch(str1,0,cmdSearchRes);
	bool includeTarget = false;
	includeTarget = (find(cmdSearchRes.begin(), cmdSearchRes.end(), str2) != cmdSearchRes.end());
	if (cmdSearchRes.size() >= 1 && includeTarget) {
		cmdSearchRes.clear();
		return true; }
	else { 
		cmdSearchRes.clear();
		return false; }
}
//��Сд�����е��ַ�������ж�
//����ʹ����Lambda���ʽ
//ע��:�˱ȽϺ����������廷��������

string operationGuess(string partialCmd) {
	string notfound;
	auto stringToLower = [](string& str) {
		for (char& c : str) { c = tolower(c); }
		};
	stringToLower(partialCmd);
	for (string temp : allCommand) {
		if (partialCmd == temp)return temp;
	}//����û���������ָ����ֱ�ӽ��䷵��
	commandTrie.layerSearch(partialCmd, 0, cmdSearchRes);
	if (cmdSearchRes.size() == 0)
		return notfound;
	//���û�в��ҵ�ָ���򷵻ؿ��ַ���
	if (cmdSearchRes.size() == 1)
		return cmdSearchRes[0];
	//���ҵ�һ���򷵻ز²���
	return "ambiguity";
	//�����������������,���ж��ƥ����,�������崦��ָ��
}
//������ָ���Զ���ȫ����
//�������廷��������

command* stringToCmd(string fullCmd,string content)
{
	if (fullCmd.empty())
		return nullptr;
	else if (fullCmd == "add")
		return new addCmd(content);
	else if (fullCmd == "clear")
		return new clearCmd(content);
	else if (fullCmd == "confirm")
		return new confirmCmd(content);
	else if (fullCmd == "count")
		return new countCmd(content);
	else if (fullCmd == "delete")
		return new deleteCmd(content);
	else if (fullCmd == "favoriate")
		return new favoriateCmd(content);
	else if (fullCmd == "help")
		return new helpCmd(content);
	else if (fullCmd == "quit")
		return new quitCmd(content);
	else if (fullCmd == "save")
		return new saveCmd(content);
	else if (fullCmd == "search")
		return new searchCmd(content);
	else if (fullCmd == "select")
		return new selectCmd(content);
	else if (fullCmd == "switch")
		return new switchCmd(content);
	else
		return nullptr;
}
//ָ���ʶ����ָ��ʵ��ӳ����
//�ڴ�й¶����:�κε��ø�ӳ�����ĺ�������Ҫ���ڴ��ʼ������

commandPair lexicalAnalyser(string commandIn){
	string operation;
	string content;
	istringstream temp(commandIn);
	temp >> operation;
	getline(temp>>ws, content);
	return commandPair(operation,content);
}
//��ָ������ݷ��벢����ָ�����ݶ�Ԫ��ļ򵥴ʷ�������

command* analyseCommand(string userCommand)
{
	string operation;
	string content;
	istringstream temp(userCommand);
	temp >> operation;
	getline(temp>>ws, content);
	operation = operationGuess(operation);
	cmdSearchRes.clear();
	return stringToCmd(operation, content);
}
//�����û�������Ϣ��ָ��ʷ�������
//�ڴ�й¶����:�κε��ø�ӳ�����ĺ�������Ҫ���ڴ��ʼ������
//�������廷��������

bool askConfirm() {
	string ifConfirm;
	getline(cin, ifConfirm);
	auto temp = lexicalAnalyser(ifConfirm);
	if (operationEqual(temp.first, "confirm") && temp.second.empty())
		return true;
	else
		return false;
}
//����confirmָ��ĺ���.���ںܶ�ָ����Ҫconfirmȷ�Ϲʶ�����н�һ����װ��
//�������廷��������

bool sendSubCommand(string expectedCmd, bool executive) {
	string userCommand;
	getline(cin, userCommand);
	auto temp = lexicalAnalyser(userCommand);

	if (operationEqual(temp.first, expectedCmd)) {
		if (executive) {
			auto cmdTemp = stringToCmd(expectedCmd, temp.second);
			cmdTemp->execute();
			delete cmdTemp;
		}
		return false;
	}
	else {
		haveCmdPassedIn = true;
		cmdPassedIn = userCommand;
		return true;
	}
}
//���ж�ָ��ת����
//�������û������ָ����Ϊ״ָ̬��ĺ����ָ֧���,����ǰ�򴫵����ײ����������
//�������廷��������

bool sendSubCommand(bool strict, string expectedCmd, bool executive) {
	string userCommand;
	getline(cin, userCommand);
	auto temp = analyseCommand(userCommand);
	if (temp->operationClass == expectedCmd) {
		if (executive)temp->execute();
		delete temp;
		return false;
	}
	haveCmdPassedIn = true;
	cmdPassedIn = userCommand;
	delete temp;
	return true;
}
//Ӳ�ж�ָ��ת����
//�������廷��������

//////////////////////////////////////////////////////////////
//ָ��ʵ�ֺ���////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void deleteCmd::execute()
{
	if (this->content.empty())
	{
		cout << "��û��������Ҫɾ����Tag.������.\n";
	}
	else {
		cout << "��ȷ��Ҫɾ�� " << this->content << " �������?�������Ȼ�������˳�����ʱ��������.\n"
			 << "���ȷ��,��ʹ��confirmָ��," << "���������κ���������.\n";
		if (askConfirm())
		{
			innerDeleteWord(this->content, mainTrie);
		}
		else { cout << "�ѷ���ɾ��.\n";}
	}
}
//ɾ��ָ�������

void addCmd::execute()
{
	if (this->content.empty())
	{
		cout << "��û��������Ҫ��ӵ�Tag.������.\n";
	}
	else {
		int chineseIndex = 0;
		bool havetrans = 0;
		string tag, trans;
		for (auto contentElement : this->content) {
			if (isalpha(contentElement) || isspace(contentElement))
				chineseIndex++;
			else break;
		}
		if (chineseIndex == 0)
			cout << "��������������û������Ӣ��,���߽���Ӣ�ĵ�˳��д����,������.\n";
		else {
			tag = this->content.substr(0, chineseIndex);
			havetrans = (!chineseIndex == this->content.size()-1);
			//�����һ����Ӣ���ַ����������ַ���ĩβλ������
			if(!havetrans)
			trans = this->content.substr(chineseIndex);
		}
		cout << "��ȷ��Ҫ��� " << tag;

		if(havetrans)
			cout << " (" << trans << ") ";
		else cout << " (û�и�������) ";

		cout << " �������?\n�������Ȼ�������˳�����ʱ��������.\n"
			 << "���ȷ��,��ʹ��confirmָ��," << "���������κ���������.\n";

		if (askConfirm())
		{
			innerAddWord(tag, trans, mainTrie);
			cout << "����ѳɹ�.��ǰ���� " << mainTrie.count << " ���ʻ�\n";
		}
		else { cout << "�ѷ������.\n"; }
	}
}
//���ָ�������

void switchCmd::execute()
{
	if (autoClear == false)autoClear = true;
	else autoClear = false;
}
//�л�ģʽָ�������

void favoriateCmd::execute(){
	if (favoriateList.empty())
	{
		cout << "�����ղؼ���û������." << endl;
		return;
	}
	cout << "                 �ղؼ�\n"
		<< "==========================================\n";
	int seqNumber = 1;
	for (string s : searchResult) {
		cout << "��" << seqNumber << "��" << "      " << s
			<< "      " << showTrans(s) << endl;
		seqNumber++;
	}
	cout << "==========================================\n";
	cout << "�˴�ʹ��clearָ���������ղؼ�,ʹ�������κ�ָ�����.\n";
	if (!sendSubCommand(true, "clear", false)) {
		favoriateList.clear();
		cout << "�ղؼ��Ѿ����.\n";
		return;
	}
	return;
}
//�ղؼ�չʾָ�������

void clearCmd::execute()
{
	system("cls");
}
//�ֶ���նԻ���¼ָ�������

void helpCmd::execute()
{
	cout << "=======================================================================\n"
		 << "                              ָ���б�                            \n"
		 << "search-----���Ұ����ؼ��ʵ�Tag       delete----ɾ�������Tag		 \n"
		 << "add--------����һ���´ʻ�            select-----ѡ��������������ղؼ�\n"
		 << "switch----�л���������Ϣ����ģʽ   help------�鿴ָ���б�         \n"
		 << "favoriate--չʾ�ղؼ�                clear-----��նԻ���¼���ղؼ�\n"
		 << "save-------����Դʿ���޸�          quit------�˳�����\n"
		 << "confirm----ȷ��ָ��                  count-----�鿴��ǰ�ʻ�����\n"
		 << "=======================================================================\n"
		 << "                              ʹ��˵��                            \n"
		 << "  ǰ�ĸ�ָ�����Ҫ��������ָ��������,���������Ĺؼ���,Ҫɾ������ʲô.\n"
		 << "����ָ�������Ҫ��ָ�����ƺ���������,��ʹ������������Ҳ�����������.\n"
		 << "���������벻������ָ��,��\"con\",������Զ�ʶ��Ϊconfirm.������Ҫע��\n"
		 << "������ǰ׺(��\"c\")����ָ��ƥ��ʱ�����޷�����������˼,����Ҫ��������\n"
		 << "ָ�����ָ��������֮���Կո�ָ�,һ���ͺ�,���Ǹ���ո����Ҳ������ʶ��\n"
		 << "�ó���ǰ�в�֧����һ���������ؼ���,��ͨ�����ʹ��.\n\n"
		 << "  ����Ҫ����tagʱ,������ѡ���Եظ�����Ӧ�����ķ���.search,tag������֮��\n"
		 << "�Կո�ָ�,����\"add apple ƻ��\".����Ӣ��tag������԰����ո�,�����ܹ�\n"
		 << "��ȷʶ����Щ��Tag��Щ�����ķ���.��Ҳ���Բ��������ķ���.\n\n"
		 << "  switchָ���ʹ�û�ʹ�öԻ���ʷ��Ϣ��ÿ��������ָ��ʱ�Զ������.�ظ�ʹ\n"
		 << "�ø�ָ���ʹ�ó������Զ����ģʽ����Զ����ģʽ�������л�.\n\n"
		 << "  ����������չʾ�ղؼ�ʱʹ��clearָ���ȷ�Ͽ�������ղؼ�.\n\n"
		 << "  ���ڴ洢������Ҫʹ�ÿ��ַ�����wchar_t,ԭ�г������������,��Ҫ��дһ\n"
		 << "ר�����ڴ������ĵ��ֵ�,������̫��,�ʳ���ǰ�в�֧����������.\n"
		 << "=======================================================================\n";
}
//����ָ�������

void selectCmd::execute()
{
	int selected = 0;
	if (resMaximumSeqNumber == 1) {
		string selectedOne = searchResult[0];
		favoriateList.push_back(selectedOne);
		cout << "ѡ��Ĵʻ� " << selectedOne << " (" << showTrans(selectedOne) << ") "
			<< "�ѱ������ղؼ�.\n";
		return;
	}
	if (this->content.empty()) {
	  cout << "û������Ҫѡ��Ľ�����,ָ����Ч." << endl;
	  return; 
	}
	for (char c : this->content) {
		if (!isdigit(c))
		{cout << "�Ƿ�����.������������" << endl;return;}
	}
	istringstream iss(this->content);
	iss >> selected;
	if (selected <= resMaximumSeqNumber)
	{
		string selectedOne = searchResult[selected - 1];
		favoriateList.push_back(selectedOne);
		cout << "ѡ��Ĵʻ� " << selectedOne << " (" << showTrans(selectedOne) << ") "
			 << "�ѱ������ղؼ�.\n";
		return;
	}
	else { cout << "��Ч������,û��ƥ��Ľ��." << endl; return; }
}
//ѡ���ղ�ָ�������

void searchCmd::execute()
{
	resMaximumSeqNumber = 0;
	resMinimumSeqNumber = 1;
	searchResult.clear();
	if (content.empty()) {
		cout << "��û������Ҫ�����Ĺؼ���.������.\n";
		return;
	}
	mainTrie.deepSearch(this->content);
	showResult();
}
//����ָ�������

void saveCmd::execute()
{
	cout << "���ڽ��б���..." << endl;
	filesystem::path dictRepository(pathToFile);
	if (!checkDictCount(pathToFile)) {
		for (auto& entry : filesystem::directory_iterator(dictRepository)) {
			if (entry.path().extension() == stdextension)
				remove(entry.path());
		}
	}
	saveChange();
	cout << "���������.\n";
}
//����ָ�������

void quitCmd::execute()
{
	if (changeRecord.empty()) {
		cout << "�����Ѿ���ֹ����.��л����ʹ��.\n";
		Sleep(1500);
		askToQuit = true;
		return;
	}
		cout << "��������δ����ĸ���,��������:\n"
		<< "=======================================================================\n";
		showChange();
		cout << "=======================================================================\n"
			<< "�Ƿ�Ҫ������Щ����?�����,ʹ��confirmָ��.������ʹ��saveָ��.\n"
			<< "�����Ҫ�������������˳�,������������������.\n";
		if (!sendSubCommand("confirm")) {
			askToQuit = true; return;
		}
		if (!sendSubCommand("save")) {
			askToQuit = true; return;
		}
		else return;
}
//�˳����������

void confirmCmd::execute(){
	return;
}
//ȷ��ָ�������

void countCmd::execute() {
	cout << "��ǰһ���洢�� " << mainTrie.count << " ���ʻ�." << endl;
}
//�鿴����ָ�������

void ambiguityCmd::execute() {
	cout << "����ָ��������,����������ܴ�������ָ��:\n";
	for (string temp : cmdSearchRes) {
		cout << temp << endl;
	}
	cmdSearchRes.clear();
	cout << "����������.\n";
}
//���崦��ָ�������