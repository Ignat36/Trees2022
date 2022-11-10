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

int main()
{
    for (int i = 0; i < 10000; i++) {
        int action_id;
        std::string name, phone_number;
        char buf[100];

        printf_s("%s", "Enter action number : \n1. Add new contact\n2.Find number by name\nAction number : ");

        scanf_s("%d", &action_id, 1);

        std::string num;

        switch (action_id)
        {
        case 1:
            printf_s("%s", "Enter name : ");

            scanf_s("%s", buf, sizeof(buf));
            name = std::string(buf);

            printf_s("%s", "Enter phone number : ");
            scanf_s("%s", buf, sizeof(buf));
            phone_number = std::string(buf);

            dict[name] = phone_number;

            break;

        case 2:
            printf_s("%s", "Enter name : ");
            scanf_s("%s", buf, sizeof(buf));
            name = std::string(buf);

            try {
                num = dict.findValueWithKey(name);
                printf_s("Number : %s\n", num.c_str());
            }
            catch (...) {
                printf_s("%s", "Record with such name is not found\n");
            }
            break;

        case 3:
            print_dict();
            break;

        default:
            break;
        }
    }
}