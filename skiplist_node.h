#include <iostream>
#include <vector>

constexpr double bad_coin = 0.4;

template <typename T>
struct skiplist_node {
    std::vector<skiplist_node<T>*> levels;
    T value;

    skiplist_node() = default;
    skiplist_node(size_t level, T val) {
        levels = std::vector<skiplist_node<T>*>(level, nullptr);
        value = val;
    }


    virtual ~skiplist_node() {
        delete levels[0];
    }
};

template <typename T>
std::ostream& operator<<(std::ostream &os, const skiplist_node<T> &m) {
    for (int i = 0; i < m.levels.size(); ++i)
        os << m.value << ' ';
    os << '\n';

    return os;
}
