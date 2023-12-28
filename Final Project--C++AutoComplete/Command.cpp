#include "Command.h"
#include "NodeAndTrie.h"

static bool charEqual(char c1, char c2) {
	return tolower(c1) == tolower(c2);
}

bool operationEqual(string str1, string str2)
{
	auto charEqual = [](char c1, char c2) {return tolower(c1) == tolower(c2); };
	return equal(str1.begin(),str1.end(),str2.begin(),charEqual);
}
//��Сд�����е��ַ�������ж�
//����ʹ����Lambda���ʽ
//��δ��ɲ���ȫ�����ƥ��

command* analyseCommand(string userCommand)
{
	string operation;
	string content;
	istringstream temp(userCommand);
	temp >> operation;
	getline(temp, content);

	if(operation.empty())
		return nullptr;
	else if (operationEqual(operation,"help"))
		return new helpCmd(content); //չʾ�����б�
	else if (operationEqual(operation, "delete"))
		return new deleteCmd(content); //ɾ��ָ��
	else if (operationEqual(operation, "add"))
		return new addCmd(content);
	else if (operationEqual(operation, "record"))
		return new recordCmd(content);
	else if (operationEqual(operation, "favoriate"))
		return new showFavoriateCmd(content);
	else if (operationEqual(operation, "clear"))
		return new clearScreenCmd(content);
	else if (operationEqual(operation, "wildcard"))
		return new wildcardCmd(content);
	else if (operationEqual(operation, "search"))
		return new searchCmd(content);
	else if (operationEqual(operation, "save"))
		return new saveCmd(content);
	else if (operationEqual(operation, "quit"))
		return new quitCmd(content);
	else 
		return nullptr;
}

void clearFavoriateCmd::execute()
{
	favoriateList.clear();
	cout << "�ղؼ��ѳɹ����" << endl;
}
//����ղؼ�ָ�������

void deleteCmd::execute()
{
	if (this->content.empty())
	{
		cout << "��û��������Ҫɾ����Tag.������.\n";
	}
	else {
		cout << "��ȷ��Ҫɾ�� " << this->content << " �������?�������Ȼ�������˳�����ʱ��������.\n"
			 << "���ȷ��,��ʹ��confirmָ��," << "���������κ���������.\n";
		string ifConfirm;
		getline(cin, ifConfirm);
		command* temp = analyseCommand(ifConfirm);
		if (temp != nullptr && temp->readClass() != "confirm")
		{
			mainTrie.userRemove(this->content);
			cout << "ɾ���ѳɹ�.��ǰʣ�� " << mainTrie.count << " ���ʻ�\n";
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
		cout << "��ȷ��Ҫ��� " << this->content << " �������?�������Ȼ�������˳�����ʱ��������.\n"
			<< "���ȷ��,��ʹ��confirmָ��," << "���������κ���������.\n";
		string ifConfirm;
		getline(cin, ifConfirm);
		command* temp= analyseCommand(ifConfirm);
		if (temp!=nullptr && temp->readClass() != "confirm")
		{
			int countNow = mainTrie.insert(this->content);
			cout << "����ѳɹ�.��ǰ���� " << countNow << " ���ʻ�\n";
		}
		else { cout << "�ѷ������.\n"; }
	}
}
//���ָ�������

void recordCmd::execute()
{
}

void showFavoriateCmd::execute()
{
}

void clearScreenCmd::execute()
{

}

void helpCmd::execute()
{
	cout << "=====================================================================\n"
		 << "                              ָ���б�                            \n"
		 << "search-----���Ұ����ؼ��ʵ�Tag   delete----ɾ�������Tag		 \n"
		 << "add--------����һ���´ʻ�        record----�ղر�Ŷ�Ӧ���������\n"
		 << "clear------��յ�ǰ�Ի�����      help------�鿴ָ���б�         \n"
		 << "favoriate--չʾ�ղؼ�            wildcard--�鿴ͨ�����������\n"
		 << "save-------����Դʿ���޸�      quit------�˳�����\n"
		 << "confirm----ȷ��ָ��              count-----�鿴��ǰ�ʻ�����\n"
		 << "=====================================================================\n"
		 << "                              ʹ��˵��                            \n"
		 << "  ǰ�ĸ�ָ�����Ҫ��������ָ��������,���������Ĺؼ���,Ҫɾ������ʲô.\n"
		 << "����ָ�������Ҫ��ָ�����ƺ���������,��ʹ������������Ҳ�����������.\n"
		 << "���������벻������ָ��,��\"con\",������Զ�ʶ��Ϊconfirm.������Ҫע��\n"
		 << "������ǰ׺(��\"c\")����ָ��ƥ��ʱ�����޷�����������˼,����Ҫ��������\n"
		 << "ָ�����ָ��������֮���Կո�ָ�,һ���ͺ�,���Ǹ���ո����Ҳ������ʶ��\n"
		 << "�ó���֧����һ���������ؼ���,Ҳ֧��ͨ�����ʹ��."
		 << "======================================================================\n";
}
//����ָ��

void wildcardCmd::execute()
{
}

void searchCmd::execute()
{
}

void saveCmd::execute()
{
}

void quitCmd::execute()
{
}

void confirmCmd::execute(){

}
