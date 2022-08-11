/* A simple kernel
 */
#include <adf.h>
#include <aie_api/aie.hpp>
#include "aie_api/aie_adf.hpp"
#include "aie_api/utils.hpp"
#include "include.h"

//window-based I/O
void bright_window(input_window<float> * in, output_window<int32> * out) {

	for (unsigned i=0; i<NUM_SAMPLES; i++) {

		//read in pixels and convert to float
    	aie::vector<float, 4> pixels_f = window_readincr_v<4>(in);

    	//create array of scalars
    	aie::vector<float, 4> scalars = aie::broadcast<float, 4>(1.5);

    	//multiply the pixels by the scalar and convert back to integers
    	pixels_f = aie::mul(pixels_f, scalars);
    	aie::vector<int32, 4>pixels = aie::to_fixed(pixels_f);

    	//take the min of the scaled pixels and 255
    	pixels = aie::min(pixels, 255);

		//write pixels to output window
    	window_writeincr(out, pixels);
    }
}

//stream-based I/O
void bright_stream(input_stream<int32> * in, output_stream<int32> * out){

	const int VEC_SIZE = 8;

	aie::vector<float, VEC_SIZE> pixels_f;

	for (unsigned i = 0; i < NUM_SAMPLES; i++){

		//read pixels as stream inputs
		for (unsigned j = 0; j < VEC_SIZE; j++){
			pixels_f[j] = get_ss(0);
		}

		//create array of scalars & multiply by pixels
		aie::vector<float, VEC_SIZE> scalars = aie::broadcast<float, VEC_SIZE>(1.5);
		pixels_f = aie::mul(pixels_f, scalars);

		//convert to scalars & output to stream
		aie::vector<int32, VEC_SIZE> pixels = aie::to_fixed(pixels_f);
		pixels = aie::min(pixels, 255);

		for(unsigned j = 0; j < VEC_SIZE; j++){
			writeincr(out, pixels[j]);
		}

		/*
		int32 pixel = get_ss(0); //retrieve pixel from stream

		pixel = pixel * 1.5;	// inefficient scaling that doesn't use vector operations
		if (pixel > 255){
			pixel = 255;
		}
		writeincr(out, pixel);
		*/
	}
}
