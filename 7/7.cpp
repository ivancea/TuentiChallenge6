#include <iostream>
#include <vector>

using namespace std;

vector<int> convertString(string& str){
	vector<int> v(str.size(),0);
	for(int i=0; i<str.size(); i++){
		char& c = str[i];
		if('a' <= c && c <= 'z')
			v[i] = -(c-'a'+1);
		else if(c!='.')
			v[i] = c-'A'+1;
	}
	return v;
}

void transformMatrix(vector< vector<int> >& mat){ // [a b c] -> [a a+b a+b+c]
	for(vector<int>& v:mat){
		for(int i=1; i<v.size(); i++)
			v[i] += v[i-1];
	}
}

inline int getSum(const vector<int>& mat, int a, int b){
	int ret = 0;
	if(a<=b){
		ret = mat[b];
		if(a>0)
			ret -= mat[a-1];
	}else{
		ret = mat[mat.size()-1];
		if(a>0)
			ret -= mat[a-1];
		ret += mat[b];
	}
	return ret;
}

int getMaxSum(vector< vector<int> >& mat){
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
		
	transformMatrix(mat);
	
	/// BRUTEFORCE
	
	for(int i=0; i<mat.size(); i++){
		for(int j=0; j<mat[i].size(); j++){ // Starting at each number
		
			for(int l=0; l<mat[0].size()-1; l++){ // For each sub-matriz size
				int maxSum = 0;
				for(int n=0; n<mat.size(); n++){
					maxSum += getSum(mat[(i+n)%mat.size()], j, (j+l)%mat[0].size());
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
		
		vector< vector<int> > mat(n);
		
		for(int i=0; i<n; i++){
			getline(cin, t);
			mat[i] = convertString(t);
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