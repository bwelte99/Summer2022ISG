
#include <adf.h>
#include "kernels.h"
#include "project.h"

using namespace adf;

brightGraph mygraph;

int main(void) {
  mygraph.init();
  mygraph.run(1);
  mygraph.end();
  return 0;
}
