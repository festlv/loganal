#include <CException.h>
#include <ftdi.h>
#include "ftdi_reader.h"
#include "config.h"

static struct ftdi_context *ftdi_c;

void ftdi_reader_create() {
    if ((ftdi_c = ftdi_new()) == 0)
    {
        Throw(FTDI_NEW_FAILED);
    }

    if (ftdi_usb_open(ftdi_c, FTDI_VID, FTDI_PID)!=0) {
        ftdi_free(ftdi_c);
        Throw(FTDI_USB_OPEN_FAILED);
    }
    
    if (ftdi_set_baudrate(ftdi_c, 3000000)!=0) {
        ftdi_usb_close(ftdi_c);
        ftdi_free(ftdi_c);
        Throw(FTDI_SET_BAUDRATE_FAILED);
    }
}

void ftdi_reader_destroy() {
    ftdi_usb_close(ftdi_c);
    ftdi_free(ftdi_c);
}

void ftdi_reader_read_data(unsigned char *data_block, 
            unsigned long int num_samples) {

    unsigned long int i=0;
    int bufsize=4096;
    int read_res;
    while (i<num_samples) {
        read_res = ftdi_read_data(ftdi_c, data_block+i, bufsize);
        if (read_res>0)
            i+=read_res;
        else
            Throw(FTDI_READ_DATA_FAILED);

        if ((num_samples - i) < bufsize)
            bufsize = num_samples-i;
    }
}
