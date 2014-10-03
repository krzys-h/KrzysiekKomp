#include "main.h"

typedef struct 
{ 
	/* dane w buforze */ 
	unsigned char *data; 
	/* rozmiar, poczatek bufora, koniec bufora */ 
	unsigned size, in_ptr, out_ptr; 
} queue_t; 

static int inq(queue_t *q, unsigned data) 
{ 
	unsigned temp; 
	temp = q->in_ptr + 1; 
	if(temp >= q->size) temp = 0; 
	/* jesli in_ptr+1==out_ptr to znaczy, ¿e kolejka jest pe³na */ 
	if(temp == q->out_ptr) return -1; 
	q->data[q->in_ptr] = data; 
	q->in_ptr = temp; 
	return 0; 
} 

static int deq(queue_t *q, unsigned char *data) 
{ 
	/* gdy out_ptr==in_ptr, znaczy ¿e kolejka jest pusta */ 
	if(q->out_ptr == q->in_ptr) return -1; 
	*data = q->data[q->out_ptr++]; 
	if(q->out_ptr >= q->size) q->out_ptr = 0; 
	return 0; 
} 

static int empty(queue_t *q) 
{ 
	return q->out_ptr == q->in_ptr; 
}

#define KBD_QUEUE_SIZE            64 
static unsigned char kbd_queue_data[KBD_QUEUE_SIZE]; 

static queue_t kbd_buf={ 
      kbd_queue_data, 
      KBD_QUEUE_SIZE, 
      0, 
      0 
}; 


static int read_kbd(void) 
{ 
unsigned long timeout; 
unsigned stat, data; 
 for(timeout = 500000L; timeout != 0; timeout--) 
 { 
  stat = inportb(0x64); 
/* czekaj gdy bufor klawiatury jest pe³ny */ 
  if(stat & 0x01) 
  { 
   data = inportb(0x60); 
/* pêtla, gdy b³ad parzystosci, lub koniec czasu oczekiwania */ 
   if((stat & 0xC0) == 0) return data; 
  } 
 } 
 return -1; 
} 

static void write_kbd(unsigned adr, unsigned data) 
{ 
unsigned long timeout; 
unsigned stat; 
 for(timeout = 500000L; timeout != 0; timeout--) 
 { 
  stat = inportb(0x64); 
/* czekaj gdy bufor klawiatury nie zrobi siê pusty */ 
  if((stat & 0x02) == 0) break; 
 } 
 if(timeout == 0) 
 { 
  vga_puts("write_kbd: timeout\n"); 
  return; 
 } 
outportb(adr, data); 
} 

#define      KEY_F1            0x80 
#define      KEY_F2            (KEY_F1 + 1) 
#define      KEY_F3            (KEY_F2 + 1) 
#define      KEY_F4            (KEY_F3 + 1) 
#define      KEY_F5            (KEY_F4 + 1) 
#define      KEY_F6            (KEY_F5 + 1) 
#define      KEY_F7            (KEY_F6 + 1) 
#define      KEY_F8            (KEY_F7 + 1) 
#define      KEY_F9            (KEY_F8 + 1) 
#define      KEY_F10            (KEY_F9 + 1) 
#define      KEY_F11            (KEY_F10 + 1) 
#define      KEY_F12            (KEY_F11 + 1) 
#define      KEY_INS            0x90 
#define      KEY_DEL            (KEY_INS + 1) 
#define      KEY_HOME      (KEY_DEL + 1) 
#define      KEY_END            (KEY_HOME + 1) 
#define      KEY_PGUP      (KEY_END + 1) 
#define      KEY_PGDN      (KEY_PGUP + 1) 
#define      KEY_LFT            (KEY_PGDN + 1) 
#define      KEY_UP            (KEY_LFT + 1) 
#define      KEY_DN            (KEY_UP + 1) 
#define      KEY_RT            (KEY_DN + 1) 
#define      KEY_PRNT      (KEY_RT + 1) 
#define      KEY_PAUSE      (KEY_PRNT + 1) 
#define      KEY_LWIN      (KEY_PAUSE + 1) 
#define      KEY_RWIN      (KEY_LWIN + 1) 
#define      KEY_MENU      (KEY_RWIN + 1) 

#define      KBD_META_ALT      0x0200 
#define      KBD_META_CTRL      0x0400 
#define      KBD_META_SHIFT      0x0800 
#define      KBD_META_ANY      (KBD_META_ALT | KBD_META_CTRL | KBD_META_SHIFT) 
#define      KBD_META_CAPS      0x1000 
#define      KBD_META_NUM      0x2000 
#define      KBD_META_SCRL      0x4000 

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

static int set1_scancode_to_ascii(unsigned code) 
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
 static unsigned saw_break_code, kbd_status; 
unsigned temp; 
/* sprawdz czy kod break (np. gdy klawisz zosta³ zwolniony) */ 
if(code >= 0x80) 
 { 
  saw_break_code = 1; 
  code &= 0x7F; 
 } 
/* kod break, które nas na razie interesuj¹ 
   to Ctrl, Shift, Alt */ 
if(saw_break_code) 
 { 
  if(code == RAW1_LEFT_ALT || code == RAW1_RIGHT_ALT) 
   kbd_status &= ~KBD_META_ALT; 
  else if(code == RAW1_LEFT_CTRL || code == RAW1_RIGHT_CTRL) 
   kbd_status &= ~KBD_META_CTRL; 
  else if(code == RAW1_LEFT_SHIFT || code == RAW1_RIGHT_SHIFT) 
   kbd_status &= ~KBD_META_SHIFT; 
  saw_break_code = 0; 
  return -1; 
 } 
/* jesli to kod make: sprawdzklawisze "meta" 
   podobnie jak powy¿ej */ 
if(code == RAW1_LEFT_ALT || code == RAW1_RIGHT_ALT) 
 { 
  kbd_status |= KBD_META_ALT; 
  return -1; 
 } 
 if(code == RAW1_LEFT_CTRL || code == RAW1_RIGHT_CTRL) 
 { 
  kbd_status |= KBD_META_CTRL; 
  return -1; 
 } 
 if(code == RAW1_LEFT_SHIFT || code == RAW1_RIGHT_SHIFT) 
 { 
  kbd_status |= KBD_META_SHIFT; 
  return -1; 
 } 
/* Scroll Lock, Num Lock, i Caps Lock ustawiaj¹ diody LED. */ 
if(code == RAW1_SCROLL_LOCK) 
 { 
  kbd_status ^= KBD_META_SCRL; 
  goto LEDS; 
 } 
 if(code == RAW1_NUM_LOCK) 
 { 
  kbd_status ^= KBD_META_NUM; 
  goto LEDS; 
 } 
 if(code == RAW1_CAPS_LOCK) 
 { 
  kbd_status ^= KBD_META_CAPS; 
LEDS:             
  write_kbd(0x60, 0xED);      /* komenda "set LEDS" */ 
  temp = 0; 
  if(kbd_status & KBD_META_SCRL) 
   temp |= 1; 
  if(kbd_status & KBD_META_NUM) 
   temp |= 2; 
  if(kbd_status & KBD_META_CAPS) 
   temp |= 4; 
  write_kbd(0x60, temp); 
  return -1; 
 } 
/* brak konwersji, gdy Alt jest nacianiêty */ 
if(kbd_status & KBD_META_ALT) 
  return code; 
/* konwertuj A-Z[\]^_ na kody sterowania */ 
if(kbd_status & KBD_META_CTRL) 
 { 
  if(code >= sizeof(map) / sizeof(map[0])) 
   return -1; 
  temp = map[code]; 
  if(temp >= 'a' && temp <= 'z') 
   return temp - 'a'; 
  if(temp >= '[' && temp <= '_') 
   return temp - '[' + 0x1B; 
  return -1; 
 } 
/* konwertuj kod skanowania na kod ASCII */ 
if(kbd_status & KBD_META_SHIFT) 
 { 
/* ignoruj niepoprawne kody */ 
  if(code >= sizeof(shift_map) / sizeof(shift_map[0])) return -1; 
  temp = shift_map[code]; 
  if(temp == 0) return -1; 
/* caps lock? */ 
  if(kbd_status & KBD_META_CAPS) 
  { 
   if(temp >= 'A' && temp <= 'Z') 
    temp = map[code]; 
  } 
 } else { 
  if(code >= sizeof(map) / sizeof(map[0])) 
   return -1; 
  temp = map[code]; 
  if(temp == 0) 
   return -1; 
  if(kbd_status & KBD_META_CAPS) 
  { 
   if(temp >= 'a' && temp <= 'z') 
    temp = shift_map[code]; 
  } 
 } 
 return temp; 
} 

void do_irq1(void) 
{
int klawisz=inportb(0x60); 
klawisz=set1_scancode_to_ascii(klawisz); 
 if(klawisz>0 && klawisz<256) 
 { 
  inq(&kbd_buf,klawisz); 
 } 
}

extern void irq1(void); 

void kbd_init(void) 
{ 
idt_set_intr_gate(&idt[0x21], (u32int)&irq1); 
enable_irq(1); 
}

int getch(void)
{
 unsigned char p;
 if(deq(&kbd_buf,&p)<0) return 0;
 return p;
}

int getstr(char* buffer)
{
	char i = 0;
	char enter = 0;
	while(!enter) {
		char c = getch();
		if(!c) continue;
		switch(c) {
			case '\b':
				if(i>0) {
					i--;
					buffer[i] = '\0';
					vga_putch('\b');
				}
				break;
			case '\n':
				buffer[i] = '\0';
				enter = 1;
				vga_putch('\n');
				break;
			default:
				vga_putch(c);
				buffer[i] = c;
				i++;
		}
	}
	return i;
}
