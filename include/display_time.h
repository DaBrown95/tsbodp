#ifndef DISPLAY_TIME_H
#define DISPLAY_TIME_H

/* Eight-byte serialized clock view. The final halfword is copied but its role
 * is unknown; arithmetic/comparison names come from observed field radices. */
struct DisplayTimeRecord {
    short day;
    signed char hour, minute, second, tick;
    unsigned short reserved;
};
enum DisplayTimeFieldMask {
    DISPLAY_TIME_SECOND = 1,
    DISPLAY_TIME_MINUTE = 2,
    DISPLAY_TIME_HOUR = 4,
    DISPLAY_TIME_DAY = 8,
    DISPLAY_TIME_TICK = 16
};
unsigned int display_time_add(struct DisplayTimeRecord *,
                              const struct DisplayTimeRecord *);
unsigned int display_time_compare(const struct DisplayTimeRecord *,
                                  const struct DisplayTimeRecord *, unsigned int);
void display_time_clear(struct DisplayTimeRecord *);
void display_time_copy(struct DisplayTimeRecord *, const struct DisplayTimeRecord *);
void display_time_copy_add(const struct DisplayTimeRecord *,
                          const struct DisplayTimeRecord *, struct DisplayTimeRecord *);
unsigned int display_time_equal(const struct DisplayTimeRecord *,
                                const struct DisplayTimeRecord *, unsigned int);
unsigned int display_time_period(const struct DisplayTimeRecord *);
short display_time_weekday(const struct DisplayTimeRecord *);
unsigned int display_time_in_range(const struct DisplayTimeRecord *,
                                   const struct DisplayTimeRecord *,
                                   const struct DisplayTimeRecord *, unsigned int);
#endif
