#include <iostream>
#include <fstream>
#include <string>
#include "LL.h"
using namespace std;

class District {
public:
    string dist;
    int pt1, pt2, pt3;
    District() : dist(""), pt1(0), pt2(0), pt3(0) {}
    District(string name) :dist(name) {}
    District(string name, int p1, int p2, int p3) :dist(name), pt1(p1), pt2(p2), pt3(p3) {}
    void compare();

    bool operator==(District& dis)
    {
        return dist == dis.dist;
    }
};

void District::compare() {
    if (pt1 > pt2) {
        if (pt1 > pt3)
            cout << dist << " - " << pt1 << " won.";
        else
            cout << dist << " - " << pt3 << " won.";
    }
    else {
        if(pt2>pt3)
            cout << dist << " - " << pt2 << " won.";
        else
            cout << dist << " - " << pt3 << " won.";
    }
}

class City {
protected:
    string city;
    int total1, total2, total3;
public:
    LL<District>* vote;
    City();
    void assign(string c, int t1, int t2, int t3) {
        city = c;
        total1 += t1;
        total2 += t2;
        total3 += t3;
    }
    
    string getCity() { return city; }

    void cityWon() {
        if (total1 > total2) {
            if (total1 > total3)
                cout << city << " - " << total1 << " won.";
            else
                cout << city << " - " << total3 << " won.";
        }
        else {
            if (total2 > total3)
                cout << city << " - " << total2 << " won.";
            else
                cout << city << " - " << total3 << " won.";
        }
    }

    void compare() {
        if (total1 > total2) {
            if (total1 > total3)
                cout << "party1 won with " << total1 << " votes" << endl;
            else
                cout << "party2 won with " << total1 << " votes" << endl;
        }
        else {
            if (total2 > total3)
                cout << "party2 won with " << total1 << " votes" << endl;
            else
                cout << "party3 won with " << total1 << " votes" << endl;
        }
    }
};

int main() {
    string comm, c, d, city, district;
    int party1, party2, party3;
    ifstream vote("vote.txt");
    City cities[3];
    node<District>* disNode;
    while (!vote.eof()) {  
        vote >> city >> district >> party1 >> party2 >> party3;

        if (city == "Ankara") {
            cities[0].assign(city, party1, party2, party3);
            District dis(district, party1, party2, party3);
            cities[0].vote->insertLast(dis);
        }
        else if(city=="İstanbul") {
            cities[1].assign(city, party1, party2, party3);
            District dis(district, party1, party2, party3);
            cities[1].vote->insertLast(dis);
        }
        else if(city=="İzmir") {
            cities[2].assign(city, party1, party2, party3);
            District dis(district, party1, party2, party3);
            cities[2].vote->insertLast(dis);
        }

    }

    do {
        cout << " List | District | City | Quit " << endl;
        cout << "Enter your choice of action: ";
        cin >> comm;

        if (comm == "List") {
            cout << "Enter city name: ";
            cin >> c;
            cout << "City: " << c;
            
            if (c == "Ankara")
                cout << cities[0].vote;
            else if (c == "İstanbul")
                cout << cities[1].vote;
            else if (c == "İzmir")
                cout << cities[2].vote;
        }
        else if (comm == "District") {
            cout << "Enter district name: ";
            cin >> d;
            District dis(d);
            for (int i = 0; i < 4; i++) {
                disNode = cities[i].vote->search(dis);
                if (disNode != NULL)
                    cout << "In " << d << "-" << cities[i - 1].getCity() << " " << cities[i - 1].vote;
            }            
        }
        else if (comm == "City") {
            cout << "Enter city name: ";
            cin >> c;
            if (c == "Ankara")
                cities[0].compare();
            else if (c == "İstanbul")
                cities[1].compare();
            else if (c == "İzmir")
                cities[2].compare();
        }
    } while (comm != "Quit");
}
