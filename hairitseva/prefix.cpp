#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "bundle.h"
using namespace std;

vector<int> prefix(const str& string)
{
    vector<int> pi(string.length());
    pi[0] = 0;
    for (int i = 0; i<string.length(); i++){
        int j = pi[i-1];
        while (j>0 && string[i] != string[j]){
            j = pi[j-1];
        }
        if (string[i] == string[j]) j++;
        pi[i] = j;
    }
    return pi;
} 
