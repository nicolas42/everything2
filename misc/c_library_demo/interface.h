/* interface.h */
#include <stdio.h>

struct library {
    const int some_value;
    void (*method1)(void);
    void (*method2)(int);
    /* ... */
};

extern const struct library Library;
/* interface.h */
