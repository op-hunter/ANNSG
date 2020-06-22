//
// Created by cmli on 20-6-20.
//

#ifndef ANNSG_DISTANCE_H
#define ANNSG_DISTANCE_H
#include <stdlib.h>
#include <iostream>

namespace annsg {

    class Distance {
    public:
        virtual float dist(const float* a, const float* b, size_t dim, size_t offseta = 0, size_t offsetb = 0) const = 0;
        virtual ~Distance() {};
    };

    class DistanceIP : public Distance {
    public:
        float dist(const float* a, const float* b, size_t dim, size_t offseta = 0, size_t offsetb = 0) const {
            float ret = 0.0;
            return ret;
        }
    };

    class DistanceL2 : public Distance {
    public:
        DistanceL2(size_t n) {
            pnorm_ = (char *) malloc(sizeof(float) * n);
            if (!pnorm_) {
                std::cout << "malloc space 4 norm failed!" << std::endl;
            }
            dip_ = new DistanceIP();
        }
        ~DistanceL2() {
            if (pnorm_)
                free(pnorm_);
            delete dip_;
        }
        float dist(const float* a, const float* b, size_t dim, size_t offseta = 0, size_t offsetb = 0) const {
            float ret = *((float*)pnorm_ + offseta) + *((float*)pnorm_ + offsetb);
            return ret - dip_->dist(a, b, dim) * 2;
        }
        DistanceIP *dip_;
        char *pnorm_;
    };

}

#endif //ANNSG_DISTANCE_H
