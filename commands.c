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
	u8int buffer[512];
	disc_read(0, 0, 0, 1, 1, (u16int*)&buffer[0]);
	pisz_u16int((u16int)buffer[510]);
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