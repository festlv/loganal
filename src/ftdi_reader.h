#ifndef __FTDI_READER__H
#define __FTDI_READER__H

#include <CException.h>


extern void ftdi_reader_create();

//reads num_samples synchronously from ftdi device and saves them in buffer pointed by data_block.
//caller is responsible for allocating buffer

extern void ftdi_reader_read_data(unsigned char *data_block, unsigned long int num_samples);

extern void ftdi_reader_destroy();

#endif
