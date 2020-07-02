//
// Created by cmli on 20-6-20.
//

#ifndef ANNSG_ANNSG_H
#define ANNSG_ANNSG_H

#include "definations.h"
#include "distance.h"
#include "utils.h"

namespace annsg {

class ANNSG {
 public:
    ANNSG(size_t n, size_t dim, MetrcType mt);
    ~ANNSG();

    void Load(const char *file_location);
    void Save(const char *file_location);
    void LoadKnng(const char *file_location);
    void SetKnng(const char **knng, size_t n);
    void Resize(const size_t n);
    void Build(const size_t n, const float *data, size_t nn);
    void Search(const float *data, const float *query_data, size_t topk, float *top_dists, size_t *top_ids, const size_t search_k);
 private:
    void init(const float *data, size_t *f);
    void search(const float *pdata, const float *query, min_heap *knn, min_heap *candidates, boost::dynamic_bitset<> *vis = nullptr);
    void make_graph(size_t *f);
    void no_one_less(size_t *f);

    size_t d_; // dim
    size_t nb_; // num of base
    size_t nn_; // max num of neighbors
    size_t np_; // navigate point id
    int metric_type_;
    Distance* df_; // distance function
    size_t link_size_; // size of per link
    char **graph;
    uint8_t index_status_; // 0: nothing 1: knng  2: annsg

};

}



#endif //ANNSG_ANNSG_H
