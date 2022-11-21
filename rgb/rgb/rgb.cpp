#define _CRT_SECURE_NO_WARNINGS

#include "rbt.h"
#include <iostream>
#include <map>

RBT<std::string, std::string> dict;
std::map<int, int> mp;


void print_dict()
{
    for (auto i = dict.begin(); i != dict.end(); ++i) 
        printf_s("%s ", (* i).c_str());

    printf("\n");
}

void print_dict_l()
{
    for (auto i = dict.begin_l(); i != dict.end_l(); ++i)
        printf_s("%s ", (*i).c_str());

    printf("\n");
}

int main()
{
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 20; i++) {
            std::cout << rand() % 10;
        }
        std::cout << "\n";
    }
}