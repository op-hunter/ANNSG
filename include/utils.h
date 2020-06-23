//
// Created by cmli on 20-6-22.
//

#ifndef ANNSG_UTILS_H
#define ANNSG_UTILS_H

using P = std::pair<size_t, float>;

struct min_heap {
    min_heap(size_t size) {
        cap = size;
        tot = 0;
        pa = (P*) malloc(sizeof(P) * cap);
    }

    ~min_heap() {
        if (pa) {
            free(pa);
        }
    }

    void push(P e) {
        for (int i = ++ tot; i > 1 && cmp(e, pa[i >> 1]); i >>= 1) {
            pa[i] = pa[i >> 1];
        }
        pa[i] = e;
    }

    void pop() {
        P tmp = pa[tot];
        for (int i = 2; i < n; i <<= 1) {
            if (i < n - 1) {
                i = min(i, i + 1);
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

    P *pa = nullptr;
    int tot, cap;
};

#endif //ANNSG_UTILS_H
