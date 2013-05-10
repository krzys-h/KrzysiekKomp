#include "main.h"
void cmd_echo(char *param[])
{
	vga_puts((char*)param);
}


void cmd_time()
{
	time_t czas = gettime();
	
	pisz_time(czas.hour*60*60+czas.minute*60+czas.second);
}

void cmd_clrscr()
{
	vga_cls();
}

void cmd_runtime()
{
	pisz_time_ms(runtime);
}

void cmd_beep()
{
	beep();
}

void cmd_testboot()
{
	// Should print "85/170" (55/AA in decimal)
	u8int buffer[512];
	disc_read(0, 0, 0, 1, 1, &buffer[0]);
	pisz_u8int(buffer[510]);
	vga_putch('/');
	pisz_u8int(buffer[511]);
}


void p(partition_t part)
{
	vga_puts("bootable="); pisz_u8int(part.bootable); vga_putch('\n');
	vga_puts("start_H="); pisz_u8int(part.start_H); vga_putch('\n');
	vga_puts("start_C="); pisz_u16int(part.start_C); vga_putch('\n');
	vga_puts("start_S="); pisz_u8int(part.start_S); vga_putch('\n');
	vga_puts("filesystem="); pisz_u8int(part.filesystem); vga_putch('\n');
	vga_puts("used="); pisz_u8int(part.used); vga_putch('\n');
	vga_puts("end_H="); pisz_u8int(part.end_H); vga_putch('\n');
	vga_puts("end_C="); pisz_u16int(part.end_C); vga_putch('\n');
	vga_puts("end_S="); pisz_u8int(part.end_S); vga_putch('\n');
	vga_puts("relative_start="); pisz_u16int(part.relative_start); vga_putch('\n');
	vga_puts("total_sectors="); pisz_u16int(part.total_sectors); vga_putch('\n'); vga_putch('\n');
}

void cmd_testpart()
{
	/*partition_t part = parttable_getbootable();
	
	vga_puts("Aktywna partycja (");
	pisz_u8int(partition_bootable+1);
	vga_puts(") zaczyna sie w H:");
	pisz_u8int(part.start_H);
	vga_puts(" C:");
	pisz_u16int(part.start_C);
	vga_puts(" S:");
	pisz_u8int(part.start_S);
	vga_puts(", konczy w H:");
	pisz_u8int(part.end_H);
	vga_puts(" C:");
	pisz_u16int(part.end_C);
	vga_puts(" S:");
	pisz_u8int(part.end_S);
	vga_puts(" i ma ");
	pisz_u16int(part.total_sectors);
	vga_puts(" sektorow.");*/
	p(partition[0]); delay(500);
	p(partition[1]); delay(500);
	p(partition[2]); delay(500);
	p(partition[3]); delay(500);
}

void cmd_memory()
{
	vga_puts("W komputerze jest ");
	pisz_u16int(total_memory_size / 1024);
	vga_puts(" MB = ");
	pisz_u16int(total_memory_size);
	vga_puts(" KB pamieci RAM.");
}

void cmd_help()
{
	vga_puts("KrzysiekKomp 1.0\n");
	vga_puts("Kompilacja: "__DATE__" "__TIME__"\n");
	vga_puts("--------------------------------------------------\n");
	vga_puts("Oto lista dostepnych polecen:\n");
	vga_puts("echo param ===> Wyswietla parametr (param).\n");
	vga_puts("time =========> Wyswietla aktualny czas.\n");
	vga_puts("clrscr =======> Czysci ekran.\n");
	vga_puts("memory =======> Pokazuje ilosc pamieci RAM.\n");
	vga_puts("beep =========> Wydaje odglos z PC Speakera :)\n");
	vga_puts("runtime ======> Pokazuje czas od uruchomienia systemu.\n");
	vga_puts("help =========> Wyswietla ten ekran.\n");
	vga_puts("reboot =======> Restartuje komputer.\n");
	vga_puts("shutdown =====> Wylacza komputer.");
}

void cmd_reboot()
{
	reboot();
}

void cmd_shutdown()
{
	vga_puts("W BUDOWIE");
	//shutdown();
}

void cmd_nieznana(char *komenda[])
{
	vga_puts("Komenda ");
	vga_puts((char*)komenda);
	vga_puts(" nie istnieje!\n");
	vga_puts("Wpisz \"help\" aby uzyskac pomoc.");
}