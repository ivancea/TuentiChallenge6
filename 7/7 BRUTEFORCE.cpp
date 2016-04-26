#include <iostream>
#include <vector>

using namespace std;

void convertString(string& str){
	for(char& c:str){
		if('a' <= c && c <= 'z')
			c = -(c-'a'+1);
		else if(c=='.')
			c = 0;
		else
			c = c-'A'+1;
	}
}

int getMaxSum(vector<string>& mat){
	/// INFINITY (horizontal) or 0?
	int max = 0;
	for(int i=0; i<mat.size(); i++){
		int sum = 0;
		for(int j=0; j<mat[i].size(); j++){
			if(mat[i][j]>max)
				max = mat[i][j];
			sum += mat[i][j];
		}
		if(sum>0)
			return -1;
	}
	/// INFINITY (vertical)
	for(int i=0; i<mat[0].size(); i++){
		int sum = 0;
		for(int j=0; j<mat.size(); j++)
			sum += mat[j][i];
		if(sum>0)
			return -1;
	}
	if(max==0)
		return 0;
	
	/// BRUTEFORCE
	
	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[i].size(); j++){ // Starting at each number
		
			for(int l=1; l<mat[0].size(); l++){ // For each sub-matriz size
				int maxSum = 0;
				for(int n=0; n<mat.size(); n++){
					for(int m=0; m<l; m++){ // Sum sub-matrix
						maxSum += mat[(i+n)%mat.size()][(j+m)%mat[0].size()];
					}
					if(maxSum>max) // If sub-matrix since here sums greater than max, assign
						max = maxSum;
				}
			}
			
		}
	}
	
	return max;
}

int main(){
	string t;
	int c;
	getline(cin,t);
	c = stoi(t);
	for(int cc=1; cc<=c; cc++){
		getline(cin,t);
		
		int n,m;
		
		n = t.find(' ');
		m = stoi(t.substr(n+1));
		n = stoi(t.substr(0,n));
		
		vector<string> mat(n);
		
		for(int i=0; i<n; i++){
			getline(cin, mat[i]);
			convertString(mat[i]);
		}
		cerr << "Case #" << cc << ": ";
		cout << "Case #" << cc << ": ";
		int k = getMaxSum(mat);
		if(k==-1)
			cout << "INFINITY";
		else
			cout << k;
		if(k==-1)
			cerr << "INFINITY";
		else
			cerr << k;
		endl(cerr);
		endl(cout);
	}
}