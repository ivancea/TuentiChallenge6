#include <iostream>
#include <vector>

using namespace std;

int main(){
    int c;
	cin >> c;
	for(int cc=1; cc<=c; cc++){
		cout << "Case #" << cc << ": ";
		uint64_t n,m,k;
		cin >> n >> m >> k;
		if((n*m)/m != n || n*m>k){
			cout << "IMPOSSIBLE" << endl;
		}else if(n*m==k){
			cout << "0" << endl;
		}else{
			// TODO
			cout << "UNKNOWN" << endl;
		}
	}
}