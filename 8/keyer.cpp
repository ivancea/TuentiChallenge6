#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char** argv){
	if(argc!=2)
		return 1;
	ifstream in(argv[1]);
	ofstream out("testOutput.txt");
	
	vector<string> v;
	
	while(in){
		string t;
		getline(in,t);
		v.push_back(t);
	}
	
	
	const int N = 10;
	for(int i=N; i<v[N].size()-N; i++)
		out << v[N][i];
	for(int i=N; i<v.size()-N; i++)
		out << v[i][v[i].size()-N];
	for(int i=v.size()-N-2; i>N; i--)
		out << v[v.size()-N-1][i];
	for(int i=v.size()-N-1; i>N; i--)
		out << v[i][N];
	
}