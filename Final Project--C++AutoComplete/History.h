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
};//历史记录结构

history::history(){}

void history::clearAll() {
	record.clear();
}//删除历史记录

void history::insert(string inputRecord) {
	record.insert(record.end(), inputRecord);
}//自动写入历史记录