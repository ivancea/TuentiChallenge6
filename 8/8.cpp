#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "sockets.cpp"

using namespace std;

vector<string> parseLabyrinth(const string& str){
	vector<string> v(7);
	istringstream ss(str);
	for(int i=0; i<7; i++)
		getline(ss, v[i]);
	return v;
}

vector<string> readFromClient(TCPClient& cl){
    string t;
    while(t.size()<8*7)
        t += cl.recv();
    cout << t << endl;
    return parseLabyrinth(t);
}

int main(){
    srand(time(0));

	TCPClient cl("52.49.91.111", 1986);

	vector<string> lab = readFromClient(cl);

    bool running = true;
    sf::RenderWindow window;


    window.create(sf::VideoMode(500,500), "Challenge 8: Labyrinth", sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(60);

    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glOrtho(0,window.getSize().x, window.getSize().y,0,0,1);
    glMatrixMode(GL_PROJECTION);

    while(running && window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            switch(ev.type){
            case sf::Event::Closed:
                running = false;
                break;
            case sf::Event::KeyPressed:
            {
                bool readClient = true;
                switch(ev.key.code){
                case sf::Keyboard::W:
                    cl.send("u\n");
                break;
                case sf::Keyboard::D:
                    cl.send("r\n");
                break;
                case sf::Keyboard::S:
                    cl.send("d\n");
                break;
                case sf::Keyboard::A:
                    cl.send("l\n");
                break;
                default:
                    readClient = false;
                }
                if(readClient){
                    lab = readFromClient(cl);
                }
                break;
            }
            default:
                break;
            }
        }

        window.clear();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        for(int i=0; i<lab.size(); i++){
            for(int j=0; j<lab[i].size(); j++){
                switch(lab[i][j]){
                case '#': glColor3ub(0,0,0); break;
                case ' ': glColor3ub(255,255,255); break;
                default:  glColor3ub(255,0,0);
                }
                int n = 500/7;
                glBegin(GL_POLYGON);
                    glVertex2i(j*n, i*n);
                    glVertex2i((j+1)*n, i*n);
                    glVertex2i((j+1)*n, (i+1)*n);
                    glVertex2i(j*n, (i+1)*n);
                glEnd();
            }
        }

        window.display();

        this_thread::sleep_for(chrono::milliseconds(10));
    }
    window.close();
}
