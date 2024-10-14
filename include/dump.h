#ifndef PROGRAMMINGSEMINARS_DUMP_H
#define PROGRAMMINGSEMINARS_DUMP_H

#include <stdio.h>

void dump_byte(
    unsigned char byte_value,
    FILE *output_stream);

void dump_bytes(
    unsigned char const *bytes_addr,
    size_t bytes_count,
    FILE *output_stream);

#endif //PROGRAMMINGSEMINARS_DUMP_H