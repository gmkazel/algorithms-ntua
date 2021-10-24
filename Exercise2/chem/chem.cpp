/**************************************************************************
Project     : Algorithms and Complexity - Assignment 2 - Exercise 1
Author      : Ioannis Michail Kazelidis (gkazel@outlook.com)
Date        : December 21, 2020.
Description : Chem. (C++)
-----------
School of ECE, National Technical University of Athens.
**************************************************************************/

#include <bits/stdc++.h>

using namespace std;

int substances, flasks;

int energy(int start, int flasks, int substances, int **costs, int **memo){
    if(memo[start][flasks] == -1){
        if(flasks == 1){
            memo[start][flasks] = costs[start][substances-1];
            return costs[start][substances-1];
        }

        int sum = INT_MAX;

        for(int j = start; j < substances - flasks + 1; ++j){
            if(j == start){
                sum = min(sum, energy(j+1, flasks-1, substances, costs, memo));
            }
            else if(costs[start][j] < sum){
                sum = min(sum, costs[start][j] + energy(j+1, flasks-1, substances, costs, memo));
            }
        }
        memo[start][flasks] = sum;
        return sum;
    }
    else{
        return memo[start][flasks];
    }
}

int main(){
    ios::sync_with_stdio(false);

    cin >> substances >> flasks;

    int **reactions = new int*[substances];
    int **costs = new int*[substances];
    int **memo = new int*[substances];

    for(int i=0; i < substances; ++i){
        reactions[i] = new int[substances];
        costs[i] = new int[substances];
        memo[i] = new int[substances];
        memset(reactions[i], 0, substances*sizeof(int));
        memset(costs[i], 0, substances*sizeof(int));
        memset(memo[i], -1, substances*sizeof(int));
        for(int j=i+1; j < substances; ++j){
            cin >> reactions[i][j];
        }
    }

    int temp;
    int sum;
    //initialize costs
    for(int j=1; j < substances; ++j){
        for(int i=0; i < j; ++i){
            if(i==0){
                if(j==1){
                    costs[i][j] = reactions[i][j];
                    temp = costs[i][j];
                }
                else{
                    sum = 0;
                    for(int k=i; k <= j - 1; ++k){
                        sum+= reactions[k][j];
                    }
                    temp = sum;
                    costs[i][j] = temp + costs[i][j-1];
                }
            }
            else{
                temp -= reactions[i-1][j];
                costs[i][j] = costs[i][j-1] + temp;
            }
        }
    }

    //calculate energy
    cout << energy(0, flasks, substances, costs, memo) << endl;

    delete[] reactions;
    delete[] costs;
    delete[] memo;

    return 0;
}
