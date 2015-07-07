#ifndef JAKOPTER_COORDS_H
#define JAKOPTER_COORDS_H

#include "com_channel.h"
#include "com_master.h"

/* Max number of digit into an integer. */
#define INT_LEN 11
#define FLOAT_LEN 10

#define COORDS_INTERVAL 	1 // interval in seconds
/*size of float digits plus 3 spaces and \0*/
#define COORDS_BUF_SIZE FLOAT_LEN*3+4
#define COORDS_FILENAME "/tmp/jakopter_coords.txt"
#define TSTAMP_LEN 2*INT_LEN+2

int jakopter_init_coords();
int jakopter_stop_coords();

const char* jakopter_log_coords();


#endif