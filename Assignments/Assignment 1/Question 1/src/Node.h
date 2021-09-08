#include<string>
using namespace std;

class Node
{
    public:
    string current;
    Node *next;

    Node(string token);
};