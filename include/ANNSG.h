//
// Created by cmli on 20-6-20.
//

#ifndef ANNSG_ANNSG_H
#define ANNSG_ANNSG_H

#include "definations.h"
#include "distance.h"

namespace annsg {

class ANNSG {
 public:
    ANNSG(size_t n, float *pdata, size_t dim, MetrcType mt);
    ~ANNSG();
 private:
    size_t nv_; // num of vectors in the index
    size_t dim_;

};

}



#endif //ANNSG_ANNSG_H
