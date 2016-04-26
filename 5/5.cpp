#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>

#include "sockets.cpp"

using namespace std;

string findWord(string& txt){
	size_t p1 = txt.find('_');
	size_t p2 = txt.find('\n', p1);
	string t = txt.substr(p1, p2-p1);
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
			if(word[i]!='_' && word[i] != s[i]){
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
		cl.send((char)(pos+'A') + "\n");
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
			if(txt.size()>=2 && txt.substr(txt.size()-2)=="> "){
				word = findWord(txt);
				if(word.find('_')==string::npos){ // Finished
					cout << endl;
					cl.send("\n");
					characters.clear();
				}else{
					logic(cl, words, word, characters);
				}
				txt.clear();
			}
		}
	}
	
	cout << "#ENDED#" << endl;
	cin.get();
	
}