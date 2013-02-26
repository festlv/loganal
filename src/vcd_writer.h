#ifndef __VCD_WRITER__H
#define __VCD_WRITER__H

#include <stdio.h>

extern void vcd_writer_write_header(FILE *fp, int sample_rate);
extern void vcd_writer_write_data(FILE *fp, unsigned char *data_block, unsigned long int num_samples);

#endif
