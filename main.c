// Johnicholas mostly just copied this out of the Ceu manual.

#include "types.h" // as illustrated above in "Types"
#include <stdio.h>

int ceu_is_running; // detects program termination

// The signature is slightly different if you are compiling without trace turned on.
// The manual has a ceu_callback_main with trace turned on, a four-argument function.
// We want a ceu_callback_main without trace turned on, a three-argument function.
int ceu_callback_main (int cmd, tceu_callback_val p1, tceu_callback_val p2) 
{
  int is_handled = 0;
  switch (cmd) {
  case CEU_CALLBACK_TERMINATING:
    ceu_is_running = 0;
    is_handled = 1;
    break;
  case CEU_CALLBACK_OUTPUT:
    if (p1.num == CEU_OUTPUT_O) {
      int val = *((int*)p2.ptr);
      if (val == -1) {
	printf("Fizz");
      } else if (val == -2) {
	printf("Buzz");
      } else if (val == -3) {
	printf("\n");
      } else {
	printf("%d", val);
      }
      is_handled = 1;
    }
    break;
  }
  // The meaning of a ceu callback return code is "I handled this".
  // It is used in order to have a bunch of callbacks each specializing in a different
  // subset of output events. Then the Ceu runtime, in order to send a particular output event,
  // will walk through the callbacks up until one of them says "I handled this".
  // In this case, this is the only callback function, and so in some sense it doesn't
  // matter what we return? But returning "is_handled" works for more complicated cases,
  // too.
  return is_handled;
}

int main (int argc, char* argv[])
{
  ceu_is_running = 1;
  tceu_callback cb = { &ceu_callback_main, NULL };
  ceu_start(&cb, argc, argv);
  while (ceu_is_running) {
    int v;
    if (scanf("%d", &v) == 1) {
      ceu_input(CEU_INPUT_I, &v);
    }
    ceu_input(CEU_INPUT__ASYNC, NULL);
  }
  ceu_stop();
}
