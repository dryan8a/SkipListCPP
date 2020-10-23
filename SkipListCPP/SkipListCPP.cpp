#include <iostream>
#include "SkipList.h"

int main()
{
    auto list = SkipList<int>::Create(5);
    list->Insert(1);
    list->Insert(3);
    list->Insert(2);
    list->Remove(2);
    list->Remove(3);
    list->Remove(1);
    std::cout << list->Contains(1);
}
