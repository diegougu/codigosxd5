#include <iostream>
#include <forward_list>
#include <vector>
#include <stack>
#include <unordered_set>
#include <string>
#include <queue> 
using namespace std;
struct CEdge
{
    CEdge(int idn = -1, int v = 0)
    {
        id_node = idn;
        value = v;
    }
    int id_node;
    int value;
};

struct CNode
{
    CNode(int id = -1, string v = "")
    {
        id_node = id;
        value = v;
    }
    int id_node;
    string value;
    forward_list<CEdge> edges;
};

class CGraph
{
public:
    void InsNode(string v);
    void InsEdge(int idn1, int idn2, int v);
    void Print();
    void BP(string ini, string fin);
    void BA(string ini, string fin);
    vector<CNode> nodes;
private:
    void PrintIteStack(stack<CNode> s);
    void PrintIteQueue(queue<CNode> q);
};

void CGraph::InsNode(string v)
{
    CNode n(nodes.size(), v);
    nodes.push_back(n);
}

void CGraph::InsEdge(int idn1, int idn2, int v)
{
    CEdge e(idn2, v);
    CEdge e2(idn1, v);

    nodes[idn1].edges.push_front(e);
    nodes[idn2].edges.push_front(e2);

}

void CGraph::BA(string ini, string fin) {
    int i = 0;
    for (; i < nodes.size() && nodes[i].value != ini; i++);
    queue<CNode> q;
    unordered_set<int> visited;
    q.push(nodes[i]);

    while (!q.empty() && q.front().value != fin) {
        PrintIteQueue(q);
        auto e = q.front().edges;
        visited.insert(q.front().id_node);
        q.pop();
        e.reverse();
        for (auto n : e) {
            auto ite = visited.find(nodes[n.id_node].id_node);
            if (ite == visited.end()) {
                q.push(nodes[n.id_node]);
            }
        }
    }
    PrintIteQueue(q);
}

void CGraph::BP(string ini, string fin) {
    int i = 0;
    for (; i < nodes.size() && nodes[i].value != ini; i++);
    stack<CNode> s;
    unordered_set<int> visited;
    s.push(nodes[i]);

    while (!s.empty() && s.top().value != fin) {
        PrintIteStack(s);
        auto e = s.top().edges;
        visited.insert(s.top().id_node);
        s.pop();
        for (auto n : e) {
            auto ite = visited.find(nodes[n.id_node].id_node);
            if (ite == visited.end()) {
                s.push(nodes[n.id_node]);
            }
        }
    }
    PrintIteStack(s);
}

void CGraph::PrintIteStack(stack<CNode> s) {
    stack<CNode> p = s;
    while (!p.empty()) {
        cout << p.top().value << " ";
        p.pop();
    }
    cout << endl;
}

void CGraph::PrintIteQueue(queue<CNode> q) {
    queue<CNode> p = q;
    while (!p.empty()) {
        cout << p.front().value << " ";
        p.pop();
    }
    cout << endl;
}

void CGraph::Print()
{
    for (auto n : nodes)
    {
        cout << n.value << " ";
        for (auto e : n.edges)
            cout << "->" << nodes[e.id_node].value << " ";
        cout << "\n";
    }
}


int main() {
    CGraph g;

    g.InsNode("1");   // 0
    g.InsNode("2");   // 1
    g.InsNode("3");   // 2
    g.InsNode("4");   // 3
    g.InsNode("5");   // 4
    g.InsNode("6");   // 5
    g.InsNode("7");   // 6
    g.InsNode("8");   // 7
    g.InsNode("8");   // 8 (nodo repetido en valor pero diferente id)
    g.InsNode("10");  // 9
    g.InsNode("11");  // 10
    g.InsNode("12");  // 11
    g.InsNode("13");  // 12
    g.InsNode("14");  // 13
    g.InsNode("15");  // 14
    g.InsNode("16");  // 15
    g.InsNode("17");  // 16
    g.InsNode("18");  // 17
    g.InsNode("19");  // 18
    g.InsNode("20");  // 19
    g.InsNode("21");  // 20
    g.InsNode("22");  // 21

    g.InsEdge(0, 1, 1);  // 1 - 2
    g.InsEdge(0, 2, 1);  // 1 - 3
    g.InsEdge(0, 3, 1);  // 1 - 4

    g.InsEdge(1, 4, 1);  // 2 - 5
    g.InsEdge(1, 5, 1);  // 2 - 6

    g.InsEdge(2, 6, 1);  // 3 - 7
    g.InsEdge(2, 7, 1);  // 3 - 8

    g.InsEdge(3, 8, 1);  // 4 - 8
    g.InsEdge(3, 9, 1);  // 4 - 10

    g.InsEdge(4, 10, 1); // 5 - 11
    g.InsEdge(6, 11, 1); // 7 - 12
    g.InsEdge(6, 12, 1); // 7 - 13
    g.InsEdge(7, 13, 1); // 8 - 14

    g.InsEdge(9, 14, 1); // 10 - 15
    g.InsEdge(9, 15, 1); // 10 - 16
    g.InsEdge(9, 16, 1); // 10 - 17

    g.InsEdge(10, 17, 1); // 11 - 18
    g.InsEdge(10, 18, 1); // 11 - 19
    g.InsEdge(10, 19, 1); // 11 - 20

    g.InsEdge(16, 20, 1); // 17 - 21
    g.InsEdge(16, 21, 1); // 17 - 22

    g.Print();
    cout << endl;

    g.BP("1", "15");
    cout << endl;
    g.BA("1", "15");
}
