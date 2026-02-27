#pragma once

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
 * Parses flexible date/time strings into a time_t.
 *
 * Returns:
 *   - valid time_t on success
 *   - (time_t)-1 on failure
 */
time_t parse_due_time(const char *input);

time_t vtp(char* data_string);
