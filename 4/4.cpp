#include <iostream>
#include <vector>

using namespace std;

char getValue(const string& s){
	if(s=="R") return 1;
	if(s=="RU") return 2;
	if(s=="RD") return 3;
	if(s=="L") return 4;
	if(s=="LU") return 5;
	if(s=="LD") return 6;
	if(s=="U") return 7;
	if(s=="D") return 8;
	if(s=="K") return 9;
	if(s=="P") return 10;
}

vector<char> parseMoves(const string& str){
	vector<char> v;
	size_t p1=0,
		   p2=0;
	do{
		p2=str.find('-',p1);
		if(p2==string::npos)
			v.push_back(getValue(str.substr(p1)));
		else
			v.push_back(getValue(str.substr(p1,p2-p1)));
		p1 = p2+1;
	}while(p2!=string::npos);
	return v;
	
}

const vector< vector<char> > MOVES = {parseMoves("L-LD-D-RD-R-P"),
									  parseMoves("R-RD-D-LD-L-K"),
									  parseMoves("D-RD-R-P"),
									  parseMoves("R-D-RD-P"),
									  parseMoves("D-LD-L-K")};

int main(){
    string t;
	getline(cin,t);
	int n = stoi(t);
	for(int i=1; i<=n; i++){
		cout << "Case #" << i << ": ";
		getline(cin,t);
		vector<char> v = parseMoves(t);
		int count = 0;
		for(int i=0; i<v.size(); i++){
			bool add = false;
			for(int j=0; j<MOVES.size(); j++){
				int k = 0;
				for(; k<MOVES[j].size(); k++)
					if(i+k>=v.size() || v[i+k] != MOVES[j][k])
						break;
				if(MOVES[j].size()-1==k){
					if(i+k < v.size() && v[i+k]>=9)
						i += k;
					add = true;
					break;
				}else if(MOVES[j].size()==k){
					i += MOVES[j].size()-1;
					break;
				}
			}
			count += add;
		}
		cout << count << '\n';
	}
	flush(cout);
}