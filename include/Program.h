#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Command{
    string commandType;
    int* arguments;
};
struct Line{
    int number;
    Command op;
    Line(Command& c, int num): number(num), op(c) {};
};

class Program
{

    public:
        void s(int);
        void z(int);
        void t(int, int);
        void j(int, int, int);
        void init(vector<int>);
        Program();
        ~Program();
        void AddLine(Command&);
        Command Parse(string input);
        int getResult();
        friend istream& operator>>(istream&, Command&);
        int nextLine;
        vector <Line> lines;
        vector <int> regs;
    protected:
    private:
};

#endif // PROGRAM_H
