/*
 * Unit tests for the timer formatting in time.c.
 *
 * "time.h" below is smk's own header, not the system one. It is included
 * with quotes so it resolves next to this file; do not add -I. to the
 * compile, or cgreen's <time.h> would resolve to it too.
 */

#include <cgreen/cgreen.h>

#include "time.h"

/* A minute is 60 seconds of TI_HZ ticks each. */
#define MINUTES(m) ((m) * 60 * TI_HZ)

Describe(TiStr);
BeforeEach(TiStr) {}
AfterEach(TiStr) {}

Ensure(TiStr, formats_minutes_seconds_and_hundredths) {
    assert_that(tistr(MINUTES(1) + 30*TI_HZ + TI_HZ/2), is_equal_to_string(" 1:30.50"));
}

Ensure(TiStr, pads_a_single_digit_minute_count) {
    assert_that(tistr(MINUTES(9)), is_equal_to_string(" 9:00.00"));
}

/* %2d is a minimum width, not a maximum, so a run of a hundred minutes or
   more needs three digits and the result no longer fits in eight. */
Ensure(TiStr, formats_three_digit_minutes) {
    assert_that(tistr(MINUTES(100)), is_equal_to_string("100:00.00"));
}

int main(int argc, char **argv) {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, TiStr, formats_minutes_seconds_and_hundredths);
    add_test_with_context(suite, TiStr, pads_a_single_digit_minute_count);
    add_test_with_context(suite, TiStr, formats_three_digit_minutes);
    return run_test_suite(suite, create_text_reporter());
}
