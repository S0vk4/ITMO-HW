#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

struct Thing
{
    int x1, y1, x2, y2;

    Thing(int & x1, int & y1, int & x2, int & y2) : 
        x1(x1), y1(y1), x2(x2), y2(y2) {}

    int getDistance(const Thing & other) const
    {
        return max(0, 
                max(x1 - other.x2, 
                    max(y1 - other.y2, 
                        max(other.y1 - y2, 
                            other.x1 - x2))));
    }
};

int main()
{
    unsigned int n, w;
    int x1, x2, y1, y2;
    scanf("%u %u\n", &n, &w);
    vector<Thing> things;
    vector< vector<long long int> > g(n + 2, vector<long long int>(n + 2));
    g[0][n + 1] = w;
    g[n + 1][0] = w;
    for (size_t i = 0; i < n; ++i)
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        things.emplace_back(x1, y1, x2, y2);
        g[i + 1][0] = w - y2;
        g[0][i + 1] = w - y2;
        g[i + 1][n + 1] = y1;
        g[n + 1][i + 1] = y1;
        for (size_t j = 0; j < i; ++j)
        {
            g[i + 1][j + 1] = things[i].getDistance(things[j]);
            g[j + 1][i + 1] = g[i + 1][j + 1];
        }
    }
    vector<long long int> dist(n + 2, LLONG_MAX);
    dist[0] = 0;
    priority_queue< pair<long long int, long long int> > q;
    q.push(make_pair(0, 0));
    int cur;
    while (!q.empty())
    {
        cur = q.top().second;
        q.pop();
        while (!q.empty() && q.top().first != -dist[q.top().second])
        {
            q.pop();
        }
        for (size_t i = 0; i < n + 2; ++i)
        {
            if (i == cur)
            {
                continue;
            }
            if (dist[i] > g[cur][i] + dist[cur])
            {
                dist[i] = g[cur][i] + dist[cur];
                q.push(make_pair(-dist[i], i));
            }
        }
    }
    printf("%lld\n", dist[n + 1]);
    return 0;
}
