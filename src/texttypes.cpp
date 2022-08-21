#include "texttypes.h"

bool strmatch(ccpc begin, ccpc end, ccpc str) {
  ccp p;
  ccp q;
  for (p = begin, q = str; p < end and *q and *p == *q; p++, q++);
  return p == end and not *q;
}
