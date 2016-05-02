#include <iostream>
#include <vector>
#include <map>

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp> 

using namespace std;
using namespace boost;
using namespace boost::multiprecision;

typedef cpp_int ulong;

typedef rational<ulong> Prob;

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