#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

vector< unordered_map<unsigned int, int> > g;
vector< unordered_map<unsigned int, int> > rest;
vector<bool> visited;

unsigned int t;

int dfs(unsigned int v, int minC)
{
    if (v == t)
    {
        return minC;
    }
    visited[v] = true;
    for (auto i = rest[v].begin(); i != rest[v].end(); ++i)
    {
        if (!visited[i->first] && g[v][i->first] > i->second)
        {
            int d = dfs(i->first, min(minC, g[v][i->first] - i->second));
            if (d > 0)
            {
                i->second += d;
                rest[i->first][v] -= d;
                return d;
            }
        }
    }
    return 0;
}

void printPath(unsigned int v)
{
    printf("%u ", v + 1);
    if (v == t)
    {
        return;
    }
    visited[v] = true;
    for (auto i = rest[v].begin(); i != rest[v].end(); ++i)
    {
        if (!visited[i->first] && i->second > 0)
        {
            --(i->second);
            printPath(i->first);
            return;
        }
    }
}

int main()
{
    freopen("snails.in", "r", stdin);
    freopen("snails.out", "w", stdout);
    unsigned int n, m, a, b, s;
    scanf("%u %u %u %u", &n, &m, &s, &t);
    --s;
    --t;
    g.resize(n, unordered_map<unsigned int, int>());
    rest.resize(n, unordered_map<unsigned int, int>());
    visited.resize(n, false);
    for (size_t i = 0; i < m; ++i)
    {
        scanf("%u %u", &a, &b);
        if (a == b)
        {
            continue;
        }
        --a;
        --b;
        if (!g[a].count(b))
        {
            g[a][b] = 1;
            if (!g[b].count(a))
            {
                g[b][a] = 0;
                rest[b][a] = 0;
            }
            rest[a][b] = 0;
        }
        else
        {
            g[a][b] += 1;
        }
    }
    int flow(0), resDfs;
    while (true)
    {
        resDfs = dfs(s, INT_MAX);
        if (!resDfs)
        {
            break;
        }
        flow += resDfs;
        for (size_t i = 0; i < n; ++i)
        {
            visited[i] = false;
        }
    }
    if (flow > 1)
    {
        printf("YES\n");
        for (int j = 0; j < 2; ++j)
        {
            for (size_t i = 0; i < n; ++i)
            {
                visited[i] = false;
            }
            printPath(s);
            printf("\n");
        }
    }
    else
    {
        printf("NO\n");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}

