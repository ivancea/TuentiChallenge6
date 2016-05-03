#include <iostream>
#include <thread>

#include "sockets.cpp"

using namespace std;

void fn(TCPClient& cl){
	while(cl.isConnected()){
		string t;
		getline(cin,t);
		cl.send(t+"\n");
	}
}

int main(){
	TCPClient cl("52.49.91.111", 9999);
	
	thread th(fn, ref(cl));
	th.detach();
	
	while(cl.isConnected()){
		string t;
		t = cl.recv();
		if(t!=""){
			cout << t << endl;
		}
	}
}