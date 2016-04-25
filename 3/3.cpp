#include <iostream>
#include <vector>
#include <map>

using namespace std;


pair<string,string> split(const string& s){
	size_t a = 0, b=0;
	for(int i=0; i<s.size(); i++)
		if(s[i]!=' '){
			a = i;
			break;
		}
	b = s.find(':');
	return make_pair(s.substr(a,b-a), (s.size()<=b+2?"":s.substr(b+2)));
}

enum Code{
	Write,
	Move,
	State
};

map<string,Code> codeHelper = {{"write", Write},
					     	   {"move",  Move},
							   {"state", State}};

struct Instruction{
	Code code;
	string arg;
	
	string doIt(string& tape, int& pos){
		switch(code){
		case Write:
			if(tape.size()<=pos)
				tape += ' ';
			tape[pos] = arg[0];
			break;
		case Move:
			if(arg=="right")
				++pos;
			else
				--pos;
			break;
		case State:
			return arg;
		}
		return "";
	}
	
};

int main(){
	map<string, map<char, vector<Instruction> > > states;
	vector<string> tapes;
	
	{ // Load data context
		string actualState;
		map<char, vector<Instruction> > state;
		
		char actualChar = 0;
		vector<Instruction> actualIns;
		
		while(cin){
			string t;
			getline(cin,t);
			if(t=="---" || t=="code:")
				continue;
			if(t=="tapes:")
				break;
			auto p = split(t);
			if(p.second.size()==0){
				if(p.first[0]=='\''){
					if(actualChar!=0){
						state[actualChar] = actualIns;
					}
					actualChar = p.first[1];
					actualIns.clear();
				}else{
					if(actualState!=""){
						state[actualChar] = actualIns;
						states[actualState] = state;
					}
					actualState = p.first;
					state.clear();
				}
			}else{
				Instruction ins;
				ins.code = codeHelper[p.first];
				if(p.second[0]=='\'')
					ins.arg = p.second.substr(1,1);
				else
					ins.arg = p.second;
				actualIns.push_back(ins);
			}
		}
		state[actualChar] = actualIns;
		states[actualState] = state;
		
		while(cin){
			string t;
			getline(cin,t);
			if(t=="...")
				break;
			auto p = split(t);
			p.second[0] =
			p.second[p.second.size()-1] = ' ';
			tapes.push_back(p.second);
		}
	}
	
	for(int i=0; i<tapes.size(); i++){
		cout << "Tape #" << (i+1) << ":";
		string& tape = tapes[i];
		int pos = 1;
		
		map<char, vector<Instruction> > state = states["start"];
		
		while(true){
			char c = ' ';
			if(tape.size()>pos)
				c = tape[pos];
			vector<Instruction>& ins = state[c];
			string k;
			for(Instruction& i : ins){
				k = i.doIt(tape, pos);
			}
			if(k!=""){
				if(k=="end")
					break;
				state = states[k];
			}
		}
		if(tape[tape.size()-1]==' ')
			cout.write(tape.c_str(), tape.size()-1);
		else
			cout << tape;
		endl(cout);
		
	}
}