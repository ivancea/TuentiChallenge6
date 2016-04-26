#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>

#include "sockets.cpp"

using namespace std;

string findWord(string& txt){
	istringstream ss(txt);
	string t;
	
	for(int i=0; i<10; i++)
		getline(ss, t);
	
	for(int i=t.size()-1; i>=0; i--)
		if(t[i]==' ')
			t.erase(i,1);
	return t;
}

void logic(TCPClient& cl, map<size_t, vector<string> >& words, string& word, string& characters){
	vector<int> times('Z'-'A'+1, 0);
	for(const string& s : words[word.size()]) {
		bool able = true;
		for(int i=0; i<word.size(); i++)
			if(word[i]!='_'){
				if(word[i] != s[i]){
					able = false;
					break;
				}
			}else if(characters.find(s[i])!=string::npos){
				able = false;
				break;
			}
		if(!able)
			continue;
		set<char> rep;
		for(char c:s){
			rep.insert(c);
		}
		for(char c:rep)
			++times[c-'A'];
	}
	
	for(char c : characters)
		times[c-'A'] = 0;
	
	int max = -1;
	int pos = -1;
	for(int i=0; i<times.size(); i++)
		if(times[i]>max){
			max=times[i];
			pos = i;
		}
	if(pos==-1){
		cout << "\n\nERROR\n\n";
	}else{
		cout << (char)(pos+'A') << endl;
		string st(2,'\n');
		st[0] = (char)(pos+'A');
		cl.send(st);
		characters += (char)(pos+'A');
	}
}


int main(){
	ifstream wordsFile("words.txt");
	map<size_t, vector<string> > words;
	while(wordsFile){
		string t;
		wordsFile >> t;
		if(t.size()>0)
			words[t.size()].push_back(t);
	}
	
	TCPClient cl("52.49.91.111", 9988);
	
	cl.send("\n");
	
	string t;
	string txt; // For read all input from server
	string characters; // Characters used
	string word; // Word (_A_Z)
	while(true){
		t=cl.recv();
		if(t!=""){
			cout << t;
			txt += t;
			if(txt.size()>=2){
				if(txt.substr(txt.size()-2)=="> "){
					word = findWord(txt);
					logic(cl, words, word, characters);
				}else if(txt.substr(txt.size()-3)=="..."){ // Finished
						cout << "\nNEXT ROUND" << endl;
						cl.send("\n");
						characters.clear();
				}
				txt.clear();
			}
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	
	cout << "#ENDED#" << endl;
	cin.get();
	
}