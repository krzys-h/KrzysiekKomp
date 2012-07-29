#include "main.h"
void cmd_echo(char *param[])
{
	vga_puts((char*)param);
}


void cmd_time()
{
	char h,m,s;
	
	h=getcmos(0x04);
	m=getcmos(0x02);
	s=getcmos(0x00);
	
	pisz_time(h*60*60+m*60+s);
}

void cmd_clrscr()
{
	vga_cls();
}

void cmd_runtime()
{
	pisz_time_ms(runtime);
}

void cmd_settime()
{
	time_t czas;
	vga_puts("Godzina: ");
	czas.h = getnum();
	vga_puts("Minuta: ");
	czas.m = getnum();
	vga_puts("Sekunda: ");
	czas.s = getnum();
	settime(czas);
	vga_puts("Ustawienia zapisane!\n");
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