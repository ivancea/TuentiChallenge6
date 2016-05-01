#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef unsigned long long ulong;

ulong gcd(ulong a, ulong b){
	while(b!=0){
		ulong t = b;
		b = a%b;
		a = t;
	}
	return a;
}

struct Prob{
	ulong num, denom;
	
	Prob():num(0),denom(1){}
	
	Prob operator*(const Prob& p) const{
		Prob t;
		t.num = num * p.num;
		t.denom = denom * p.denom;
		t.reduce();
		return t;
	}
	
	void set(ulong _num, ulong _denom){
		num = _num;
		denom = _denom;
		reduce();
	}
	
	double asDouble() const{
		return num/denom;
	}
	
	void reduce(){
		ulong t = gcd(denom,num);
		if(t>1){
			denom /= t;
			num /= t;
			cerr << num << "/" << denom << endl;
		}
	}
};

vector<Prob> calc(const vector< map<int, Prob> >& probs, int initial, int changes){
	vector<Prob> v(probs.size());
	v[initial].set(1,1); // Initial prob
	
	while(changes-->0){
		vector<Prob> t(probs.size());
		/*for(auto it:v){
			cerr << it.num << "/" << it.denom << endl;
		}
		cerr << endl;*/
		for(int i=0; i<v.size(); i++){
			if(v[i].num>0){
				for(auto it:probs[i]){
					t[it.first] = v[i] * it.second;
				}
			}
		}
		v = t;
	}
	
	return v;
}

int main(){
	int seats, probNumber;
	cin >> seats >> probNumber;
	vector< map<int, Prob> > probs(seats);
	for(int i=0; i<probNumber; i++){
		int a,b;
		string t;
		cin >> a >> b >> t;
		probs[a][b].set(stoi(t.substr(0, t.size()-4)), 100);
	}
	int q;
	cin >> q;
	for(int qq=1; qq<=q; qq++){ // Case #q: Chair: n Last digits: a/b
		int initial, changes;
		cin >> initial >> changes;
		vector<Prob> t = calc(probs, initial, changes);
		int maxIndex = -1;
		double max = 0;
		for(int i=t.size()-1; i>=0; i--){
			if(t[i].asDouble()>max){
				max = t[i].asDouble();
				maxIndex = i;
			}
		}
		if(maxIndex==-1){
			cout << "Case #" << qq << ": ERROR" << endl;
		}else{
			cout << "Case #" << qq << ": Chair: " << maxIndex << " Last digits: " << t[maxIndex].num%10 << '/' << t[maxIndex].denom%10 << endl;
		}
	}
}