#include <cstdlib>
#include <cmath>
#include <cstdio>

typedef struct {
    /* because checking floating point equality is tricky, store the
     * confidence as int(confidence*100) */
    int conf;
    double zval;
} ztable_entry;

/* cdf(critical value) = 0.5 + convidence / 2 */
/* critical value = cdf^{-1}(0.5 + confidence / 2) */
static ztable_entry z_table[] = {
    { 99, 2.58  },
    { 98, 2.33  },
    { 95, 1.96  },
    { 90, 1.645 },
};

#define Z_TABLE_LEN  sizeof(z_table)/sizeof(z_table[0])

double critval(int conf) {
    for(size_t i=0; i < Z_TABLE_LEN; ++i) {
        if (z_table[i].conf == conf) {
            return z_table[i].zval;
        }
    }
    return NAN;
}

void list_confidence(FILE* os, const char* delim=", ") {
    ztable_entry* ptr = z_table;
    while( ptr < z_table + Z_TABLE_LEN) {
        fprintf(os, ".%d", ptr->conf);
        if (ptr < z_table + Z_TABLE_LEN -1)
            fputs(delim, os);
        ++ptr;
    }
}
