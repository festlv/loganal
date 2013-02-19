#include <libftdi1/ftdi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

const int SAMPLE_RATE=1000000;

const int SAMPLE_MILLISECONDS = 1000;
double elapsed; // in milliseconds

clock_t start, end;

unsigned char *data_ptr;

int main(void) {
    int ret, i;
    struct ftdi_context *ftdi;
    struct ftdi_device_list  *curdev;
    int retval = EXIT_SUCCESS;

    if ((ftdi = ftdi_new()) == 0)
    {
        fprintf(stderr, "ftdi_new failed\n");
        return EXIT_FAILURE;
    }
    printf("ftdi_new() called\n");
    if (ftdi_usb_open(ftdi, 0x403,0x6001)!=0) {
        fprintf(stderr, "Cannot find USB device with VID:0x0403, PID:0x6001\n");
        retval=EXIT_FAILURE;
        goto deinit;
    }
    printf("ftdi_open()\n");
    
    if (ftdi_set_baudrate(ftdi, 3000000)!=0) {
        fprintf(stderr, "Cannot set baudrate\n");
        retval=EXIT_FAILURE;
        goto free;
    }
    printf("ftdi_set_baudrate()\n");
    
    data_ptr = calloc(SAMPLE_RATE/1000*SAMPLE_MILLISECONDS, sizeof(unsigned char));
    printf("calloc\n");
    int read_data_count;
    int target_samples = SAMPLE_RATE/1000*SAMPLE_MILLISECONDS;
    int bufsize = 4096;
    start = clock();
    
   

    i=0;
    while (i<target_samples) {
        read_data_count= ftdi_read_data(ftdi, data_ptr + i, 4096);
        if (read_data_count>0)
            i+=read_data_count;
        else
        {
            fprintf(stderr, "Read error\n");
            goto free;
        }
        if ((target_samples - i)<bufsize)
            bufsize = target_samples-i;
    
    }
    /* do some work */
    
    end = clock();
    
    elapsed = ((double) (end - start) * 1000) / CLOCKS_PER_SEC;
    printf("Sample time: %f\n", elapsed);     
        
    free:
    ftdi_usb_close(ftdi);

    deinit:
    ftdi_free(ftdi);

    return retval;
}


