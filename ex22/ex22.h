#ifndef _ex22_h
#define _ex22_h
/*
struct State {
        int the_size;
            int the_age;
};
*/

extern int THE_SIZE;

// gets and sets an internal static variable in ex22.c
// int get_age(struct State *state);
// void set_age(struct State *state, int age);
int get_age();
void set_age(int age);

// updates a static variable that's inside update_ratio
double update_ratio(double ratio);

void print_size();

#endif
