#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <string>

using namespace std;

struct history {
	history();
	vector<string> record;
	void insert(string inputRecord);
	void clearAll();
};//��ʷ��¼�ṹ

history::history(){}

void history::clearAll() {
	record.clear();
}//ɾ����ʷ��¼

void history::insert(string inputRecord) {
	record.insert(record.end(), inputRecord);
}//�Զ�д����ʷ��¼