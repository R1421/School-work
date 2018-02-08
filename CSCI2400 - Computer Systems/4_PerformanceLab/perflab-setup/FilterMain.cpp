#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
//############################################################################################
    for (int i=0; i < size; i++) {
      filter->setRDIM0(i);
      for (int j=0; j < size; j++) {
        int value;
        input >> value;
        //filter -> set(i,j,value);
        filter->set0(j,value);
      }
    }
//############################################################################################

    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;

//################################################################################################################################
  int divisor = filter->getDivisor();
  int filterSize = filter->getSize();
  int width = (input->width)-2;
  int height = (input->height)-2;


for(int col = 0; col < width; col = col + 1) {
    //for(int plane = 0; plane < 3; plane++) {
        for(int row = 0; row < height ; row = row + 1) {


            int valuea = 0;
            int value1a = 0;
            int value2a = 0;
            int value3a = 0;

            int valueb = 0;
            int value1b = 0;
            int value2b = 0;
            int value3b = 0;

            int valuec = 0;
            int value1c = 0;
            int value2c = 0;
            int value3c = 0;

            for (int i = 0; i < filterSize; i += 3) {
                filter->setRDIM(i);
                for (int j = 0; j < filterSize; j += 3) {
                    value1a = value1a + (input->color[col + j    ][0][row + i] * filter->get0(j  )) + (input->color[col + j    ][0][row + i + 1] * filter->get1(j  )) + (input->color[col + j    ][0][row + i + 2] * filter->get2(j  ));
                    value2a = value2a + (input->color[col + j + 1][0][row + i] * filter->get0(j+1)) + (input->color[col + j + 1][0][row + i + 1] * filter->get1(j+1)) + (input->color[col + j + 1][0][row + i + 2] * filter->get2(j+1));
                    value3a = value3a + (input->color[col + j + 2][0][row + i] * filter->get0(j+2)) + (input->color[col + j + 2][0][row + i + 1] * filter->get1(j+2)) + (input->color[col + j + 2][0][row + i + 2] * filter->get2(j+2));

                    value1b = value1b + (input->color[col + j    ][1][row + i] * filter->get0(j  )) + (input->color[col + j    ][1][row + i + 1] * filter->get1(j  )) + (input->color[col + j    ][1][row + i + 2] * filter->get2(j  ));
                    value2b = value2b + (input->color[col + j + 1][1][row + i] * filter->get0(j+1)) + (input->color[col + j + 1][1][row + i + 1] * filter->get1(j+1)) + (input->color[col + j + 1][1][row + i + 2] * filter->get2(j+1));
                    value3b = value3b + (input->color[col + j + 2][1][row + i] * filter->get0(j+2)) + (input->color[col + j + 2][1][row + i + 1] * filter->get1(j+2)) + (input->color[col + j + 2][1][row + i + 2] * filter->get2(j+2));

                    value1c = value1c + (input->color[col + j    ][2][row + i] * filter->get0(j  )) + (input->color[col + j    ][2][row + i + 1] * filter->get1(j  )) + (input->color[col + j    ][2][row + i + 2] * filter->get2(j  ));
                    value2c = value2c + (input->color[col + j + 1][2][row + i] * filter->get0(j+1)) + (input->color[col + j + 1][2][row + i + 1] * filter->get1(j+1)) + (input->color[col + j + 1][2][row + i + 2] * filter->get2(j+1));
                    value3c = value3c + (input->color[col + j + 2][2][row + i] * filter->get0(j+2)) + (input->color[col + j + 2][2][row + i + 1] * filter->get1(j+2)) + (input->color[col + j + 2][2][row + i + 2] * filter->get2(j+2));
                }
            }

            valuea = value1a+value2a+value3a;
            valuea = valuea / divisor;

            valueb = value1b+value2b+value3b;
            valueb = valueb / divisor;

            valuec = value1c+value2c+value3c;
            valuec = valuec / divisor;


            if ( valuea  < 0 ) { valuea = 0; }
            if ( valuea  > 255 ) { valuea = 255; }

            if ( valueb  < 0 ) { valueb = 0; }
            if ( valueb  > 255 ) { valueb = 255; }

            if ( valuec  < 0 ) { valuec = 0; }
            if ( valuec  > 255 ) { valuec = 255; }

            output -> color[col][0][row] = valuea;
            output -> color[col][1][row] = valueb;
            output -> color[col][2][row] = valuec;
        }
    //}
  }

//################################################################################################################################

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
