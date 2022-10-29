#include "texttypes.h"

bool strmatch(ccpc begin, ccpc end, ccpc str) {
  ccp p = begin;
  ccp q = str;
  for (; p < end and *q and *p == *q; p++, q++);
  return p == end and not *q;
}
