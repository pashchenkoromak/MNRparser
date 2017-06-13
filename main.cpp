#include <iostream>
#include <fstream>
#include <string>
#include "Program.h"

using namespace std;

int main()
{
    Command a;
    Program p;
    ifstream fin("max.txt");

    string s;
    do{
        getline(fin, s);
        a = p.Parse(s);
        p.AddLine(a);
    } while (!fin.eof());

    int k;
    vector<int> data;
    int N;
    cout << "Put here count of arguments:\n";
    cin >> N;
    cout << "Put here Natural arguments:\n";
    for(int i = 0; i < N; i++)
    {
        cin >> k;
        data.push_back(k);
    }
    p.init(data);
    cout << p.getResult();
    return 0;
}
