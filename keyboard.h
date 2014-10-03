#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

extern void irq1(void); 

void kbd_init(void);

int getch(void);

int getstr(char* buffer);

#endif