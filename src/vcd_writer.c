#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "vcd_writer.h"

void vcd_writer_write_header(FILE *fp, int sample_rate) {
    char time_str[50];
    time_t t;
    struct tm *tmp;
    t = time(NULL);
    tmp = localtime(&t);
    strftime(time_str, sizeof(time_str), "%b %d %Y %H:%M:%S", tmp);
    fprintf(fp, "$date %s $end\n", time_str);
    fprintf(fp, "$version Hspacelv LA v0.1 $end\n");
    fprintf(fp, "$timescale %d us $end\n", (1/sample_rate)*1000000);
    fprintf(fp, "$var wire 8 ! data $end\n");
    fprintf(fp, "$enddefinitions $end\n");
}
static byte_to_bin(char *buf, unsigned char byte) {
    int z, i=0;
    for (z=128;z>0;z=z>>1) {
        buf[i] = ((byte & z)==z) ? '1' : '0';
        i++;
    }
    buf[i]='\0';
}
void vcd_writer_write_data(FILE *fp, unsigned char *data_block,
        unsigned long int num_samples) {
   static unsigned char buf[8];
   int i;
   for (i=0;i<num_samples;i++) {
       fprintf(fp, "#%d\n", i);
       byte_to_bin(buf, data_block[i]);
       fprintf(fp, "b%s !\n", buf);
   }
}
