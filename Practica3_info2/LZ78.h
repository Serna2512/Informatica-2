#ifndef LZ78_H
#define LZ78_H

struct Entry {
    int prefix;
    char c;
};

int findEntry(Entry* dict, int size, int prefix, char c);
Entry* compressLZ78(const char* input);

#endif // LZ78_H