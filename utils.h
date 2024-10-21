#ifndef UTILS_H
#define UTILS_H

//#define DEBUG_FPRINTF

#ifdef DEBUG_FPRINTF
    #define DEB_PR(...) fprintf(stderr, __VA_ARGS__);
#else
    #define DEB_PR(...)
#endif

#endif // UTILS_H