#include <iostream>

#include "skiplist.h"

int main()
{
    skiplist<int> sl(0, 100);

    sl.insert(2);
    sl.insert(5);
    sl.insert(12);
    sl.insert(11);
    sl.insert(16);
    sl.insert(15);
    sl.insert(13);
    sl.insert(11);
    sl.insert(2);

    auto k = sl.search(15);
    sl.erase(15);
    k = sl.search(15);
    //std::cout << sl;
    return 0;
}
