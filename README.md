# ZPL - JSON writer module
[![npm version](https://badge.fury.io/js/zpl_json_write.c.svg)](https://badge.fury.io/js/zpl_json_write.c)

A simple module used for exporting JSON files from zpl_json.c parser.
The exported data is JSON standard friendly.

## Usage
```c
#define ZPL_IMPLEMENTATION
#define ZPLJ_IMPLEMENTATION
#define ZPLJW_IMPLEMENTATION
#include <zpl.h>
#include <zpl_json.h>
#include <zpl_json_write.h>

char *source = "/* this is a comment */ \"+ľščťžýáíé=\": true, \"huge\": 2.2239333e5, // Hello, new comment \n \"array\": [+1,2,-3,4,5],     \"hello\": \"world\", \"abc\": 42.67, \"children\" : { \"a\": 1, \"b\": 2 }";

int main(void) {

    zplj_object_t root = {0};

    isize di = zpl_strlen(source);
    char *d = zpl_malloc(di+1);
    zpl_strncpy(d, source, di);
    d[di] = 0;

    zplj_parse(&root, di, d, zpl_heap_allocator(), true);

    zpljw_dump_json_contents(zpl_file_get_standard(zpl_file_standard_output_ev), &root, 0);

    zplj_free(&root);
    zpl_mfree(d);

    return 0;
}
```
