#include "Command.h"
#include "NodeAndTrie.h"

string command::operationClass = "command";
string helpCmd::operationClass = "help";
string deleteCmd::operationClass = "delete";
string addCmd::operationClass = "add";
string recordCmd::operationClass = "record";
string showFavoriateCmd::operationClass = "showFavoriate";
string clearFavoriateCmd::operationClass = "clearFavoriate";
string wildcardCmd::operationClass = "wildcard";
string searchCmd::operationClass = "search";
string saveCmd::operationClass = "save";
string quitCmd::operationClass = "quit";
string confirmCmd::operationClass = "confirm";
string clearScreenCmd::operationClass = "clearScreen";

int resMinimumSeqNumber = 1;
int resMaximumSeqNumber = 0;
vector<string> record;
trie mainTrie;
trie commandTrie;
vector<string> searchResult;
map<string, string>tagAndTrans;
vector<string> favoriateList;
vector<changeUnit> changeRecord;