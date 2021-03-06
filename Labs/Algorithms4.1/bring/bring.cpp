#include <iostream>
#include <vector>
#include <climits>
#include <map>

using namespace std;

vector< map<unsigned int, int> > g;
vector< map<unsigned int, int> > rest;
vector<bool> visited;
unsigned int t, n;

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
                //rest[i->first][v] -= d;
                if (v + n != i->first && i->first + n != v)
                {
                    if (i->first > v)
                    {
                        rest[i->first - n][v + n] -= d;
                        //rest[v + n][i->first - n] += d;
                    }
                    else
                    {
                        rest[i->first + n][v - n] -= d;
                        //rest[v - n][i->first + n] += d;
                    }
                }
                else
                {
                    rest[i->first][v] -=d;
                }
                return d;
            }
        }
    }
    return 0;
}

int main()
{
    freopen("bring.in", "r", stdin);
    freopen("bring.out", "w", stdout);
    unsigned int m, k, s;
    scanf("%u %u %u %u %u\n", &n, &m, &k, &s, &t);
    --s;
    --t;
    visited.resize(n, false);
    vector< pair<unsigned int, unsigned int> > tubes;
    unsigned int from, to;
    for (size_t i = 0; i < m; ++i)
    {
        scanf("%u %u\n", &from, &to);
        tubes.emplace_back(from - 1, to - 1);
        tubes.emplace_back(to - 1, from - 1);
    }
    for (size_t i = 0; i < n; ++i)
    {
        tubes.emplace_back(i, i);
    }
    int flow(0), resDfs;
    unsigned int day(0);
    while (flow < k)
    {
        ++day;
        g.resize(n + day * n, map<unsigned int, int>());
        for (size_t i = 0; i < rest.size(); ++i)
        {
            for (auto j = rest[i].begin(); j != rest[i].end(); ++j)
            {
                j->second = 0;
            }
        }
        rest.resize(n + day * n, map<unsigned int, int>());
        visited.assign(day * n, false);
        visited.resize(n + day * n, false);
        for (size_t i = 0; i < tubes.size(); ++i)
        {
            from = tubes[i].first + (day - 1) * n;
            to = tubes[i].second + day * n;
            if (i >= 2 * m)
            {
                g[from][to] = 1e4;
                //g[to][from] = 0;
                //rest[to][from] = 0;
            }
            else
            {
                g[from][to] = 1;
            }
            g[to][from] = 0;
            rest[from][to] = 0;
            rest[to][from] = 0;
        }
        flow = 0;
        t += n;
        while (true)
        {
            resDfs = dfs(s, k - flow);
            flow += resDfs;
            if (!resDfs || k == flow)
            {
                break;
            }
            visited.assign(n + day * n, false);
        }
    }
    printf("%u\n", day);
    vector<unsigned int> ships(k, s);
    for (size_t i = 0; i < day; ++i)
    {
        vector< pair<unsigned int, unsigned int> > ans;
        for (size_t j = 0; j < k; ++j)
        {
            for (auto h = rest[ships[j]].begin(); 
                    h != rest[ships[j]].end(); ++h)
            {
                //if (h->second > 0)
                //{
                //    printf("%u -> %u : %d\n", ships[j], h->first, h->second);
                //}
                if (h->second > 0) 
                {
                    //cerr << k->first - (i * n) << " -- " << ships[j].front() << endl;
                    --(h->second);
                    if (h->first > ships[j])
                    {
                        if (g[ships[j]][h->first] != 1e4)
                        {
                            ans.emplace_back(j, h->first % n);
                        }
                        ships[j] = h->first;
                        break;
                    }
                }
            }
        }
        printf("%lu  ", ans.size());
        for (size_t j = 0; j < ans.size(); ++j)
        {
            printf("%u %u  ", ans[j].first + 1, ans[j].second + 1);
        }
        printf("\n");
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
