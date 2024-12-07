#ifndef __SHOT__
#define __SHOT__

typedef struct Shot {
  float x, y;
  int is_fired;
  int current_frame;
} Shot;

#endif  // __SHOT__