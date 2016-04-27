#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
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
    while(t.size()<8*7){
        t += cl.recv();
    }
    cout << t << endl;
    return parseLabyrinth(t);
}

void moveLab(TCPClient& cl, vector<string>& lab, sf::Vector2i& pos){
    const int N = 5;
    if(pos.x <= 2){
        lab.insert(lab.begin(), N, string(lab[0].size(), '.'));
        pos.x += N;
    }else if(pos.x >= lab.size()-3){
        for(int i=0; i<N; i++)
            lab.push_back(string(lab[0].size(), '.'));
    }
    if(pos.y <= 2){
        for(int i=0; i<lab.size(); i++)
            lab[i] = string(N,'.')+lab[i];
        pos.y += N;
    }else if(pos.y >= lab[0].size()-3){
        for(int i=0; i<lab.size(); i++)
            lab[i] = lab[i]+string(N,'.');
    }

    vector<string> v = readFromClient(cl);
    for(int i=0; i<v.size(); i++)
        for(int j=0; j<v[i].size(); j++)
            lab[pos.x-3+i][pos.y-3+j] = v[i][j];
}

bool canMove(vector<string>& lab, sf::Vector2i& pos, int dir){
    switch(dir){
    case 0:
        if(lab[pos.x-1][pos.y]==' ')
            return true;
    case 1:
        if(lab[pos.x][pos.y+1]==' ')
            return true;
    case 2:
        if(lab[pos.x+1][pos.y]==' ')
            return true;
    case 3:
        if(lab[pos.x][pos.y-1]==' ')
            return true;
    }
    return false;
}

bool move(TCPClient& cl, vector<string>& lab, sf::Vector2i& pos, int dir){
    bool moved = false;
    switch(dir){
    case 0:
        if(lab[pos.x-1][pos.y]==' '){
            pos.x--;
            cl.send("u\n");
            moved = true;
        }
        break;
    case 1:
        if(lab[pos.x][pos.y+1]==' '){
            pos.y++;
            cl.send("r\n");
            moved = true;
        }
        break;
    case 2:
        if(lab[pos.x+1][pos.y]==' '){
            pos.x++;
            cl.send("d\n");
            moved = true;
        }
        break;
    case 3:
        if(lab[pos.x][pos.y-1]==' '){
            pos.y--;
            cl.send("l\n");
            moved = true;
        }
        break;
    }
    return moved;
}

int main(){
    srand(time(0));

    map<sf::Keyboard::Key, bool> keys;

	TCPClient cl("52.49.91.111", 1986);

	vector<string> lab(100, string(100, '.'));
	sf::Vector2i pos(lab.size()/2, lab[0].size()/2);
	int dir = 0;

	moveLab(cl, lab, pos);

    bool running = true;
    sf::RenderWindow window;


    window.create(sf::VideoMode(800,800), "Challenge 8: Labyrinth", sf::Style::Titlebar|sf::Style::Close);
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
                keys[ev.key.code] = true;
                if(ev.key.code == sf::Keyboard::Return){
                    ofstream out("labOutput.txt", ios::trunc);
                    for(string& s:lab)
                        out << s << '\n';
                    out.close();
                }
                break;
            case sf::Event::KeyReleased:
                keys[ev.key.code] = false;
                break;
            default:
                break;
            }
        }

        bool readClient = false;
        if(keys[sf::Keyboard::W] && move(cl, lab, pos, 0)){
            readClient = true;
        }else if(keys[sf::Keyboard::D] && move(cl, lab, pos, 1)){
            readClient = true;
        }else if(keys[sf::Keyboard::S] && move(cl, lab, pos, 2)){
            readClient = true;
        }else if(keys[sf::Keyboard::A] && move(cl, lab, pos, 3)){
            readClient = true;
        }

        { /// BRUTE-FORCE IA
            while(!readClient){
                switch(dir){
                case 0:
                    if(move(cl, lab, pos, 0)){
                        dir = 1;
                        readClient = true;
                    }else if(move(cl, lab, pos, 3)){
                        readClient = true;
                    }else dir = 3;
                    break;
                case 1:
                    if(move(cl, lab, pos, 1)){
                        dir = 2;
                        readClient = true;
                    }else if(move(cl, lab, pos, 0)){
                        readClient = true;
                    }else dir = 0;
                    break;
                case 2:
                    if(move(cl, lab, pos, 2)){
                        dir = 3;
                        readClient = true;
                    }else if(move(cl, lab, pos, 1)){
                        readClient = true;
                    }else dir = 1;
                    break;
                case 3:
                    if(move(cl, lab, pos, 3)){
                        dir = 0;
                        readClient = true;
                    }else if(move(cl, lab, pos, 2)){
                        readClient = true;
                    }else dir = 2;
                    break;
                }
            }
        }

        if(readClient){
            moveLab(cl, lab, pos);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        for(int i=0; i<lab.size(); i++){
            for(int j=0; j<lab[i].size(); j++){
                switch(lab[i][j]){
                case 'x': glColor3ub(0,0,255); break;
                case '#': glColor3ub(0,0,0); break;
                case '.': glColor3ub(255,0,0); break;
                case ' ': glColor3ub(255,255,255); break;
                default:  glColor3ub(0,255,0);
                }
                int n = window.getSize().x/lab.size(),
                    m = window.getSize().y/lab[i].size();
                glBegin(GL_POLYGON);
                    glVertex2i(j*m, i*n);
                    glVertex2i((j+1)*m, i*n);
                    glVertex2i((j+1)*m, (i+1)*n);
                    glVertex2i(j*m, (i+1)*n);
                glEnd();
            }
        }

        window.display();

        this_thread::sleep_for(chrono::milliseconds(1));
    }
    window.close();
}
