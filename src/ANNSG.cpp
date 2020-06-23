//
// Created by cmli on 20-6-20.
//

#include <cstring>
#include <random>
#include <time.h>
#include "../include/ANNSG.h"

namespace annsg{

ANNSG::ANNSG(size_t n, size_t dim, MetrcType mt)
: nb_(n), d_(dim), nn_(0), link_size_(0) {
    if (mt == MetrcType::IP)
        df_ = new DistanceIP();
    else if (mt == MetrcType::L2)
        df_ = new DistanceL2(n);
    else
        std::cout << "Invalid MetricType: " << mt
                  << ", MetricType is alternative in ("
                  << MetrcType::IP << ", " << MetrcType::L2 << ")" << std::endl;

    graph = (char **) malloc(sizeof(void *) * nb_);
    memset(graph, 0, sizeof(void *) * nb_);
    index_status_ = 0;
}

ANNSG::~ANNSG() {
    delete df_;
    for (auto i = 0; i < nb_; ++ i) {
        if (graph[i])
            free(graph[i]);
    }
    free(graph);
}

void ANNSG::Save(const char *file_location) {

}

void ANNSG::Load(const char *file_location) {
    index_status_ = 2;
}

void ANNSG::LoadKnng(const char *file_location) {
    index_status_ = 1;
}

void ANNSG::SetKnng(const char **knng, size_t n) {
    index_status_ = 1;
}

void ANNSG::Resize(const size_t n) {
    char **new_graph = (char **) malloc(sizeof(void *) * n);
    memset(new_graph, 0, sizeof(void *) * n);
    for (auto i = 0; i < nb_; ++ i) {
        if (graph[i]) {
            new_graph[i] = (char *) malloc(link_size_);
            memcpy(new_graph[i], graph[i], link_size_);
            free(graph[i]);
        }
    }
    free(graph);
    graph = new_graph;
    nb_ = n;
}

inline int find(int x, int *f) {
    return x == f[x] ? x : f[x] = find(f[x], f);
}

inline void join(int x, int y, int *f) {
    int fx = find(x, f), fy = find(y, f);
    if (fx != fy)
        f[fx] = fy;
}

void ANNSG::search(const float *pdata, const float *query, min_heap *knn, min_heap *candidates,
                   boost::dynamic_bitset<> *vis) {
    boost::dynamic_bitset<> *pvis = vis == nullptr ? new boost::dynamic_bitset<>(nb_, 0) : vis;
}

void ANNSG::init(const float *data, size_t *f) {
    float *c = (float *) malloc(sizeof(float) * d_);
    for (auto i = 0; i < d_; ++ i) {
        c[i] = 0;
    }
    for (size_t i = 0; i < nb_; ++ i) {
        f[i] = i;
        for (auto j = 0; j < d_; ++ j) {
            c[j] += data[i * d_ + j];
        }
    }
    for (auto i = 0; i < d_; ++ i) {
        c[i] /= nb_;
    }

    min_heap *pknn = new min_heap(nn_);
    min_heap *pcandi = new min_heap(nn_ << 3);
    search(c, pknn, pcandi);
    np_ = pknn->top().first;

    free(c);
    free(pknn);
    free(pcandi);
}

void ANNSG::Build(const size_t n, const float *data, size_t nn) {
    if (index_status_ == 2) {
        std::cout << "index has been built!" << std::endl;
        return;
    } else if (index_status_ == 0) {
        std::cout << "build failed, please set Knng first!" << std::endl;
        return;
    }
    if (n > nb_) {
        Resize(n);
    }
    nn_ = nn;
    link_size_ = (nn_ + 1) * sizeof(size_t);
    size_t* fa = (size_t *) malloc(sizeof(size_t) * nb_);
    init(data, fa);
    make_graph(fa);
    no_one_less(fa);
//    min_heap *pknn = new min_heap(nn);
//    min_heap *pcandi = new min_heap(nn << 3);

    index_status_ = 2;
    free(fa);
}

void ANNSG::Search(const float *data, const float *query_data, size_t topk, float *top_dists,
                   size_t *top_ids, const size_t search_k) {
    min_heap *pknn = new min_heap(search_k);
    boost::dynamic_bitset<> vis{nb_, 0};
    search(data, query_data, pknn, nullptr, &vis);


    for (auto i = 0; i < topk && !pknn->empty(); ++ i) {
        top_ids[i] = pknn->top().first;
        top_dists[i] = pknn->top().second;
        pknn->pop();
    }
    free(pknn);
}

}


