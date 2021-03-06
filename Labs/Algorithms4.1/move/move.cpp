#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <cmath>

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

struct Edge
{
    Edge(unsigned int from, unsigned int to, double time)
    {
        this->from = from;
        this->to = to;
        this->time = time;
    }

    unsigned int from, to;
    double time;

    bool operator<(const Edge & e) const
    {
        return time < e.time;
    }
};

int main()
{
    unsigned int n;
    double x, y, speed;
    scanf("%u", &n);
    vector<double> speeds;
    vector< pair<double, double> > coords;
    vector<Edge> sortedEdges;
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%lf %lf %lf", &x, &y, &speed);
        coords.emplace_back(x, y);
        speeds.emplace_back(speed);
    }
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%lf %lf", &x, &y);
        for (size_t j = 0; j < n; ++j)
        {
            sortedEdges.emplace_back(j, i, 
                    sqrt(
                        (coords[j].first - x) * (coords[j].first - x) +
                        (coords[j].second - y) * (coords[j].second - y)
                    ) / speeds[j]);
        }
    }
    sort(sortedEdges.begin(), sortedEdges.end());
    unsigned int matchingSize(0), edgeCount(n - 1);
    toLeft.resize(n);
    usedLeft.resize(n);
    edges.resize(n, vector<unsigned int>());
    for (size_t i = 0; i < edgeCount; ++i)
    {
        edges[sortedEdges[i].from].emplace_back(sortedEdges[i].to);
    }
    while (matchingSize < n)
    {
        edges[sortedEdges[edgeCount].from].emplace_back(
                sortedEdges[edgeCount].to);
        toLeft.assign(n, UINT_MAX);
        for (size_t i = 0; i < n; ++i)
        {
            usedLeft.assign(n, false);
            tryTyan(i);
        }
        matchingSize = 0;
        for (size_t i = 0; i < n; ++i)
        {
            if (toLeft[i] != UINT_MAX)
            {
                ++matchingSize;
            }
        }
        ++edgeCount;
    }
    printf("%.6lf\n", sortedEdges[edgeCount - 1].time);
    return 0;
}
