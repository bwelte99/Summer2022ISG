
#ifndef FUNCTION_KERNELS_H
#define FUNCTION_KERNELS_H

void bright_window(input_window<float> * in, output_window<int32> * out);
void bright_stream(input_stream<int32> * in, output_stream<int32> * out);

#endif
