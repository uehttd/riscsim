//
// Created by yury Pavlyuk on 23.04.18.
//
#include "limits.h"
#include "stdint.h"

int main(){
    int32_t a, b, r;
    a = INT_MAX;
    b = INT_MAX;
    uint32_t c;
    c = UINT_MAX;

    r = a + b;
    r += c;

    return r;
}
