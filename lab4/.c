#include <windows.h>
#include <stdio.h>
#define THREAD_COUNT 5

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#pragma argsused


struct dane_dla_watku // tablica zawiera dane , ktore otrzymaja watki
{
	char nazwa[50];
	int parametr;
} dane[THREAD_COUNT] = { { "[1]" , 5 } , { "[2]" , 8 } , { "[3]" , 12 }, { "[4]" , 16 }, { "[5]" , 20 } };
// priorytety watkow
int priorytety[THREAD_COUNT] = { THREAD_PRIORITY_BELOW_NORMAL ,
THREAD_PRIORITY_NORMAL , THREAD_PRIORITY_ABOVE_NORMAL, THREAD_PRIORITY_HIGHEST,THREAD_PRIORITY_LOWEST
};

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

HANDLE watki[THREAD_COUNT]; // dojscia ( uchwyty ) watkow
// deklaracja funkcji watku
DWORD WINAPI funkcja_watku(void* argumenty);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main(int argc, char** argv)
{
	int i;
	DWORD id; // identyfikator watku
	system("cls");
	printf("Uruchomienie programu\n");
	// tworzenie watkow
	for (i = 0; i < THREAD_COUNT; i++)
	{
		watki[i] = CreateThread(
			NULL, // atrybuty bezpieczenstwa
			0, // inicjalna wielkosc stosu
			funkcja_watku, // funkcja watku
			(void*)&dane[i],// dane dla funkcji watku
			0, // flagi utworzenia
			&id);
		Sleep(1);
		if (watki[i] != INVALID_HANDLE_VALUE)
		{
			printf(" Utworzylem watek %s o id %x\n", dane[i].nazwa, id);
			// ustawienie priorytetu
			SetThreadPriority(watki[i], priorytety[i]);
		}
	}
	Sleep(2000);
	TerminateThread(watki[2], 0);

	Sleep(20000); // uspienie watku glownego na 20 s
	return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// trzy takie funkcje pracuja wspolbieznie w programie
DWORD WINAPI funkcja_watku(void* argumenty)
{
	unsigned int licznik = 0;
	// rzutowanie struktury na wlasny wskaznik
	struct dane_dla_watku* moje_dane = (struct dane_dla_watku*)argumenty;
	// wyswietlenie informacji o uruchomieniu
	gotoxy(1, moje_dane->parametr);
	printf("%s", moje_dane-> nazwa);
	// praca , watki sa terminowane przez zakonczenie programu
	// - funkcji main
	Sleep(500);	gotoxy(1, 500 + moje_dane->parametr);	int h = GetCurrentThreadId();
	printf("Thread ID: %x\n", h);
	Sleep(500);
	while (1)
	{
		gotoxy(licznik++ / 5000 + 5, moje_dane->parametr);
		printf(".");
	}
	return 0;
}//5 watkow// w jednym zmienic priorytet// pobrac aktualny watek dzialajacy i go zakonczyc