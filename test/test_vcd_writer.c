#include "vcd_writer.h"
#include <stdio.h>
#include <string.h>
#include <unity.h>

FILE *tmpf;

void setUp() {
    tmpf = tmpfile();
}

void tearDown() {
    fclose(tmpf);
}

void test_header_written() {
    vcd_writer_write_header(tmpf, 1000000);
    fseek(tmpf, 0, SEEK_SET);
    unsigned char buf[40];
    fgets(buf, 40, tmpf);
    TEST_ASSERT_NOT_NULL(strstr(buf, "$date"));
    TEST_ASSERT_NOT_NULL(strstr(buf, "$end"));
    fgets(buf, 40, tmpf);
    TEST_ASSERT_NOT_NULL(strstr(buf, "$version"));
    fgets(buf, 40, tmpf);
    printf("%s\n", buf);
    TEST_ASSERT_NOT_NULL(strstr(buf, "$timescale"));
    fgets(buf, 40, tmpf);
    TEST_ASSERT_NOT_NULL(strstr(buf, "$var wire 8 ! data $end"));
    fgets(buf, 40, tmpf);
    TEST_ASSERT_NOT_NULL(strstr(buf, "$enddefinitions $end"));
}

void test_data_write() {
    unsigned char data[4] = {0xff, 0x00, 0x0f, 0x00};
    vcd_writer_write_data(tmpf, data, 4UL);
    fseek(tmpf, 0, SEEK_SET);
    
    unsigned char buf[20];
    fgets(buf,20, tmpf);
    TEST_ASSERT_NOT_NULL(strstr(buf, "#0"));
    fgets(buf,20,tmpf);
    TEST_ASSERT_EQUAL_STRING("b11111111 !\n", buf);
    fgets(buf, 20, tmpf);
    TEST_ASSERT_EQUAL_STRING("#1\n", buf);
    fgets(buf, 20, tmpf);
    TEST_ASSERT_EQUAL_STRING("b00000000 !\n", buf);
    fgets(buf, 20, tmpf);
    fgets(buf, 20, tmpf);
    TEST_ASSERT_EQUAL_STRING("b00001111 !\n", buf);
    fgets(buf, 20, tmpf);
    fgets(buf, 20, tmpf);
    TEST_ASSERT_EQUAL_STRING("b00000000 !\n", buf);
}
