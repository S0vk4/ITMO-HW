#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

vector< unordered_map<unsigned int, int> > g;
vector< unordered_map<unsigned int, int> > rest;
vector<bool> visited;

int dfs(unsigned int v, int minC)
{
    if (v == rest.size() - 1)
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

int main()
{
    freopen("flow.in", "r", stdin);
    freopen("flow.out", "w", stdout);
    unsigned int n, m, a, b;
    int c;
    scanf("%u\n%u", &n, &m);
    g.resize(n, unordered_map<unsigned int, int>());
    rest.resize(n, unordered_map<unsigned int, int>());
    visited.resize(n, false);
    vector< pair<unsigned int, unsigned int> > tubes;
    vector<int> cs;
    for (size_t i = 0; i < m; ++i)
    {
        scanf("%u %u %d", &a, &b, &c);
        --a;
        --b;
        tubes.emplace_back(a, b);
        cs.emplace_back(c);
        if (!g[a].count(b))
        {
            g[a][b] = c;
            g[b][a] = c;
            rest[a][b] = 0;
            rest[b][a] = 0;
        }
        else
        {
            g[a][b] += c;
            g[b][a] += c;
        }
    }
    int flow(0), resDfs;
    while (true)
    {
        resDfs = dfs(0, INT_MAX);
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
    printf("%d\n", flow);
    for (size_t i = 0; i < m; ++i)
    {
        if (cs[i] >= abs(rest[tubes[i].first][tubes[i].second]))
        {
            printf("%d\n", rest[tubes[i].first][tubes[i].second]);
            rest[tubes[i].first][tubes[i].second] = 0; 
            rest[tubes[i].second][tubes[i].first] = 0; 
        }
        else
        {
            if (rest[tubes[i].first][tubes[i].second] > 0)
            {
                rest[tubes[i].first][tubes[i].second] -= cs[i];
                rest[tubes[i].second][tubes[i].first] += cs[i]; 
                printf("%d\n", cs[i]);
            }
            else
            {
                rest[tubes[i].first][tubes[i].second] += cs[i];
                rest[tubes[i].second][tubes[i].first] -= cs[i]; 
                printf("%d\n", -cs[i]);
            }
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
