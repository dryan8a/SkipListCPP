#include <iostream>
#include "SkipList.h"

int main()
{
    auto list = SkipList<int>::Create(5);
    list->Insert(1);
    list->Insert(3);
    list->Insert(2);
}
