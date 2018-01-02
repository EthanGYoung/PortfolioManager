//
// Created by Ethan Young on 1/1/18.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <ctime>
#include "Fund.h"


class Algorithm {
public:
    Algorithm();
    virtual ~Algorithm();
    void predictDate(Fund *fund, tm Date, Stock *st);
};


#endif //ALGORITHM_H
