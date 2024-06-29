#include <glib.h>

#include "poet.h"

/*
 * TODO: Call free() in the tests.
 * But first check with valgrind how/if we leak memory.
 */
void test_wordlen() {
  Poet *p = NULL;
  p = Poet_new("Frobisher", 3);
  g_assert(p != NULL);
}

void test_wordlen_fail() {
  if (g_test_subprocess()) {
    Poet *p = NULL;
    p = Poet_new("Frodo", 9);
  }
  g_test_trap_subprocess(NULL, 0, 0);
  g_test_trap_assert_failed();
  g_test_trap_assert_stderr("Text to short for given word length\n");
}

void test_next() {
  Poet *p = NULL;
  p = Poet_new("abcdabceabcfabc", 3);
  char n = 0;

  /*
   * Advance three times to eat up the "abc".
   */
  n = Poet_next(p);
  n = Poet_next(p);
  n = Poet_next(p);

  /*
   * The next value must be one of the possible successors.
   */
  n = Poet_next(p);
  g_assert(n == 'd' || n == 'e' || n == 'f' || n == '\0');
}

/*
 * Test expectation about length of output.
 */
void test_length_of_output() {
  Poet *p = Poet_new("abcdabceabcfabc", 3);
  g_assert(strlen(Poet_output(p)) % 4 == 3);
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/set1/test wordlen", test_wordlen);
    g_test_add_func("/set1/test wordlen fail", test_wordlen_fail);
    g_test_add_func("/set1/test next", test_next);
    g_test_add_func("/set1/test length of output", test_length_of_output);
    return g_test_run();
}
