#include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	for(int i=1; i<=n; i++){
		cout << "Case #" << i << ": ";
		int t;
		cin >> t;
		if(t==0)
			cout << 0;
		else if(t<=4)
			cout << 1;
		else
			cout << (t-3%2==1?(t-3)/2:(t-3)/2+1);
		endl(cout);
	}
}