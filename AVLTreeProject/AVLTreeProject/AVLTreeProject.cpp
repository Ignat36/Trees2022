
// AVLTreeProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "AVL.h"
#include <iostream>

AVL dict;

int main()
{
    for (int i = 0; i < 10000; i++) {
        int action_id;
        std::string name;
        int phone_number;
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
            scanf_s("%d", &phone_number, 1);

            dict[name] = phone_number;

            break;

        case 2:
            printf_s("%s", "Enter number : ");
            scanf_s("%d", &phone_number, 1);

            try {
                num = dict.findValueWithKey(phone_number);
                printf_s("Number : %s\n", num.c_str());
            }
            catch (...) {
                printf_s("%s", "Record with such name is not found\n");
            }
            break;

        default:
            break;
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
