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
"confirm" ,"clear" ,"count" };
int resMinimumSeqNumber = 1;
int resMaximumSeqNumber = 0;
vector<string> record;
trie mainTrie;
trie commandTrie;
vector<string> searchResult;
map<string, string>tagAndTrans;
vector<string> favoriateList;
vector<changeUnit> changeRecord;
bool autoClear = false;
bool haveCmdPassedIn = false;
bool askToQuit = false;