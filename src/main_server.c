#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdint.h>

#include "iperf_api.h"

int main() {
    int port;
    struct iperf_test *test;
    int consecutive_errors;

    port = 5555;

    test = iperf_new_test();
    if (test == NULL) {
        printf("failed to create test\n");
        exit(-1);
    }
    iperf_defaults(test);
    iperf_set_test_role(test, 's');
    iperf_set_test_server_port(test, port);
    iperf_set_test_bind_address(test, "0.0.0.0");
    consecutive_errors = 0;
    for (;;) {
        if (iperf_run_server(test) < 0) {
            printf("error - %s\n\n", iperf_strerror(i_errno));
            ++consecutive_errors;
            if (consecutive_errors >= 5) {
                printf("too many errors, exiting\n");
                break;
            }
        } else
            consecutive_errors = 0;
        iperf_reset_test(test);
    }

    iperf_free_test(test);
    return 0;
}
