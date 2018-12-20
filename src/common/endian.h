//
// Created by me on 20/12/18.
//

#ifndef OPEN_OBD2_ENDIAN_H
#define OPEN_OBD2_ENDIAN_H


#include <climits>
#include <cstddef>

template<typename T>
T swapEndian(T u) {
    static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");

    union {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++) {
        dest.u8[k] = source.u8[sizeof(T) - k - 1];
    }

    return dest.u;
}

#endif //OPEN_OBD2_ENDIAN_H
