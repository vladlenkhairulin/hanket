#include <iostream>
#include "bundle.h"
#include <readline/readline.h>
using namespace std;

int kmp(const string& big, const string& small){
    int index = -1;
    if (small.empty()) return -1;
    vector<int> pi(small.length()) = prefix(small);
    int j  = 0;
    for (int i = 0; i<big.length()-small.length()+1){
        while (j>0 && small[j] != big[i]]){
            j = pi[j-1];

        }
        if (big[i] == small[j]){
            j++;
        }
        if (j == small.length()){
            index = i-j+1;
        }
    }
    return index;
}
