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
  VALUE rbDestString;
  unsigned char* src;
  unsigned char written = 0; // Should not exceed 3, so 8 bits is plenty.
  size_t srclen;
  size_t i; // for looping the src
  unsigned char current;
  unsigned char match;

  /*
   Destination is padded with up to 3 trailing zeros
   for short names.
  */
  char dest[5] = {'0', '0', '0', '0', '\0'};

  rb_scan_args(argc, argv, "1", &input);

  Check_Type(input, T_STRING);

  srclen = RSTRING_LEN(input);
  src = (unsigned char *) StringValueCStr(input);

  dest[0] = toupper(src[0]);

  for(i = 1; i < srclen; i++) {
    if (written >= 3) {
      break;
    }

    if (src[i] > 128) {
      rb_raise(rb_eArgError, "non-ASCII character found");
      break;
    }

    current = tolower(src[i]);

    match = mapping[ current ];

    if (0xFE == match) {
      continue;
    }

    // The 2nd character must still respect
    // the 'double code number' rule.
    if (1 == i) {
      if (match == mapping[tolower(src[0])]) {
        continue;
      }
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

  rbDestString = rb_str_new_cstr(dest);

  return rbDestString;
}
void
Init_soundx() {
  m_soundx = rb_define_module("SoundX");
    
  rb_define_module_function(m_soundx, "encode", rb_soundx, -1);
}
