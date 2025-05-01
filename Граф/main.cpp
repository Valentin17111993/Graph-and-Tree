#include <iostream>
#include "Graph.h"
#include "task.h"
using namespace std;

int main()
{
    // создаём объект
    Graph g;
    cifr(g);

    g.findMinDistanceDecstr(0);
    return 0;
}