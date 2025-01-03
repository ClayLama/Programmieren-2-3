#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VORNAME 30
#define MAX_NACHNAME 30
#define MAX_MAIL 320
#define MAX_NOTE 15
#define MAX_STRING 320


typedef struct {
	char vorname[MAX_VORNAME+2];
	char nachname[MAX_NACHNAME+2];
}sGanzname;

typedef struct {
	sGanzname name;
	char email[MAX_MAIL+2];
	int matrikelnummer;
	int note;
}sStudent;

/*
	Entscheidung: M�glichkeit 4: Doppelt verkettete Liste mit Zeiger auf Studierendendaten

	Gr�nde:
	- Vor- und R�ckw�rtsnavigation erleichtert Einf�gen und L�schen.
	- Daten k�nnen unabh�ngig von der Liste verwaltet und theoretisch mehrfach genutzt werden.
	- Geringerer Speicherverbrauch pro Listenelement.

	Nachteile:
	- Verwaltung ist komplexer
*/

//Listenelement
typedef struct sElement {
	sStudent* student;
	struct sElement* prev;
	struct sElement* next;
} sElement;

sElement* einfuegenStudent(sElement* liste, sElement* neu, int index);
sElement* findeListenAnfang(sElement* liste);
sElement* findeListenEnde(sElement* liste);
int zaehleStudierende(sElement* liste);
int findePosition(sElement* liste, sElement* neu);
sElement* neuerStudentEingabe();
void ausgabeListe(sElement* liste);
sElement* loescheListe(sElement* liste);
sElement* findeMatrikelnummer(sElement* liste, int matrikelnummer);
sElement* loescheStudi(sElement* student);
int leseString(char string[], int anzahlZeichen);
int leseZahl(int minimalZahl, int maximalZahl, int* zahl);