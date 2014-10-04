#include "services/keyboard.h"

#include "common/types.h"
#include "common/ports.h"
#include "screen/text_screen.h"
#include "arch/idt.h"

typedef struct
{
	unsigned char *data;
	/* size, beginning, end */
	unsigned size, in_ptr, out_ptr;
} queue_t;

int inq(queue_t *q, unsigned data)
{
	unsigned temp;
	temp = q->in_ptr + 1;
	if(temp >= q->size) temp = 0;
	if(temp == q->out_ptr) return -1; // if the queue is full, return -1
	q->data[q->in_ptr] = data;
	q->in_ptr = temp;
	return 0;
}

int deq(queue_t *q, unsigned char *data)
{
	if(q->out_ptr == q->in_ptr) return -1; // if the queue is empty, return -1
	*data = q->data[q->out_ptr++];
	if(q->out_ptr >= q->size) q->out_ptr = 0;
	return 0;
}

int empty(queue_t *q)
{
	return q->out_ptr == q->in_ptr;
}

#define KEYBOARD_QUEUE_SIZE 64
static unsigned char keyboard_queue_data[KEYBOARD_QUEUE_SIZE];

static queue_t keyboard_buf = {
      keyboard_queue_data,
      KEYBOARD_QUEUE_SIZE,
      0,
      0
};


int read_keyboard(void)
{
	unsigned long timeout;
	unsigned stat, data;
	for(timeout = 500000L; timeout != 0; timeout--) {
		stat = inportb(0x64);
		if(stat & 0x01) {
			data = inportb(0x60);
			if((stat & 0xC0) == 0) return data;
		}
	}
	return -1;
}

void write_keyboard(unsigned adr, unsigned data)
{
	unsigned long timeout;
	unsigned stat;
	for(timeout = 500000L; timeout != 0; timeout--) {
		stat = inportb(0x64);
		if((stat & 0x02) == 0) break;
	}
	
	/*if(timeout == 0) {
		screen_print("write_keyboard: timeout\n");
		return;
	}*/
	
	outportb(adr, data);
}

#define      RAW1_LEFT_CTRL            0x1D
#define      RAW1_LEFT_SHIFT            0x2A
#define      RAW1_CAPS_LOCK            0x3A
#define      RAW1_LEFT_ALT            0x38
#define      RAW1_RIGHT_ALT            0x38
#define      RAW1_RIGHT_CTRL            0x1D
#define      RAW1_RIGHT_SHIFT      0x36
#define      RAW1_SCROLL_LOCK      0x46
#define      RAW1_NUM_LOCK            0x45
#define      RAW1_DEL            0x53

int set1_scancode_to_ascii(unsigned code)
{
	static const unsigned char map[] =
	{
/* 00 */0,	0x1B,	'1',	'2',	'3',	'4',	'5',	'6',
/* 08 */'7',	'8',	'9',	'0',	'-',	'=',	'\b',	'\t',
/* 10 */'q',	'w',	'e',	'r',	't',	'y',	'u',	'i',
/* 1Dh to lewy Ctrl */
/* 18 */'o',	'p',	'[',	']',	'\n',	0,	'a',	's',
/* 20 */'d',	'f',	'g',	'h',	'j',	'k',	'l',	';',
/* 2Ah to lewy Shift */
/* 28 */'\'',	'`',	0,	'\\',	'z',	'x',	'c',	'v',
/* 36h to prawy Shift */
/* 30 */'b',	'n',	'm',	',',	'.',	'/',	0,	0,
/* 38h to lewy Alt, 3Ah to Caps Lock */
/* 38 */0,	' ',	0,	KEY_F1,	KEY_F2,	KEY_F3,	KEY_F4,	KEY_F5,
/* 45h to Num Lock, 46h to Scroll Lock */
/* 40 */KEY_F6,	KEY_F7,	KEY_F8,	KEY_F9,	KEY_F10,0,	0,	KEY_HOME,
/* 48 */KEY_UP,	KEY_PGUP,'-',	KEY_LFT,'5',	KEY_RT,	'+',	KEY_END,
/* 50 */KEY_DN,	KEY_PGDN,KEY_INS,KEY_DEL,0,	0,	0,	KEY_F11,
/* 58 */KEY_F12
	};
	static const unsigned char shift_map[] =
	{
/* 00 */0,	0x1B,	'!',	'@',	'#',	'$',	'%',	'^',
/* 08 */'&',	'*',	'(',	')',	'_',	'+',	'\b',	'\t',
/* 10 */'Q',	'W',	'E',	'R',	'T',	'Y',	'U',	'I',
/* 18 */'O',	'P',	'{',	'}',	'\n',	0,	'A',	'S',
/* 20 */'D',	'F',	'G',	'H',	'J',	'K',	'L',	':',
/* 28 */'"',	'~',	0,	'|',	'Z',	'X',	'C',	'V',
/* 30 */'B',	'N',	'M',	'<',	'>',	'?',	0,	0,
/* 38 */0,	' ',	0,	KEY_F1,	KEY_F2,	KEY_F3,	KEY_F4,	KEY_F5,
/* 40 */KEY_F6,	KEY_F7,	KEY_F8,	KEY_F9,	KEY_F10,0,	0,	KEY_HOME,
/* 48 */KEY_UP,	KEY_PGUP,'-',	KEY_LFT,'5',	KEY_RT,	'+',	KEY_END,
/* 50 */KEY_DN,	KEY_PGDN,KEY_INS,KEY_DEL,0,	0,	0,	KEY_F11,
/* 58 */KEY_F12
	};
	
	static unsigned saw_break_code, keyboard_status;
	unsigned temp;
	
	// Key released (break code)?
	if(code >= 0x80) {
		saw_break_code = 1;
		code &= 0x7F;
	}
	
	if(saw_break_code) {
		if(code == RAW1_LEFT_ALT || code == RAW1_RIGHT_ALT)
			keyboard_status &= ~KBD_META_ALT;
		else if(code == RAW1_LEFT_CTRL || code == RAW1_RIGHT_CTRL)
			keyboard_status &= ~KBD_META_CTRL;
		else if(code == RAW1_LEFT_SHIFT || code == RAW1_RIGHT_SHIFT)
			keyboard_status &= ~KBD_META_SHIFT;
		saw_break_code = 0;
		return -1;
	}
	
	// Key pressed (make code)?
	if(code == RAW1_LEFT_ALT || code == RAW1_RIGHT_ALT) {
		keyboard_status |= KBD_META_ALT;
		return -1;
	}
	if(code == RAW1_LEFT_CTRL || code == RAW1_RIGHT_CTRL) {
		keyboard_status |= KBD_META_CTRL;
		return -1;
	}
	if(code == RAW1_LEFT_SHIFT || code == RAW1_RIGHT_SHIFT) {
		keyboard_status |= KBD_META_SHIFT;
		return -1;
	}

	if(code == RAW1_SCROLL_LOCK) {
		keyboard_status ^= KBD_META_SCRL;
		goto LEDS;
	}
	if(code == RAW1_NUM_LOCK) {
		keyboard_status ^= KBD_META_NUM;
		goto LEDS;
	}
	if(code == RAW1_CAPS_LOCK) {
		keyboard_status ^= KBD_META_CAPS;
		LEDS:
		write_keyboard(0x60, 0xED); /* "set LEDs" command */
		temp = 0;
		if(keyboard_status & KBD_META_SCRL)
			temp |= 1;
		if(keyboard_status & KBD_META_NUM)
			temp |= 2;
		if(keyboard_status & KBD_META_CAPS)
			temp |= 4;
		write_keyboard(0x60, temp);
		return -1;
	}
	
	/* no converion if ALT is pressed */
	if(keyboard_status & KBD_META_ALT)
		return code;
	
	/* Convert A-Z[\]^_ to control codes */
	if(keyboard_status & KBD_META_CTRL) {
		if(code >= sizeof(map) / sizeof(map[0]))
			return -1;
		temp = map[code];
		if(temp >= 'a' && temp <= 'z')
			return temp - 'a';
		if(temp >= '[' && temp <= '_')
			return temp - '[' + 0x1B;
		return -1;
	}
	
	/* convert scancode to ASCII */
	if(keyboard_status & KBD_META_SHIFT) { // SHIFT?
		/* ignore bad codes */
		if(code >= sizeof(shift_map) / sizeof(shift_map[0]))
			return -1;
		temp = shift_map[code];
		if(temp == 0)
			return -1;
		
		/* Caps lock? */
		if(keyboard_status & KBD_META_CAPS) {
			if(temp >= 'A' && temp <= 'Z')
				temp = map[code];
		}
	} else {
		/* ignore bad codes */
		if(code >= sizeof(map) / sizeof(map[0]))
			return -1;
		temp = map[code];
		if(temp == 0)
			return -1;
			
		/* Caps lock? */
		if(keyboard_status & KBD_META_CAPS) {
			if(temp >= 'a' && temp <= 'z')
				temp = shift_map[code];
		}
	}
	return temp;
}

void do_irq1()
{
	int key = inportb(0x60);
	key = set1_scancode_to_ascii(key);
	if(key > 0 && key < 256)
	{
		inq(&keyboard_buf, key);
	}
}

void keyboard_init()
{
	idt_set_intr_gate(&idt[0x21], (u32int)&irq1);
	enable_irq(1);
}

char getchar()
{
	unsigned char p;
	if(deq(&keyboard_buf, &p) < 0) return 0;
	return p;
}

int getstring(char* buf)
{
	char i = 0;
	bool enter = false;
	while(!enter) {
		char c = getchar();
		if(!c) continue;
		switch(c) {
			case '\b':
				if(i>0) {
					i--;
					buf[i] = 0;
					screen_printchar('\b');
				}
				break;
			case '\n':
				buf[i] = 0;
				enter = true;
				screen_printchar('\n');
				break;
			default:
				screen_printchar(c);
				buf[i] = c;
				i++;
		}
	}
	return i;
}
