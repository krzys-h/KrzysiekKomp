#include "main.h"

u8int mouse_cycle=0;     //unsigned char
s8int mouse_byte[3];    //signed char
s8int mouse_x=0;         //signed char
s8int mouse_y=0;         //signed char

//Mouse functions
void mouse_handler()
{
  switch(mouse_cycle)
  {
    case 0:
      mouse_byte[0]=inportb(0x60);
      mouse_cycle++;
      break;
    case 1:
      mouse_byte[1]=inportb(0x60);
      mouse_cycle++;
      break;
    case 2:
      mouse_byte[2]=inportb(0x60);
      mouse_x=mouse_byte[1];
      mouse_y=mouse_byte[2];
	  vga_puts("MOUSE: x=");
	  pisz_s16int(mouse_x);
	  vga_puts(" y=");
	  pisz_s16int(mouse_y);
	  vga_putch('\n');
      mouse_cycle=0;
      break;
  }
  vga_puts("MOUSE: IRQ");
}

inline void mouse_wait(u8int a_type) //unsigned char
{
  u32int _time_out=100000; //unsigned int
  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inportb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inportb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(u8int a_write) //unsigned char
{
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  outportb(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  outportb(0x60, a_write);
}

u8int mouse_read()
{
  //Get's response from mouse
  mouse_wait(0); 
  return inportb(0x60);
}

void mouse_init()
{
  u8int _status;  //unsigned char

  //Enable the auxiliary mouse device
  mouse_wait(1);
  outportb(0x64, 0xA8);
  
  //Enable the interrupts
  mouse_wait(1);
  outportb(0x64, 0x20);
  mouse_wait(0);
  _status=(inportb(0x60) | 2);
  mouse_wait(1);
  outportb(0x64, 0x60);
  mouse_wait(1);
  outportb(0x60, _status);
  
  //Tell the mouse to use default settings
  mouse_write(0xF6);
  mouse_read();  //Acknowledge
  
  //Enable the mouse
  mouse_write(0xF4);
  mouse_read();  //Acknowledge

  //Setup the mouse handler
  idt_set_intr_gate(&idt[0x20+0x12], (u32int)&mouse_handler);
}