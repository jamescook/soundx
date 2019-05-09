#include <stdlib.h>
#include <ruby.h>
#include <ctype.h> 

static VALUE m_soundx;


/*
Mapping from wikipedia:

b, f, p, v             => 1
c, g, j, k, q, s, x, z => 2
d, t                   => 3
l                      => 4
m, n                   => 5
r                      => 6
*/

/*
 Pre-computed mapping of a-z to the above
 table.
*/
static const unsigned char mapping[128] = {
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,  '0',
 '1',  '2',  '3',  '0',  '1',  '2',  '0',
 '0',  '2',  '2',  '4',  '5',  '5',  '0',
 '1',  '2',  '6',  '2',  '3',  '0',  '1',
 '0',  '2',  '0',  '2', 0xFE, 0xFE, 0xFE,
0xFE, 0xFE
};

static VALUE
rb_soundx(int argc, VALUE* argv, VALUE self)
{
  VALUE input;
  unsigned char* src;
  int written = 0;
  size_t srclen;
  char *dest = malloc(5);

  if (!dest) {
    rb_raise(rb_eNoMemError, "malloc failed");
  }

  rb_scan_args(argc, argv, "1", &input);

  if (TYPE(input) != T_STRING) {
    rb_raise(rb_eTypeError, "expected a String");
  }

  srclen = RSTRING_LEN(input);
  src = (unsigned char *) StringValueCStr(input);

  dest[0] = toupper(src[0]);

  for(size_t i = 1; i <= srclen; i++) {
    if (written >= 3) {
      break;
    }

    if ('\0' == src[i]) {
      break;
    }

    if (src[i] > 128) {
      free(dest);
      rb_raise(rb_eArgError, "non-ASCII character found");
      break;
    }

    unsigned char current = tolower(src[i]);

    unsigned char match = mapping[ current ];
    if (0xFE == match) {
      continue;
    }

    // Skip if previous character is the same
    if (dest[written] == match) {
      continue;
    }

    // We landed on a vowel-like character,
    // so skip to the next char
    if ('0' == match) {
      continue;
    }

    dest[written+1] = mapping[ current ];

    written++;
  }

  // Pad at most three '0' characters
  // to handle really short names
  if (written < 3) {
    for( int i = (3-written); i > 0; i--) {
      dest[written+i] = '0';
    }
  }

  dest[4] = '\0';

  VALUE rbString = rb_str_new_cstr(dest);
  free(dest);

  return rbString;
}
void
Init_soundx() {
  m_soundx = rb_define_module("SoundX");
    
  rb_define_module_function(m_soundx, "encode", rb_soundx, -1);
}
