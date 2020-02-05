#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <vector>

namespace tools {
    void printa(int* a, int len) {
        printf("[ ");
        for (int i = 0; i < len-1; i++) {
            printf("%d, ", a[i]);
        }
        printf("%d ]\n", a[len-1]);
    }

    void printv(std::vector<int> v) {
        printf("{[ ");
        for (int i = 0; i < v.size()-1; i++) {
            printf("%d, ", v.at(i));
        }
        printf("%d ]}\n", v.at(v.size()-1));
    }

    void printl(char c, int n) {
        for (int i = 0; i < n; i++) printf("%c", c);
        printf("\n");
    }
}

#endif // TOOLS_H
