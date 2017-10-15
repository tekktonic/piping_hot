#ifndef PARSE_H
#define PARSE_H

#include "dtype.h"

struct parsed
{
    char *cmd;
    List args;
};

enum type
{
    UTF8,
    ASCII
};

bool isascii(unsigned char u8char);

enum type strtype(const char *str);

struct parsed parse(char *string);
#endif
