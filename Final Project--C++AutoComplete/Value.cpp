#include "Command.h"
#include "NodeAndTrie.h"

string command::operationClass = "command";
string helpCmd::operationClass = "help";
string deleteCmd::operationClass = "delete";
string addCmd::operationClass = "add";
string switchCmd::operationClass = "switch";
string favoriateCmd::operationClass = "showFavoriate";
string selectCmd::operationClass = "select";
string searchCmd::operationClass = "search";
string saveCmd::operationClass = "save";
string quitCmd::operationClass = "quit";
string confirmCmd::operationClass = "confirm";
string clearCmd::operationClass = "clear";
string countCmd::operationClass = "count";
string ambiguityCmd::operationClass = "ambiquity";

vector<string> allCommand = {
"help" ,"delete" ,"add" ,
"switch" ,"favoriate" ,
"select" ,"search" ,"save" ,"quit" ,
"confirm" ,"clear" ,"count" };			//����ָ����б�

vector<string> searchResult;			//������ʱ�洢�����������չʾ
map<string, string>tagAndTrans;			//��ǩ�뷭��ӳ���
vector<string> favoriateList;			//�ղؼ�����
vector<changeUnit> changeRecord;		//����Ŀ¼����
int resMinimumSeqNumber = 1;		    //��С���к�,��ʱ�洢����������
int resMaximumSeqNumber = 0;		    //������к�,��ʱ�洢����������
vector<string> record;					//��ʷ��¼�洢����ʵ��
trie mainTrie;							//Ӣ��Tag�洢��
trie commandTrie;						//ָ��洢��
trie zhTransTrie;						//���ķ���洢��,����char�������ƿ����޷�ʵ��
bool autoClear = false;				    //�Ƿ����Զ����ģʽ
bool haveCmdPassedIn = false;		    //�Ƿ��б�ǰ�򴫵����ײ�Ĵ�����ָ��
string cmdPassedIn;						//�洢����ָ������
bool askToQuit = false;				    //�û��Ƿ�Ҫ���˳�
vector<string> cmdSearchRes;			//�洢��������ָ��