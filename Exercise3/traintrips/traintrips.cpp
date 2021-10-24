/**************************************************************************
Project     : Algorithms and Complexity - Assignment 3 - Exercise 2
Author      : Ioannis Michail Kazelidis (gkazel@outlook.com)
Date        : January 18, 2021.
Description : Traintrips. (C++)
-----------
School of ECE, National Technical University of Athens.
**************************************************************************/

#include <bits/stdc++.h>

using namespace std;

unsigned distances, queries;
unsigned maximum;
vector<unsigned> dist, quer;
vector<bool> possible;

void check(unsigned distances);

int main()
{
  ios::sync_with_stdio(false);

  cin >> distances >> queries;

  dist.resize(distances);
  quer.resize(queries);

  for (unsigned i = 0; i < distances; ++i)
  {
    cin >> dist[i];
  }

  for (unsigned i = 0; i < queries; ++i)
  {
    cin >> quer[i];
  }

  maximum = *max_element(quer.begin(), quer.end());
  possible.resize(maximum, 0);

  sort(dist.begin(), dist.end());
  check(distances);

  for (unsigned i = 1; i <= queries; ++i)
  {
    if (possible[i])
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }

  return 0;
}

void check(unsigned distances)
{
  possible[0] = true;

  for (unsigned i = 0; i <= distances; ++i)
  {
    unsigned val = dist[i];

    // if it is already possible skip
    if (possible[val])
    {
      continue;
    }

    for (unsigned j = 0; j + val <= maximum; ++j)
    {
      if (possible[j])
      {
        possible[j + val] = true;
      }
    }
  }
}
