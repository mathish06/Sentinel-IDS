#include <Arduino.h>

#ifndef WIFI_HEADER_
    #define WIFI_HEADER_

    typedef struct {
    uint8_t frame_control[2];
    uint8_t duration[2];
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    uint8_t seq_ctrl[2];
} wifi_header_t;

#endif