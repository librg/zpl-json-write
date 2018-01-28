/*

  ZPL - JSON parser module

  Usage:
  #define ZPLJW_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:

  #define ZPLJW_IMPLEMENTATION
  #include"zpl_json_write.h"

  Dependencies:
  zpl_json.h

  Credits:
  Dominik Madarasz (GitHub: zaklaus)

  Version History:
  1.0.0 - Initial version

    
    Copyright 2017 Dominik Madarász
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License. 
*/

#ifndef ZPL_INCLUDE_ZPL_JSON_WRITE_H
#define ZPL_INCLUDE_ZPL_JSON_WRITE_H

#ifdef __cplusplus
extern "C" {
#endif

    ZPL_DEF void zpljw_dump_json_contents(zpl_file_t *f, zplj_object_t *o, isize indent);

#ifdef __cplusplus
}
#endif

#if defined(ZPLJW_IMPLEMENTATION) && !defined(ZPLJW_IMPLEMENTATION_DONE)
#define ZPLJW_IMPLEMENTATION_DONE

#ifdef __cplusplus
extern "C" {
#endif

#define zpljw__ind(x) for (int i = 0; i < x; ++i) zpl_fprintf(f, " ");

    void zpljw__dump_value(zpl_file_t *f, zplj_object_t *o, isize indent, b32 is_inline, b32 is_last) {
        zplj_object_t *node = o;
        indent+=4;

        if (!is_inline) {
            zpljw__ind(indent);
            zpl_fprintf(f, "\"%s\": ", node->name);
        }

        switch (node->type) {
        case zplj_type_string_ev: {
            zpl_fprintf(f, "\"%s\"", node->string);
        }break;

        case zplj_type_array_ev: {
            zpl_fprintf(f, "[");
            isize elemn = zpl_array_count(node->elements);
            for (int j = 0; j < elemn; ++j) {
                zpljw__dump_value(f, node->elements + j, -4, true, true);

                if (j < elemn-1) {
                    zpl_fprintf(f, ", ");
                }
            }
            zpl_fprintf(f, "]");
        }break;

        case zplj_type_integer_ev: {
            zpl_fprintf(f, "%lld", node->integer);
        }break;

        case zplj_type_real_ev: {
            zpl_fprintf(f, "%.3llf", node->real);
        }break;

        case zplj_type_object_ev: {
            zpljw_dump_json_contents(f, node, indent);
        }break;

        case zplj_type_constant_ev: {
            /**/ if (node->constant == zplj_constant_true_ev) {
                    zpl_fprintf(f, "true");
                }
                else if (node->constant == zplj_constant_false_ev) {
                    zpl_fprintf(f, "false");
                }
                else if (node->constant == zplj_constant_null_ev) {
                    zpl_fprintf(f, "null");
                }
        }break;
        }

        if (!is_inline) {

            if (!is_last) {
                zpl_fprintf(f, ",\n");
            }
            else {
                zpl_fprintf(f, "\n");
            }
        }
    }

    void zpljw_dump_json_contents(zpl_file_t *f, zplj_object_t *o, isize indent) {
        zpljw__ind(indent-4);
        zpl_fprintf(f, "{\n");
        isize cnt = zpl_array_count(o->nodes);

        for (int i = 0; i < cnt; ++i) {
            if (i < cnt-1) {
                zpljw__dump_value(f, o->nodes + i, indent, false, false);
            }
            else {
                zpljw__dump_value(f, o->nodes + i, indent, false, true);
            }
        }

        zpljw__ind(indent);

        if (indent > 0) {
            zpl_fprintf(f, "}");
        }
        else {
            zpl_fprintf(f, "}\n");
        }
    }

#undef zpljw__ind

#ifdef __cplusplus
}
#endif

#endif // ZPLJW_IMPLEMENTATION

#endif // ZPL_INCLUDE_ZPL_JSON_WRITE_H
