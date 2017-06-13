#include "Program.h"
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

Program::Program()
{
    //ctor
}

void Program::init(vector<int> data)
{
    for(int i = 0; i < data.size(); i++)
        regs.push_back(data[i]);
}

void Program::AddLine(Command& c)
{
    Line l(c, lines.size() + 1);
    lines.push_back(l);
}

Command Program::Parse(string input)
{
    Command c;
    if (input[0] == 's' || input[0] == 'S')
    {
        c.commandType = "s";
        c.arguments = new int [1];
        string num = input.substr(2, input.end() - input.begin() - 3);
        c.arguments[0] = stoi(num, nullptr, 10);
    } else
    if (input[0] == 'z' || input[0] == 'Z')
    {
        c.commandType = "z";
        c.arguments = new int [1];
        string num = input.substr(2, input.end() - input.begin() - 3);
        c.arguments[0] = stoi(num, nullptr, 10);
    } else
    if (input[0] == 't' || input[0] == 'T')
    {
        c.commandType = "t";
        c.arguments = new int [2];
        int iter = 0;
        while (input[iter] != ',')
            iter++;
        string num = input.substr(2, iter - 2);
        c.arguments[0] = stoi(num, nullptr, 10);
        num = input.substr(iter + 1, input.length() - iter - 1);
        c.arguments[1] = stoi(num, nullptr, 10);
    } else
    if (input[0] == 'J' || input[0] == 'j')
    {
        c.commandType = "j";
        c.arguments = new int [3];
        int iter = 0, iter1;
        while (input[iter] != ',')
            iter++;
        iter1 = iter + 1;
        while (input[iter1] != ',')
            iter1++;
        string num = input.substr(2, iter - 2);
        c.arguments[0] = stoi(num, nullptr, 10);
        num = input.substr(iter + 1, iter1 - iter - 1);
        c.arguments[1] = stoi(num, nullptr, 10);
        num = input.substr(iter1 + 1, input.length() - iter1 - 1);
        c.arguments[2] = stoi(num, nullptr, 10);
    } else
    cout << "WRONG COMMAND!" << endl;
    return c;
}

istream& operator>>(istream& in, Program& pr)
{
    string s;
    getline(in, s);
    while (s != ""){
        Command p = pr.Parse(s);
        pr.AddLine(p);
        getline(in, s);
    }
}

void Program::s(int pos)
{
    while (regs.size() <= pos)
        regs.push_back(0);
    regs[pos]++;
    nextLine++;
}

void Program::z(int pos)
{
    while (regs.size() <= pos)
        regs.push_back(0);
    regs[pos] = 0;
    nextLine++;
}

void Program::t(int src, int dest)
{
    while (regs.size() <= max(dest, src))
        regs.push_back(0);
    regs[dest] = regs[src];
    nextLine++;
}

void Program::j(int posF, int posS, int nL)
{

    while (regs.size() <= max(posF, posS))
        regs.push_back(0);
    if (regs[posF] == regs[posS])
        nextLine = nL - 1; else
        nextLine++;
}

int Program::getResult()
{
    int st = clock();
    nextLine = 0;
    while (nextLine < lines.size()) //&& clock() - st < 1000)
    {
        if (lines[nextLine].op.commandType == "s")
            s(lines[nextLine].op.arguments[0]); else
        if (lines[nextLine].op.commandType == "z")
            z(lines[nextLine].op.arguments[0]); else
        if (lines[nextLine].op.commandType == "t")
            t(lines[nextLine].op.arguments[0], lines[nextLine].op.arguments[1]); else
        if (lines[nextLine].op.commandType == "j")
            j(lines[nextLine].op.arguments[0], lines[nextLine].op.arguments[1], lines[nextLine].op.arguments[2]);
    }
    if (clock() - st < 1000)
        return regs[0];
    else {
        cout << "Your program has an error here!\n";
        return 0;
    }
}

Program::~Program()
{
    //dtor
}
