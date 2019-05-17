#include <glib.h>

void test_wordlen() {
  g_assert(42 == 42);
}

int main(int argc, char **argv){
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/set1/test wordlen", test_wordlen);
    return g_test_run();
}
