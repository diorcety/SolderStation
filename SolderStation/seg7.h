#ifndef _SEG7_H
#define _SEG7_H

#ifdef SEG7_MODULE

/*
 * Init SEG7 stuff
 */
void seg7_init();

/*
 * Print temperature on 7-seg
 */
void seg7_print(int temp);

#endif //SEG7_MODULE

#endif //_SEG7_H
