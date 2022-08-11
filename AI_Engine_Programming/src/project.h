
#include <adf.h>
#include "kernels.h"

using namespace adf;

class brightGraph : public adf::graph {
private:
  kernel first;
public:
  input_plio  in;
  output_plio out;
  brightGraph(){

    //stream-based access
	/*
    first = kernel::create(bright_stream);

    in  = input_plio::create(plio_32_bits, "data/input.txt");
    out = output_plio::create(plio_32_bits, "data/stream_output.txt");

    connect < stream > net0 (in.out[0], first.in[0]);
    connect < stream > net1 (first.out[0], out.in[0]);
	*/

    //window-based access
    first = kernel::create(bright_window);

    in  = input_plio::create(plio_32_bits, "data/input.txt");
    out = output_plio::create(plio_32_bits, "data/window_output.txt");

    connect< window<32> > net0 (in.out[0], first.in[0]);	//previously 32 byte windows
    connect< window<32> > net2 (first.out[0], out.in[0]);
	

    source(first) = "kernels/kernels.cc";

    runtime<ratio>(first) = 0.1;

  }
};
