#include <iostream>
#include <map>
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
			return &c1.second;
	}
	return nullptr;
}

void compare(map<string,City>& virusA, map<string,City>& virusB){
	City *initialA = findInitial(virusA),
		 *initialB = findInitial(virusB);
	
	// Lets work!
	
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
	
	int c;
	cin >> c;
	for(int cc=0; cc<c; cc++){
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
		cout << "Case #"  << cc << ": ";
		compare(virusA, virusB);
	}
}