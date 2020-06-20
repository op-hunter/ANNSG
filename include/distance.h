//
// Created by cmli on 20-6-20.
//

#ifndef ANNSG_DISTANCE_H
#define ANNSG_DISTANCE_H
#include <stdlib.h>

namespace annsg {

    class Distance {
    public:
        virtual float dist(const float* a, const float* b, size_t dim) const = 0;
        virtual ~Distance() {};
    };

    class DistanceIP : public Distance {
    public:
        float dist(const float* a, const float* b, size_t dim) const {
            float ret = 0.0;
            return ret;
        }
    };

    class DistanceL2 : public Distance {
    public:
        float dist(const float* a, const float* b, size_t dim) const {
            float ret = 0.0;
            return ret;
        }
    };

}

#endif //ANNSG_DISTANCE_H
