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

bool compare(City* virusA, City* virusB){
	if(virusA->connections.size() != virusB->connections.size())
		return false;
	
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
			
			if(compare(virusA->connections[i], virusB->connections[j])){
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
		return false;
	
	return true;
}

int countAncestors(map<string,City>& virus, City* initial){
	int n = 0;
	string t = initial->name;
	while(true){
		bool found = false;
		for(auto it:virus){
			for(City* c:it.second.connections){
				if(c->name==t){
					n++;
					t = it.first;
					found = true;
					break;
				}
			}
			if(found)
				break;
		}
		if(!found)
			break;
	}
	return n;
}

/*
 OK   Both cities have infected the same number of cities.
 OK   Both cities have the same number of jumps to the first city where the virus started to spread.
 OK   Ancestors of both cities may not be equivalent.
 OK   Both cities will have the same spreading (paths) to the last cities where the pandemic was ongoing.
*/
bool areEquivalent(map<string,City>& virusA, map<string,City>& virusB,
				   City* cityA, City* cityB){
	if(cityA->connections.size()!=cityB->connections.size())
		return false;
	if(countAncestors(virusA, cityA)
	!= countAncestors(virusB, cityB))
		return false;
	if(!compare(cityA, cityB))
		return false;
	
	return true;
}

void compareAndCout(map<string,City>& virusA, map<string,City>& virusB){
	City *initialA = findInitial(virusA),
		 *initialB = findInitial(virusB);
	
	
	if(compare(initialA, initialB)){
		map<string,string> cities;
		set<string> seenA, seenB;
		for(auto it:virusA){
			if(seenA.find(it.first) != seenA.end())
				continue;
			for(auto it2:virusB){
				if(seenB.find(it2.first) != seenB.end())
					continue;
				if(areEquivalent(virusA, virusB, &it.second, &it2.second)){
					seenA.insert(it.first);
					seenB.insert(it2.first);
					cities[it.first] = it2.first;
					break;
				}
			}
		}
		for(auto it:cities)
			cout << ' ' << it.first << '/' << it.second;
		cout << endl;
	}else
		cout << " NO" << endl;
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