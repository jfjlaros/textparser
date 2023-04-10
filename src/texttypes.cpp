#include "texttypes.h"


bool strmatch(CCPC begin, CCPC end, CCPC str) {
  CCP p {begin};
  CCP q {str};
  for (; p < end and *q and *p == *q; ++p, ++q);
  return p == end and not *q;
}
