//
// Created by cmli on 20-6-22.
//

#ifndef ANNSG_UTILS_H
#define ANNSG_UTILS_H

#include <string.h>
#include "definations.h"

typedef struct heap_node {
    heap_node(const size_t f, const float s) : first(f), second(s) {}
    size_t first;
    float second;
}P;

//using P = std::pair<size_t, float>;

inline bool cmp(const P &a, const P &b) {
    return a.second < b.second;
}

struct min_heap {
    explicit min_heap(size_t size) {
        cap = size + 2;
        tot = 0;
        pa = (P*) malloc(sizeof(P) * cap);
    }

    ~min_heap() {
        if (pa) {
            free(pa);
        }
    }

    inline size_t emin(size_t p1, size_t p2) {
        return pa[p1].second < pa[p2].second ? p1 : p2;
    }

    void resize(size_t new_size) {
        P *tmp = (P*) malloc(sizeof(P) * new_size);
        memcpy(tmp, pa, sizeof(P) * cap);
        free(pa);
        pa = tmp;
        cap = new_size;
    }

    void push(P e, bool auto_resize = true) {
        if (tot >= cap - 1) {
            if (auto_resize)
                resize(std::max(cap + 1, cap + (cap >> 1)));
        }
        size_t i;
        for (i = ++ tot; i > 1 && cmp(e, pa[i >> 1]); i >>= 1) {
            pa[i] = pa[i >> 1];
        }
        pa[i] = e;
    }

    void pop() {
        if (tot <= 0) {
            std::cout << "heap empty, pop failed!" << std::endl;
            return;
        }
        P tmp = pa[tot];
        size_t i;
        for (i = 2; i < tot; i <<= 1) {
            if (i < tot - 1) {
                i = emin(i, i + 1);
            }
            if (cmp(tmp, pa[i]))
                break;
            pa[i >> 1] = pa[i];
        }
        pa[i >> 1] = pa[tot --];
    }

    P top() {
        return pa[1];
    }

    bool empty() {
        return !tot;
    }

    void clear() {
        tot = 0;
    }

    size_t size() {
        return tot;
    }

    size_t capacity() {
        return cap;
    }

    P get_max_dist_elem() {
        P ret(pa[1].first, pa[1].second);
        for (size_t i = (tot >> 1) + 1; i <= tot; ++ i) {
            if (ret.second > pa[i].second) {
                ret.second = pa[i].second;
                ret.first = pa[i].first;
            }
        }
        return ret;
    }

    P *pa = nullptr;
    size_t tot, cap;
};

#endif //ANNSG_UTILS_H
