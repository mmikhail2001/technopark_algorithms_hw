#include <cmath>

#include <bitset>
#include <iostream>

#include "bit_manager.h"
using std::cout;
using std::endl;
using std::bitset;

bool BitManager::Read(byte &value, std::optional<size_t> n_bits, std::optional<size_t> index_start)
{
    if (n_bits && (*n_bits > 8 || *n_bits <= 0))
    {
        return false;
    }
    if (index_start && (*index_start > n_data_bits - 1 || *index_start < 0))
    {
        return false;
    }
    if (index_start)
    {
        cursor_read = *index_start;
    }
    if (!n_bits)
    {
        *n_bits = 8;
    }
    else if (cursor_read + *n_bits > n_data_bits)
    {
        return false;
    }
    value = 0;
    int rest = cursor_read % 8;
    int index = cursor_read / 8;
    if (8 - (cursor_read % 8) < *n_bits)
    {
        value |= data[index] & ((int)pow(2, 8 - rest) - 1);
        value <<= (*n_bits - (8 - rest));
        value |= (data[index + 1] >> (8 - rest));
    }
    else
    {
        int ones_n_bits = ((int)pow(2, *n_bits) - 1);
        value |= (data[index] >> (8 - rest - *n_bits)) & (ones_n_bits);
    }
    cursor_read += *n_bits;
    return true;
}

bool BitManager::Write(byte value, std::optional<size_t> n_bits, std::optional<size_t> index_start)
{
    
}
