#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct City{
	string name;
	vector<City*> connections;
};

City* findInitial(const map<string,City>& cities){
	for(auto& c1:cities){
		bool good = true;
		for(auto& c2:cities){
			if(&c1.second==&c2.second)
				continue;
			for(City* c:c2.second.connections){
				if(c==&c1.second){
					good = false;
					break;
				}
			}
			if(!good)
				break;
		}
		if(good)
			return (City*)&c1.second;
	}
	return nullptr;
}

void sort(map<string,City>& virus){
	for(pair<const string,City>& cc:virus){
		City& c = cc.second;
		stable_sort(c.connections.begin(), c.connections.end(), [](const City* a, const City* b)->bool{return a->name < b->name;});
		stable_sort(c.connections.begin(), c.connections.end(), [](const City* a, const City* b)->bool{return a->connections.size() < b->connections.size();});
	}
}

map<string,string> compare(City* virusA, City* virusB){
	map<string,string> t;
	if(virusA->connections.size() != virusB->connections.size())
		return t;
	
	set<int> okA, okB;
	
	for(int j=0; j<virusB->connections.size(); j++){
		if(okB.find(j)!=okB.end())
			continue;
		if(okA.size() == virusA->connections.size())
			break;
		bool ok = false;
		for(int i=0; i<virusA->connections.size(); i++){
			if(okA.find(i)!=okA.end())
				continue;
			if(virusA->connections[i]->connections.size() < virusB->connections[j]->connections.size())
				continue;
			else if(virusA->connections[i]->connections.size() > virusB->connections[j]->connections.size())
				break;
			
			map<string,string> k = compare(virusA->connections[i], virusB->connections[j]);
			if(k.size()>0){
				t.insert(k.begin(), k.end());
				okA.insert(i);
				okB.insert(j);
				ok = true;
				break;
			}
		}
		if(!ok)
			break;
	}
	if(okA.size() != virusA->connections.size())
		return map<string,string>();
	
	t[virusA->name] = virusB->name;
	return t;
}

void compareAndCout(map<string,City>& virusA, map<string,City>& virusB){
	City *initialA = findInitial(virusA),
		 *initialB = findInitial(virusB);
		 
	map<string,string> cities = compare(initialA, initialB);
	
	if(cities.size()==0){
		cout << " NO" << endl;
	}else{
		for(auto it:cities)
			cout << ' ' << it.first << '/' << it.second;
		cout << endl;
	}
}

int main(){
	map<string,City> virusA;
    int n;
	cin >> n;
	for(int i=0; i<n-1; i++){
		string t;
		
		cin >> t;
		City& s = virusA[t];
		s.name = t;
		
		cin >> t;
		City& d = virusA[t];
		d.name = t;
		
		s.connections.push_back(&d);
	}
	sort(virusA);
	
	int c;
	cin >> c;
	for(int cc=1; cc<=c; cc++){
		map<string,City> virusB;
		for(int i=0; i<n-1; i++){
			string t;
			
			cin >> t;
			City& s = virusB[t];
			s.name = t;
			
			cin >> t;
			City& d = virusB[t];
			d.name = t;
			
			s.connections.push_back(&d);
		}
		sort(virusB);
		cout << "Case #"  << cc << ":";
		compareAndCout(virusA, virusB);
	}
}