#include <iostream>
#include <vector>

using namespace std;

int main(){
    int c;
	cin >> c;
	for(int cc=1; cc<=c; cc++){
		cerr << "Case #" << cc << ": ";
		cout << "Case #" << cc << ": ";
		uint64_t n,m,k;
		cin >> n >> m >> k;
		if((n*m)/m != n || n*m>k || k%m!=0){
			cerr << "IMPOSSIBLE" << endl;
			cout << "IMPOSSIBLE" << endl;
		}else if(n*m==k){
			cerr << '0' << endl;
			cout << '0' << endl;
		}else{
			
			uint64_t remaining = k-n*m;
			int times = 0;
			
			uint64_t max = m;
			uint64_t r = n-1;
			
			while(remaining > 0){
				while(remaining>=max){ // TODO: while to equation. Sqrt?
					remaining -= max;
					max *= 2;
					times++;
				}
				if(remaining == 0)
					break;
				
				while(max>remaining)
					max /= 2;
				if(max!=m){
					remaining -= max;
					times++;
				}
				
			}
			cerr << times << endl;
			cout << times << endl;
		}
	}
}