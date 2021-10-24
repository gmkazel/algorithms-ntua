/**************************************************************************
Project     : Algorithms and Complexity - Assignment 1 - Exercise 1
Author      : Ioannis Michail Kazelidis (gkazel@outlook.com)
Date        : November 17, 2020.
Description : Roadtrip. (C++)
-----------
School of ECE, National Technical University of Athens.
**************************************************************************/

#include <bits/stdc++.h>
#include <vector>

unsigned cars, stations, total_distance, remaining_time, economic_T, economic_C, sport_T, sport_C;
unsigned total_time, sport_km, economic_km, max_distance, min_distance, max_diff;

using namespace std;

unsigned reach_city(unsigned max_distance, unsigned min_distance, vector<unsigned> *distance_from_city)
{
    total_time = 0;

    for (size_t j = 0; j < stations + 1; ++j)
    {
        if (max_distance < max_diff)
        {
            total_time = INT_MAX;
            break;
        }

        if (min_distance >= (*distance_from_city)[j])
        {
            total_time += sport_T * (*distance_from_city)[j];
        }
        else
        {
            if (max_distance < (*distance_from_city)[j])
            {
                total_time = INT_MAX;
                break;
            }
            sport_km = ((max_distance - (*distance_from_city)[j]) / total_distance) * (*distance_from_city)[j];    //sport
            economic_km = (((*distance_from_city)[j] - min_distance) / total_distance) * (*distance_from_city)[j]; //economic
            total_time += sport_km * sport_T + economic_km * economic_T;
        }
        if (total_time > remaining_time)
        {
            total_time = INT_MAX;
            break;
        }
    }

    return total_time;
}

int binary_search(vector<array<unsigned, 2>> *car_information, vector<unsigned> *distance_from_city, int left, int right)
{
    unsigned mid = left + (right - left) / 2;
    if (right >= left)
    {
        max_distance = (*car_information)[mid][1] / economic_C;
        min_distance = (*car_information)[mid][1] / sport_C;
        if (reach_city(max_distance, min_distance, distance_from_city) == remaining_time)
        {
            return mid;
        }
        else if (reach_city(max_distance, min_distance, distance_from_city) < remaining_time)
        {
            return binary_search(car_information, distance_from_city, left, mid - 1);
        }
        else
        {
            return binary_search(car_information, distance_from_city, mid + 1, right);
        }
    }
    if (mid > cars)
        return cars;
    else
        return mid;
}

bool capacity_comparison(array<unsigned, 2> first_car, array<unsigned, 2> second_car)
{
    if (first_car[1] < second_car[1])
        return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> cars >> stations >> total_distance >> remaining_time;
    vector<array<unsigned, 2>> *car_information = new vector<array<unsigned, 2>>(cars);
    vector<unsigned> *distance_from_city = new vector<unsigned>(stations);
    unsigned temp, distance = 0;

    for (size_t i = 0; i < cars; ++i)
    {
        cin >> (*car_information)[i][0] >> (*car_information)[i][1];
    }

    for (size_t i = 0; i < stations; ++i)
    {
        cin >> (*distance_from_city)[i];
    }

    cin >> economic_T >> economic_C >> sport_T >> sport_C;

    sort((*distance_from_city).begin(), (*distance_from_city).end());
    temp = *(*distance_from_city).begin();
    distance = *((*distance_from_city).end() - 1);

    for (unsigned i = 1; i < stations; i++)
    {
        temp = (*distance_from_city)[i] - (*distance_from_city)[i - 1];
        (*distance_from_city)[i - 1] = temp;
    }
    (*distance_from_city)[stations - 1] = temp;
    if (distance <= total_distance)
        (*distance_from_city)[stations] = (total_distance - distance); // insert distance from last station

    max_diff = *max_element(distance_from_city->begin(), distance_from_city->end());

    sort((*car_information).begin(), (*car_information).end(), capacity_comparison); //sort by capacity
    unsigned mid = binary_search(car_information, distance_from_city, 0, cars);      //find appropriate index

    if (mid == cars)
    {
        cout << "-1" << endl;
    }
    else
    {
        unsigned min = INT_MAX;
        for (unsigned i = mid; i < cars; ++i)
        {
            if ((*car_information)[i][0] < min)
            {
                min = (*car_information)[i][0];
            }
        }
        cout << min << endl;
    }

    delete car_information;
    delete distance_from_city;
    return 0;
}
