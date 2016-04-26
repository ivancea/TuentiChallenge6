#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "sockets.cpp"

using namespace std;

void thFunc(TCPClient& cl){
	while(cl.isConnected()){
		string t;
		getline(cin,t);
		cl.send(t+'\n');
	}
}

int main(){
	TCPClient cl("52.49.91.111", 1986);
	
	thread th(thFunc, ref(cl));
	th.detach();
	
	while(cl.isConnected()){
		string t=cl.recv();
		if(t!=""){
			cout << t;
		}
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	
	cout << "#ENDED#" << endl;
	cin.get();
	
}