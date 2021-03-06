#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

vector<bool> usedLeft;
vector< vector<unsigned int> > edges;
vector<unsigned int> toLeft;

//ctrl+c, ctrl+v from Discr3.3/matching/matching.cpp
bool tryTyan(unsigned int v)
{
    if (usedLeft[v])
    {
        return false;
    }
    usedLeft[v] = true;
    for (size_t i = 0; i < edges[v].size(); ++i)
    {
        unsigned int toRight = edges[v][i];
        if (toLeft[toRight] == UINT_MAX || tryTyan(toLeft[toRight]))
        {
            toLeft[toRight] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    unsigned int n, m, edge;
    scanf("%u %u", &n, &m);
    edges.resize(n, vector<unsigned int>());
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%u", &edge);
        while (edge != 0)
        {
            edges[i].emplace_back(edge - 1);
            scanf("%u", &edge);
        }
    }
    toLeft.resize(m, UINT_MAX);
    usedLeft.resize(n);
    for (size_t i = 0; i < n; ++i)
    {
        usedLeft.assign(n, false);
        tryTyan(i);
    }
    vector<unsigned int> ans(n, 0);
    unsigned int matchingSize(0);
    for (size_t i = 0; i < m; ++i)
    {
        if (toLeft[i] != UINT_MAX)
        {
            ans[toLeft[i]] = i + 1;
            ++matchingSize;
        }
    }
    printf("%u\n", matchingSize);
    for (size_t i = 0; i < n; ++i)
    {
        if (ans[i] != 0)
        {
            printf("%u %u\n", i + 1, ans[i]);
        }
    }
    return 0;
}
