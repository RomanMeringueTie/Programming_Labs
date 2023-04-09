#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

size_t encode_varint(uint32_t value, uint8_t *buf)
{
    assert(buf != NULL);
    uint8_t *cur = buf;
    while (value >= 0x80)
    {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t **bufp)
{
    const uint8_t *cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80)
    {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90)
    {
        return r % 128;
    }
    if (p < 95)
    {
        return r % 16384;
    }
    if (p < 99)
    {
        return r % 2097152;
    }
    return r % 268435455;
}

void valuesInit(uint32_t *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = generate_number();
    }
}

void printarray(uint32_t *array, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d ", array[i]);
}

int encode_file(const char *in_file_name, const char *out_file_name)
{
    FILE *uncompressed;
    uncompressed = fopen(in_file_name, "wb");
    if (!uncompressed)
        return -1;
    FILE *compressed;
    compressed = fopen(out_file_name, "wb");
    if (!compressed)
        return -1;
    uint32_t *values;
    values = malloc(1000000 * sizeof(uint32_t));
    if (!values)
        return -1;
    valuesInit(values, 1000000);
    fwrite(values, sizeof(uint32_t), 1000000, uncompressed);
    uint8_t buf[5] = {};
    uint8_t *cur = malloc(1000000 * 5);
    uint8_t *start = cur;
    size_t size;
    for (int i = 0; i < 1000000; i++)
    {
        size = encode_varint(values[i], buf);
        for (int j = 0; j < size; j++)
        {
            *cur = buf[j];
            cur++;
        }
    }
    fwrite(start, sizeof(uint8_t), cur - start, compressed);
    fclose(compressed);
    fclose(uncompressed);
    return 0;
}

int decode_file(const char *in_file_name, const char *out_file_name)
{
    FILE *uncompressed;
    uncompressed = fopen(in_file_name, "rb");
    FILE *compressed;
    compressed = fopen(out_file_name, "rb");
    fseek(compressed, 0, SEEK_END);
    int size = ftell(compressed);
    fseek(compressed, 0, SEEK_SET);
    uint32_t uncomp[1000000];
    uint8_t *comp = malloc(size);
    fread(comp, 1, size, compressed);
    fread(uncomp, 4, 1000000, uncompressed);
    const uint8_t *cur_comp = comp;
    int count = 0;
    for (int i = 0; i < 1000000; i++)
    {
        if (decode_varint(&cur_comp) == uncomp[i])
            count++;
    }
    if (count == 1000000)
        return 0;
    else
        return -1;
    fclose(compressed);
    fclose(uncompressed);
}

int main()
{
    int ret = encode_file("uncompressed.dat", "compressed.dat");
    if (ret)
        return -1;
    ret = decode_file("uncompressed.dat", "compressed.dat");
    if (ret)
        return -1;
    return 0;
}
