#include <iostream>
#include <vector>
#include <map>

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp> 

using namespace std;
using namespace boost;
using namespace boost::multiprecision;

typedef cpp_int ulong; // unsigned long long causes overflow

ulong gcd(ulong a, ulong b){
	while(b!=0){
		ulong t = b;
		b = a%b;
		a = t;
	}
	return a;
}

typedef rational<ulong> Prob; // Fast fix
/*struct Prob{
	ulong num, denom;
	
	Prob():num(0),denom(1){}
	
	Prob operator+(const Prob& p) const{
		Prob t1(p),
			 t2(*this);
		ulong k1 = t1.denom,
			  k2 = t2.denom;
		
		t1.num *= k2;
		t1.denom *= k2;
		t2.num *= k1;
		t2.denom *= k1;
		
		t1.num += t2.num;
		
		t1.reduce();
		return t1;
	}
	
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
		}
	}
};*/

vector<Prob> calc(const vector< map<int, Prob> >& probs, int initial, int changes){
	vector<Prob> v(probs.size());
	v[initial].assign(1,1); // Initial prob
	
	while(changes-->0){
		vector<Prob> t(probs.size());
		for(int i=0; i<v.size(); i++){
			if(v[i].numerator()>0){
				for(auto it:probs[i]){
					t[it.first] = t[it.first] + v[i]*it.second;
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
		probs[a][b].assign(stoi(t.substr(0, t.size()-4)), 100);
	}
	int q;
	cin >> q;
	for(int qq=1; qq<=q; qq++){ // Case #q: Chair: n Last digits: a/b
		int initial, changes;
		cin >> initial >> changes;
		cerr << "Case #" << qq << ": " << initial << " - " << changes << endl;
		vector<Prob> t = calc(probs, initial, changes);
		int maxIndex = -1;
		Prob max;
		max.assign(-1,1);
		for(int i=t.size()-1; i>=0; i--){
			if(t[i]>max){
				max = t[i];
				maxIndex = i;
			}
		}
		if(maxIndex==-1){
			cout << "Case #" << qq << ": ERROR" << endl;
		}else{
			cout << "Case #" << qq << ": Chair: " << maxIndex << " Last digits: " << t[maxIndex].numerator()%10 << '/' << t[maxIndex].denominator()%10 << endl;
		}
	}
}