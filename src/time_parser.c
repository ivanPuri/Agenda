#define _XOPEN_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static int try_fmt(const char *s, const char *fmt, struct tm *tm_out) {
    struct tm tm = *tm_out;
    char *end = strptime(s, fmt, &tm);
    if (!end) return 0;

    while (*end && isspace((unsigned char)*end)) end++;
    if (*end != '\0') return 0;   // reject partial matches

    *tm_out = tm;
    return 1;
}

time_t parse_due_time(const char *input) {
    char s[256];
    strncpy(s, input, sizeof(s) - 1);
    s[sizeof(s) - 1] = '\0';
    s[strcspn(s, "\n")] = '\0';  // remove newline

    time_t now = time(NULL);
    struct tm tm = *localtime(&now);

    // default time if not provided
    tm.tm_hour = 0;
    tm.tm_min  = 0;
    tm.tm_sec  = 0;
    tm.tm_isdst = -1;

    // simple special cases
    if (strcasecmp(s, "noon") == 0) {
        tm.tm_hour = 12;
        return mktime(&tm);
    }

    if (strcasecmp(s, "midnight") == 0) {
        tm.tm_hour = 0;
        return mktime(&tm);
    }

    const char *formats[] = {
        "%Y-%m-%d %H:%M",    // 2026-03-03 21:00
        "%Y-%m-%d",          // 2026-03-03

        "%b %d %I%p",        // Mar 3 9PM
        "%b %d %I %p",       // Mar 3 9 PM
        "%B %d %I%p",        // March 3 9PM
        "%B %d %I %p",       // March 3 9 PM

        "%a %I%p",           // Fri 9PM
        "%a %I %p",          // Fri 9 PM
        "%A %I%p",           // Friday 9PM
        "%A %I %p",          // Friday 9 PM

        NULL
    };

    for (int i = 0; formats[i]; i++) {
        struct tm candidate = tm;
        if (try_fmt(s, formats[i], &candidate)) {
            time_t t = mktime(&candidate);
            if (t != (time_t)-1)
                return t;
        }
    }

    return (time_t)-1;  // failure
}

//novice time parse
//voon time parse
time_t vtp(char* date_string){
    const char *format = "%d %H:%M";
    struct tm tm;

    tm.tm_isdst = -1; 

    // Parse the string into the struct tm
    char *remaining_string = strptime(date_string, format, &tm);

    if (remaining_string == NULL || *remaining_string != '\0') {
        return (time_t) -1;
    }

    time_t t = mktime(&tm);

    if (t == -1) {
        return (time_t) -1;
    }
    return t;
}
