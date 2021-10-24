/**************************************************************************
Project     : Algorithms and Complexity - Assignment 1 - Exercise 2
Author      : Ioannis Michail Kazelidis (gkazel@outlook.com)
Date        : November 17, 2020.
Description : Teleports. (C++)
-----------
School of ECE, National Technical University of Athens.
**************************************************************************/

#include <bits/stdc++.h>

unsigned universes, portals, counter;

using namespace std;

class Union_Find
{
    unsigned *id, *size;

public:
    Union_Find(unsigned N)
    {
        id = new unsigned[N];
        size = new unsigned[N];
        for (unsigned i = 0; i < N; ++i)
        {
            id[i] = i;
            size[i] = 1;
        }
    }
    //destructor
    ~Union_Find()
    {
        delete[] id;
        delete[] size;
    }

    int find(unsigned p)
    {
        unsigned root = p;
        while (root != id[root])
            root = id[root];
        while (p != root)
        {
            unsigned neo = id[p];
            id[p] = root;
            p = neo;
        }
        return root;
    }

    void merge(unsigned x, unsigned y)
    {
        unsigned i, j;
        i = find(x);
        j = find(y);
        if (i == j)
            return;

        if (size[i] < size[j])
        {
            id[i] = j;
            size[j] += size[i];
        }
        else
        {
            id[j] = i;
            size[i] += size[j];
        }
    }

    bool is_connected(unsigned x, unsigned y)
    {
        return (find(x) == find(y));
    }
};

bool weight_comparison(array<unsigned, 3> portal1, array<unsigned, 3> portal2)
{
    if (portal1[2] > portal2[2])
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    counter = 0;

    cin >> universes >> portals;
    bool solution[universes];
    memset(solution, false, universes);
    vector<unsigned> *permutation = new vector<unsigned>(universes);
    vector<array<unsigned, 3>> *portal_info = new vector<array<unsigned, 3>>(portals);
    for (size_t i = 0; i < universes; ++i)
    {
        cin >> (*permutation)[i];
    }

    for (size_t i = 0; i < portals; ++i)
    {
        cin >> (*portal_info)[i][0] >> (*portal_info)[i][1] >> (*portal_info)[i][2];
    }

    Union_Find union_find = Union_Find(universes + 1);

    sort(portal_info->begin(), portal_info->end(), weight_comparison);

    for (size_t i = 0; i < universes; ++i)
    {
        if ((*permutation)[i] == i + 1)
        {
            solution[i] = true;
            counter++;
        }
    }

    bool flag = false;

    for (size_t i = 0; i < portals; ++i)
    {
        flag = false;
        union_find.merge((*portal_info)[i][0], (*portal_info)[i][1]);
        if (solution[(*portal_info)[i][0] - 1] != true)
        {
            solution[(*portal_info)[i][0] - 1] = true;
            counter++;
        }
        if (solution[(*portal_info)[i][1] - 1] != true)
        {
            solution[(*portal_info)[i][1] - 1] = true;
            counter++;
        }
        if (counter == universes)
        {
            for (size_t j = 0; j < universes; ++j)
            {
                if (!union_find.is_connected((*permutation)[j], j + 1))
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                cout << (*portal_info)[i][2] << endl;
                delete permutation;
                delete portal_info;
                return 0;
            }
        }
    }

    delete permutation;
    delete portal_info;
    return 0;
}
