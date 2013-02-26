#include <stdio.h>
#include <stdlib.h>
#include "ftdi_reader.h"
#include <CException.h>
#include "vcd_writer.h"


const int SAMPLE_RATE=1000000;

const int SAMPLE_MILLISECONDS = 1000;
double elapsed; // in milliseconds


int main(void) {
    long int num_samples = (SAMPLE_RATE/1000)*SAMPLE_MILLISECONDS;
    unsigned char *data_ptr = calloc(num_samples, sizeof(unsigned char));
    int retval=0;
    

    CEXCEPTION_T e;
    Try {
        ftdi_reader_create();
        ftdi_reader_read_data(data_ptr, num_samples);
        ftdi_reader_destroy();
        vcd_writer_write_header(stdout, SAMPLE_RATE);
        vcd_writer_write_data(stdout, data_ptr, num_samples); 

    } Catch (e) {
        printf("Exception thrown. Error code: %d\n", e);
        return e;
    }

    
    return retval;
}


