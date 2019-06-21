#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#define MAX_LIST_LENGTH 65536

using namespace std;

typedef struct __DOMAIN_AND_IP {
	std::string ip, hash_ip, ad;
	bool IsIPv6 = 0;
} address;

address addr[MAX_LIST_LENGTH];

std::ifstream inputFile;
std::ofstream outputFile;

void H2D_init(std::string src) {
	std::ifstream inputFile(src.c_str());
	std::ofstream outputFile("dnsmasq.conf.add");
}

void D2H_init(std::string src) {
	std::ifstream inputFile(src.c_str());
	std::ofstream outputFile("hosts");
}


std::string IP_Hash(std::string src) {
	std::string tmp = src;
	int pos = 0, stdpos = -1;
	if(tmp.find(".") != std::string::npos) {
		for(int i = 0; i < 3; i++) {
			stdpos += 4;
			pos = tmp.find(".", pos);
			if(pos < stdpos) { tmp.insert(stdpos - 3, stdpos - pos, '0'); }
			pos = stdpos + 1;
		}
		tmp.insert(stdpos + 1, stdpos + 4 - tmp.size(), '0'); 
		return tmp;
	} else if(tmp.find(":") != std::string::npos) {
		pos = tmp.find("::");
		if(pos != std::string::npos) {
			if(pos == 0) { tmp.insert(0, 1, '0'); pos++; }
			if(pos == (tmp.size() - 2)) { tmp.insert(tmp.size(), 1, '0'); }
//			cout << tmp << endl;
			int tpos = -1, tcnt = 0;
//			while(tpos != std::string::npos) {
//				tpos = tmp.find(":", tpos);
//				tcnt++;
//				tpos++;
//			}
			do {
				tpos = tmp.find(":", tpos + 1);
				tcnt++;
			} while(tpos != std::string::npos);
			cout << tcnt << endl;
			tmp.insert(pos + 1, 1, '0');
//			cout << tmp << endl;
			for(; tcnt < 7; tcnt++) {
				tmp.insert(pos + 1, 1, ':');
				tmp.insert(pos + 1, 1, '0');
//				cout << tmp << endl;
			}
			//need further testing
		}
		pos = 0;
		for(int i = 0; i < 7; i++) {
			stdpos += 5;
			pos = tmp.find(":", pos);
			if(pos < stdpos) { tmp.insert(stdpos - 4, stdpos - pos, '0'); }
			pos = stdpos + 1;
		}
		tmp.insert(stdpos + 1, stdpos + 5 - tmp.size(), '0'); 
		return tmp;
	}
	return tmp;
}