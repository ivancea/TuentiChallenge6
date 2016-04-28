#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct City{
	string name;
	vector<City*> connections;
	
	bool operator<(const City& c){
		return name<c.name;
	}
	bool operator==(const City& c){
		return name==c.name;
	}
	bool operator!=(const City& c){
		return name!=c.name;
	}
}

void compare(set<City>& virusA, set<City>& virusB){
	City* initialA = findInitial(virusA),
		  initialB = findInitial(virusB);
	
	// Lets work!
	
}

City* findInitial(const set<City>& cities){
	for(const City& c1:cities){
		bool good = true;
		for(const City& c2:cities){
			if(&c1==&c2)
				continue;
			for(City* c:c2.connections){
				if(c==&c1){
					good = false;
					break;
				}
			}
			if(!good)
				break;
		}
		if(good)
			return &c1;
	}
	return nullptr;
}

int main(){
	set<City> virusA;
    int n;
	cin >> n;
	for(int i=0; i<n-1; i++){
		string t;
		
		cin >> t;
		City& s = virusA[t];
		s->name = t;
		
		cin >> t;
		City& d = virusA[t];
		d->name = t;
		
		s.connections.push_back(&d);
	}
	
	int c;
	cin >> c;
	for(int cc=0; cc<c; cc++){
		set<City> virusB;
		for(int i=0; i<n-1; i++){
			string t;
			
			cin >> t;
			City& s = virusB[t];
			s->name = t;
			
			cin >> t;
			City& d = virusB[t];
			d->name = t;
			
			s.connections.push_back(&d);
		}
		cout << "Case #" + cc + ": ";
		compare(virusA, virusB);
	}
}