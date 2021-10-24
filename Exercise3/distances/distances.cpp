/**************************************************************************
Project     : Algorithms and Complexity - Assignment 3 - Exercise 1
Author      : Ioannis Michail Kazelidis (gkazel@outlook.com)
Date        : January 18, 2021.
Description : Distances. (C++)
-----------
School of ECE, National Technical University of Athens.
**************************************************************************/

#include <bits/stdc++.h>

#define MAX_N 100000

using namespace std;

int cities, streets;

struct Edge
{
    int first_node, second_node, weight;
};

struct Vertice
{
    list<pair<int, int>> adjacent;
};

typedef struct Set
{
    int parent, rank;
} Set;

Set subsets[MAX_N];

int dfs(const vector<Vertice> &nodes, int current, int parent, vector<unsigned> &times);
int find(int node);
void Union(int x, int y);
bool is_same_set(Edge &e);

int main()
{
    ios::sync_with_stdio(false);
    string solution;
    int end, n1, n2, w;
    int node1, node2, weight;
    int position = 0;

    cin >> cities >> streets;

    vector<Edge> edges(streets);
    vector<Vertice> vertices(cities);
    vector<unsigned> times(streets, 0);

    for (int i = 0; i < streets; ++i)
    {
        cin >> node1 >> node2 >> weight;
        edges[weight].first_node = node1 - 1;
        edges[weight].second_node = node2 - 1;
        edges[weight].weight = weight;
    }

    for (int i = 0; i < cities; ++i)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    edges.erase(remove_if(edges.begin(), edges.end(), is_same_set), edges.end());

    for (unsigned i = 0; i < edges.size(); ++i)
    {
        n1 = edges[i].first_node;
        n2 = edges[i].second_node;
        w = edges[i].weight;
        vertices[n1].adjacent.push_back(make_pair(n2, w));
        vertices[n2].adjacent.push_back(make_pair(n1, w));
    }

    dfs(vertices, cities / 2, 0, times);

    solution.resize(times.size());

    for (end = times.size() - 1; end >= 0; --end)
    {
        if (times[end] != 0)
        {
            solution[position] = '1';
        }
        else
            solution[position] = '0';
        position++;
    }

    solution = solution.substr(solution.find_first_of('1'), solution.length());
    cout << solution << endl;
}

int dfs(const vector<Vertice> &nodes, int current, int parent, vector<unsigned> &times)
{
    int count = 1;
    int child, idx;
    unsigned set_size;
    const Vertice &curr = nodes[current];
    for (pair<int, int> it : curr.adjacent)
    {
        tie(child, idx) = it;
        if (child == parent)
            continue;
        set_size = dfs(nodes, child, current, times);
        times[idx] += (cities - set_size) * set_size;

        while (times[idx] > 1)
        {
            if (idx == (int)times.size() - 1)
            {
                times.push_back(times[idx] / 2);
                times[idx] %= 2;
            }
            else
            {
                times[idx + 1] += times[idx] / 2;
                times[idx] %= 2;
            }
            ++idx;
        }
        count += set_size;
    }
    return count;
}

int find(int node)
{
    while (node != subsets[node].parent)
    {
        node = find(subsets[node].parent);
    }
    return node;
}

void Union(int x, int y)
{
    int setx = find(x);
    int sety = find(y);
    if (setx == sety)
        return;
    if (subsets[setx].rank > subsets[sety].rank)
    {
        subsets[sety].parent = setx;
    }
    else
    {
        subsets[setx].parent = sety;
        if (subsets[setx].rank == subsets[sety].rank)
        {
            ++(subsets[sety].rank);
        }
    }
}

bool is_same_set(Edge &e)
{
    int setx = find(e.first_node);
    int sety = find(e.second_node);
    if (setx == sety)
        return true;
    else
        Union(e.first_node, e.second_node);
    return false;
}
