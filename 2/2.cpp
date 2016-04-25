#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

pair<string,int> max(const map<string,int>& times, int limit){
	int max = -1;
	for(auto it:times){
		if(it.second<limit && it.second>max)
			max = it.second;
	}
	for(auto it:times){
		if(it.second==max)
			return it;
	}
}

int main(){
	ifstream corpus("corpus.txt");
	vector<string> c;
	c.reserve(35000);
	while(corpus){
		string k;
		corpus >> k;
		c.push_back(move(k));
	}
	
	int n;
	cin >> n;
	for(int i=1; i<=n; i++){
		cout << "Case #" << i << ": ";
		
		int a,b;
		cin >> a >> b;
		map<string,int> times;
		
		for(int i=a; i<=b; i++)
			++times[c[i]];
		
		int k=35000;
		for(int i=0; i<3; i++){
			auto p = max(times, k);
			k = p.second;
			cout << p.first << ' ' << p.second;
			if(i<2)
				cout << ',';
		}
		
		endl(cout);
	}
}