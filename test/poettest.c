#include <glib.h>

#include "poet.h"

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

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/set1/test wordlen", test_wordlen);
    g_test_add_func("/set1/test wordlen fail", test_wordlen_fail);
    return g_test_run();
}
