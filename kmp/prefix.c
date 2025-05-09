#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
int* prefix(const char* str){
    int len = strlen(str);
    int j = 0;
    int i = 1;
    int* pi = (int*)calloc(len, sizeof(int));
    pi[j] = 0;
    while (i < len){
        if (str[i] == str[j]){
            pi[i] = j+1;
            i++;
            j++;
        }
        else{
            if(j==0) i++;
            else j = pi[j-1];
        }
    }
    return pi;
}

int kmp(const char* str, const char* substr, int* pi){
    int i =0;
    int j = 0;
    while (i < strlen(str)){
        if (str[i] == substr[j]){
            i++;
            j++;
            if (j == strlen(substr)){
                int res = i - j;
                printf("Substring found at: %d", res);
                return res;
            }
        }
        else{
            if (j==0) i++;
            else j = pi[j-1];
        }
    }
    printf("Substring not found!");
    return -1;
}

void print_pi(int* pi, int len){
    printf("Prefix array: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", pi[i]);
    }
    printf("\n");
}

int main(){
    char* main_str = "joillakajoist";
    printf("You are gonna search substrings in the string \"%s\"\n", main_str);
    char* str = readline("Input the substring: ");
    int* pi = prefix(str);
    print_pi(pi, strlen(str));
    
    int res_index = kmp(main_str, str, pi);
    free(pi);
    free(str);
}
