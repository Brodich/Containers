#include "test_vector.h"
#include "test_list.h"
#include "test_stack.h"
#include "test_queue.h"
#include "test_array.h"
#include "test_associative.h"

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}