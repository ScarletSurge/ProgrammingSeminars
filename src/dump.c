#include "../include/dump.h"

#define BITS_IN_BYTE 8

void dump_byte(
    unsigned char byte_value,
    FILE *output_stream)
{
    int i;

    for (i = 0; i < BITS_IN_BYTE; ++i)
    {
        fprintf(output_stream, "%d", (byte_value >> (BITS_IN_BYTE - 1 - i)) & 1);
    }
}

void dump_bytes(
    unsigned char const *bytes_addr,
    size_t bytes_count,
    FILE *output_stream)
{
    int i;

    for (i = 0; i < bytes_count; ++i)
    {
        dump_byte(*(bytes_addr + i), output_stream);

        if (i != bytes_count - 1)
        {
            fprintf(output_stream, " ");
        }
    }
}