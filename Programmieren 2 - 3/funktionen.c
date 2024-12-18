#include "datentypenFunktionsprototypen.h"

/// Ziel: Element mit Student wird in Liste eingefügt
/// Parameter: Prüfungsliste, neues Element, index an dem eingefügt wird
/// Return:	eingefügtes Element in Liste
sElement* einfuegenStudent(sElement* liste, sElement* neu, int index) {

	//Falls Liste leer
	if (liste == NULL) {
		neu->prev = NULL;
		neu->next = NULL;
		return neu;
	}

	sElement* cursor = findeListenAnfang(liste);

	//Cursor auf Index setzen
	int posCursor = 0;
	while (posCursor < index && cursor->next != NULL) {
		cursor = cursor->next;
		posCursor++;
	}

	//Falls Listenende erreicht
	if (cursor->next == NULL && posCursor != index) {
		neu->next = NULL;
		neu->prev = cursor;
		cursor->next = neu;
		return neu;
	}

	//Falls Anfang
	if (cursor->prev == NULL) {
		neu->prev = NULL;
		neu->next = cursor;
		cursor->prev = neu;
		return neu;
	}

	//Zwischendrin
	neu->prev = cursor->prev;
	neu->next = cursor;
	cursor->prev->next = neu;
	cursor->prev = neu;

	return neu;
}

/// Ziel: Findet den Anfang einer gegebenen Liste und gibt ihn zurück
sElement* findeListenAnfang(sElement* liste) {
	sElement* cursor = liste;

	//Falls Liste leer return NULL ptr
	if (liste == NULL) {
		return NULL;
	}

	while (cursor->prev != NULL) {
		cursor = cursor->prev;
	}

	return cursor;
}

/// Ziel: Findet das Ende einer gegebenen Liste und gibt ihn zurück
sElement* findeListenEnde(sElement* liste) {
	sElement* cursor = liste;

	//Falls Liste leer return NULL ptr
	if (cursor == NULL) {
		return NULL;
	}

	while (cursor->next != NULL) {
		cursor = cursor->next;
	}

	return cursor;
}

/// Ziel: Zählt die Elemente/Studenten in der Liste und gibt diese zurück
int zaehleStudierende(sElement* liste) {
	sElement* cursor = findeListenAnfang(liste);
	int zaehler = 0;	//Zählt Listenelemente

	//Liste Leer
	if (cursor == NULL)
		return zaehler;

	//Erstes Element vorhanden
	zaehler++;

	//Weitere Elemente Zählen
	while (cursor->next != NULL) {
		cursor = cursor->next;
		zaehler++;
	}
	return zaehler;
}

/// Ziel:	Findet passende Position eines Elements (Sorrtiert nach Matrikelnummer)
///			in der gegebenen Liste und gibt die Position als int zurück
/// Parameter: Prüfungsliste, Element für das Position gefunden wird
/// Return:	Index an den das Element gehört / -1 falls Matrikelnummer bereits in Liste vorhanden 
int findePosition(sElement* liste, sElement* neu) {
	int index = 0;									//Position an der neuer Student gespeichert werden soll

	sElement* cursor = findeListenAnfang(liste);

	//Falls Liste leer
	if (liste == NULL)
		return index;

	//Index wird solange erhöht, bis Matrikelnummer vom neuen Studeneten größer-gleich aktueller Cursor
	while (cursor->student->matrikelnummer <= neu->student->matrikelnummer) {

		index++;
		if (cursor->next != NULL)
			cursor = cursor->next;
		else
			break;
	}
	//Falls Matrikelnummer bereits vorhanden
	if (cursor->student->matrikelnummer == neu->student->matrikelnummer)
		return -1;

	return index;
}

/// Ziel:	Daten eines Studenten werden von der Konsole eingelesen und als Element returned
sElement* neuerStudentEingabe() {
	//Speicher reservieren
	sElement* neuerStudent = (sElement*)malloc(sizeof(sElement));
	if (neuerStudent == NULL) {
		printf("Kein Speicher vorhanden!\n");
		exit(1);
	}
	neuerStudent->student = (sStudent*)malloc(sizeof(sStudent));
	if (neuerStudent->student == NULL) {
		printf("Kein Speicher vorhanden!\n");
		free(neuerStudent);
		exit(1);
	}

	//Eingabe Vorname
	printf("Geben Sie den Vornamen von dem Studenten ein: ");
	while (!leseString(neuerStudent->student->name.vorname, MAX_VORNAME)) {
		printf("Bitte geben Sie maximal %d Zeichen ein.\nGeben Sie den Vornamen von dem Studenten ein: ", MAX_VORNAME);
	}
	//Eingabe Nachname
	printf("Geben Sie den Nachnamen von dem Studenten ein: ");
	while (!leseString(neuerStudent->student->name.nachname, MAX_NACHNAME)) {
		printf("Bitte geben Sie maximal %d Zeichen ein.\nGeben Sie den Nachnamen von dem Studenten ein: ", MAX_NACHNAME);
	}
	//Eingabe Email
	printf("Bitte geben Sie die E-Mail-Adresse ein: ");
	while (!leseString(neuerStudent->student->email, MAX_MAIL)) {
		printf("Bitte geben Sie maximal %d Zeichen ein.\nBitte geben Sie die E-Mail-Adresse ein:  ", MAX_MAIL);
	}
	//Eingabe der Matrikelnummer
	printf("Bitte geben Sie die Matrikelnummer ein: ");
	while (!leseZahl(0, INT_MAX, &(neuerStudent->student->matrikelnummer))) {
		printf("Die Matrikelnummer darf nich groesser als %d sein.\nBitte geben Sie die Matrikelnummer ein: ", INT_MAX);
	}
	//Eingabe der Note
	printf("Bitte geben Sie die Note ein: ");
	while (!leseZahl(0, MAX_NOTE, &(neuerStudent->student->note))) {
		printf("Die Note muss zwischen 0 und %d Punkten sein.\nBitte geben Sie die Note ein: ", MAX_NOTE);
	}

	return neuerStudent;
}

/// Ziel:	Gesamte Liste wird auf der Konsole ausgegeben
void ausgabeListe(sElement* liste) {
	sElement* cursor = findeListenEnde(liste);
	int aktuellerStudent = zaehleStudierende(liste);

	//Liste Leer
	if (aktuellerStudent == 0) {
		printf("In der Pruefungsliste befinden sich keine Studenten.\n");
		return;
	}
	//Ausgabe der Daten
	while (cursor != NULL) {
		printf("Student %d:\n", aktuellerStudent);
		printf("Name: %s %s\n", cursor->student->name.vorname, cursor->student->name.nachname);
		printf("E-Mail: %s\n", cursor->student->email);
		printf("Matrikelnummer: %d\n\n", cursor->student->matrikelnummer);
		aktuellerStudent--;
		cursor = cursor->prev;
	}
	return;
}

/// Ziel:	Gesamte Liste wird gelöscht
sElement* loescheListe(sElement* liste) {
	//Jedes einzelnde Element wird gelöscht
	if (liste != NULL) {
		sElement* cursor = findeListenEnde(liste);
		sElement* prevCursor = cursor->prev;

		while (cursor != NULL) {
			free(cursor->student);
			free(cursor);
			cursor = prevCursor;
			if (cursor != NULL)
				prevCursor = cursor->prev;
		}
	}
	return NULL;
}

/// Ziel:	Findet Element mit gegebener Matrikelnummer und gibt dieses zurück
///			Falls Matrikelnummer nicht vorhanden wird der Cursor = NULL
sElement* findeMatrikelnummer(sElement* liste, int matrikelnummer) {
	sElement* cursor = findeListenAnfang(liste);

	while (cursor != NULL && cursor->student->matrikelnummer != matrikelnummer) {
		cursor = cursor->next;
	}

	return cursor;
}

/// Ziel:	Gegebener Student wird gelöscht und anderes Element wird zurückgegeben
sElement* loescheStudi(sElement* student) {
	sElement* cursor = student;

	//Einziges Element
	if (student->prev == NULL && student->next == NULL)
		cursor = NULL;

	//Erstes Element 
	else if (student->prev == NULL) {
		cursor = student->next;
		student->next->prev = NULL;
	}

	//Letztes Element 
	else if (student->next == NULL) {
		cursor = student->prev;
		student->prev->next = NULL;

	}

	//Zwischendrin
	else {
		cursor = student->prev;
		student->prev->next = student->next;
		student->next->prev = student->prev;
	}

	free(student->student);
	free(student);
	student = NULL;
	return cursor;
}

/// Ziel: String wird aus Konsole eingelesen
/// Parameter: string, in dem gespeichert werden soll, maximale Anzahl an Zeichen
/// Return:	Einlesen erfolgreich = 1, gescheitert = 0
int leseString(char string[], int anzahlZeichen) {
	if (fgets(string, anzahlZeichen + 2, stdin) != NULL) {

		// Entferne das Newline-Zeichen, falls vorhanden
		int len = (int)strlen(string);
		if (len > 0 && string[len - 1] == '\n') {
			string[len - 1] = '\0';
			return 1;
		}
		else {
			while (getchar() != '\n');
			return 0;
		}
	}
	return 0;
}

/// Ziel: Eingabe und Validierung einer Zahl
/// Parameter: Minimal mögliche Eingabe, Maximal mögliche Eingabe
/// Return: Einlesen erfolgreich = 1, gescheitert = 0
int leseZahl(int minimalZahl, int maximalZahl, int* zahl) {
	int korrekteEingabe = scanf_s("%9d", zahl);

	if (*zahl > maximalZahl || *zahl < minimalZahl)
		korrekteEingabe = 0;
	while (getchar() != '\n')
		korrekteEingabe = 0;

	return korrekteEingabe;
}