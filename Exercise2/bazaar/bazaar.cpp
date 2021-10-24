/**************************************************************************
Project     : Algorithms and Complexity - Assignment 2 - Exercise 2
Author      : Ioannis Michail Kazelidis (gkazel@outlook.com)
Date        : December 21, 2020.
Description : Bazaar. (C++)
-----------
School of ECE, National Technical University of Athens.
**************************************************************************/

#include <bits/stdc++.h>

using namespace std;

int full_sets, offers, type_count, type_price, minx, miny, minz, max_offers;
vector<vector<vector<array<int, 2>>>> merchants;
vector<vector<vector<vector<int>>>> memo;

bool cost_comparison(array<int, 2> first, array<int, 2> second){
    if(first[1] == second[1])
        return (first[0] > second[0]);
    return (first[1] < second[1]);
}

unsigned salesman(int merch, int quantity, int type, int start){
    if(quantity <= 0) return 0;
    if(start < max_offers && memo[type][merch][quantity][start] != -1){
        return memo[type][merch][quantity][start];
    }
    if(start >= (int)merchants[type][merch].size()) return INT_MAX;
    if(merchants[type][merch][start][0] >= full_sets){
        return memo[type][merch][quantity][start] = merchants[type][merch][start][1];
    }
    return memo[type][merch][quantity][start] = min(salesman(merch, quantity - merchants[type][merch][start][0], type, start+1) + merchants[type][merch][start][1], salesman(merch, quantity, type, start+1));
}

int quantity_bought(int merch, int quantity){
    if(quantity <= 0) return 0;
    return salesman(merch, quantity, 0, 0) + salesman(merch, quantity, 1, 0) + salesman(merch, quantity, 2, 0);
}

int max_offers_number(){
  int max_off = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      max_off = max(max_off, (int)merchants[i][j].size());
    }
  }
  return max_off;
}

int full_set_number(int merch){
    int sets_A = 0;
    int sets_B = 0;
    int sets_C = 0;
    for(auto i : merchants[0][merch]){
        sets_A += i[0];
    }
    for(auto i : merchants[1][merch]){
        sets_B += i[0];
    }
    for(auto i : merchants[2][merch]){
        sets_C += i[0];
    }
    return min(sets_A, min(sets_B, sets_C));
}

int total_cost(){
    int sum = INT_MAX;
    for(int x=0; x <= min(minx, full_sets); ++x){
        for(int y=0; y <= min(miny, full_sets - x); ++y){
            if(minz >= full_sets - x - y){
                sum = min(sum, quantity_bought(0,x) + quantity_bought(1,y) + quantity_bought(2,full_sets - x - y));
            }
        }
    }
    return sum;
}

int main(){
    ios::sync_with_stdio(false);

    cin >> full_sets >> offers;

    merchants.resize(3);
    for(int i=0; i<3; ++i){
        merchants[i].resize(3);
    }

    char type_id[2];
    for(int i=0; i < offers; ++i){
        cin >> type_id >> type_count >> type_price;
        if(type_id[1] == 'A') merchants[0][(int)type_id[0]-49].push_back(array<int,2>{type_count, type_price});
        if(type_id[1] == 'B') merchants[1][(int)type_id[0]-49].push_back(array<int,2>{type_count, type_price});
        if(type_id[1] == 'C') merchants[2][(int)type_id[0]-49].push_back(array<int,2>{type_count, type_price});
    }

    minx = full_set_number(0);
    miny = full_set_number(1);
    minz = full_set_number(2);
    if(full_sets > minx + miny + minz) {
        cout << "-1" << endl;
        return 0;
    }

    for(int i=0; i < 3; ++i){
        for(int j=0; j < 3; ++j){
            sort(merchants[i][j].begin(), merchants[i][j].end(), cost_comparison);
        }
    }

    max_offers = max_offers_number();
    memo.resize(3);
    for(int i=0; i < 3; ++i){
        memo[i].resize(3);
        for(int j=0; j < 3; ++j){
            memo[i][j].resize(full_sets + 1);
            for(int k=0; k < full_sets + 1; ++k){
                memo[i][j][k].resize(max_offers, -1);
            }
        }
    }

    cout << total_cost() << endl;

    return 0;
}
