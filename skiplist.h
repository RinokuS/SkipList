#include "skiplist_node.h"
#include <random>
#define MAX_LEVEL 10

template <typename T>
class skiplist {
private:
    skiplist_node<T> *root;
    skiplist_node<T> *tail;

    double uniform_random() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        return dis(gen);
    }

    size_t random_lvl() {
        int level = 1;
        while (uniform_random() < bad_coin && level < MAX_LEVEL )
            level++;

        return level;
    }

public:
    skiplist() = delete;
    skiplist(T min_value, T max_value) {
        if (min_value > max_value)
            std::swap(min_value, max_value);

        root = new skiplist_node<T>(MAX_LEVEL, min_value);
        tail = new skiplist_node<T>(MAX_LEVEL, max_value);

        for (auto& i: root->levels)
            i = tail;
    }

    ~skiplist() {
        delete root;
    }

    void insert(T value) {
        if (value < root->value || value > tail->value)
            return;

        auto temp = new skiplist_node<T>(random_lvl(), value);
        skiplist_node<T>* curr = root;
        skiplist_node<T>* help_arr[MAX_LEVEL];

        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (i <= curr->levels.size() && curr->levels[i] && curr->levels[i]->value < value)
                curr = curr->levels[i];
            help_arr[i] = curr;
        }

        for (int i = 0; i < temp->levels.size(); ++i) {
            temp->levels[i] = help_arr[i]->levels[i];
            help_arr[i]->levels[i] = temp;
        }
    }
    bool erase(T value){
        skiplist_node<T>* curr = root;
        skiplist_node<T>* help_arr[MAX_LEVEL];

        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (i <= curr->levels.size() && curr->levels[i] && curr->levels[i]->value < value)
                curr = curr->levels[i];
            help_arr[i] = curr;
        }

        skiplist_node<T>* node_to_erase = help_arr[0]->levels[0];
        if (node_to_erase->value != value)
            return false;

        for (int i = 0; i < node_to_erase->levels.size(); ++i) {
            help_arr[i]->levels[i] = node_to_erase->levels[i];
            node_to_erase->levels[i] = nullptr;
        }

        delete node_to_erase;
        return true;
    }
    skiplist_node<T>* search(T value) {
        skiplist_node<T>* curr = root;

        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            while (i <= curr->levels.size() && curr->levels[i] && curr->levels[i]->value <= value)
                curr = curr->levels[i];
        }

        if (curr != root && curr != tail && curr->value == value)
            return curr;
        else
            return nullptr;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream &os, const skiplist<T> &m) {
    auto curr = m.root;

    while(curr->levels[0] != m.tail) {
        curr = curr->levels[0];
        os << curr;
    }
}