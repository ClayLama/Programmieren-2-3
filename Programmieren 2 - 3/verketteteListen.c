//PPR2 – Übung 3 – Prof. Dr. Ulrike Herster
//"verketteteListen.c", 13.12.2024, Autoren: Kendelbacher, Pham, Schreiner
#include "datentypenFunktionsprototypen.h"

int main() {
	sElement* liste = NULL;				//Pruefungsliste mit allen Studierenden
	sElement* neu = NULL;
	sElement* cursor = NULL;		
	int schleife = 1;					//Schleife läuft, bis Schleife = 0
	int auswahl = 0;					//Ausgewählte Funkrtion des Benutzers
	int indexEinfuegen = 0;				//Index, bei dem Student eingefügt werden soll
	int matrikelnummerEingabe = 0;		//Eingegebene Matrikelnummer zum löschen


	//Schleife läuft bis Benutzer sie durch Auswahl beeendet
	while (schleife == 1) {
		printf("******************************************************\n");
		printf("*                                                    *\n");
		printf("*                   Pruefungsliste                   *\n");
		printf("*                                                    *\n");
		printf("******************************************************\n");
		printf("1. Einfuegen eines neuen Studierenden\n");
		printf("2. Ausgabe der Pruefungsliste\n");
		printf("3. Gesamte Pruefungsliste Loeschen\n");
		printf("4. Loeschen eines Studierenden\n");
		printf("5. Programm beenden\n");
		printf("Waehlen Sie eine Option: ");

		if (!leseZahl(1, 5, &auswahl)) {
			printf("Ungueltige Eingabe. Bitte geben Sie eine Zahl ein.\n\n");
			continue;
		}
		printf("\n");
		switch (auswahl) {
		case 1:
			printf("Bitte geben Sie im folgenden die Daten des Studierenden ein:\n\n");
			neu = neuerStudentEingabe();
			indexEinfuegen = findePosition(liste, neu);
			if (indexEinfuegen != -1) {
				liste = einfuegenStudent(liste, neu, indexEinfuegen);
				printf("\nDer Student wurde gespeichert.");
			}
			else
				printf("\nEin Student mit der Matrikelnummer %d existiert bereits!", neu->student->matrikelnummer);
			break;
		case 2:
			printf("Folgendes ist die Pruefungsliste:\n\n");
			ausgabeListe(liste);
			break;
		case 3:
			printf("Moechten Sie wirklich die gesamte Pruefungsliste loeschen?\n");
			printf("Geben Sie \"1\" ein, um die gesamte Liste zu loeschen: ");
			if (leseZahl(1, 1, &auswahl)) {
				liste = loescheListe(liste);
				printf("\nDie Pruefungsliste wurde geloescht.\n");
			}
			else
				printf("\nDie Liste wurde nicht geloescht.");
			break;
		case 4:
			printf("Welcher Student soll geloescht werden?\n");
			printf("Bitte geben Sie die Matrikelnummer ein: ");
			while (!leseZahl(0, INT_MAX, &matrikelnummerEingabe)) {
				printf("Die Matrikelnummer darf nich groesser als %d sein.\nBitte geben Sie die Matrikelnummer ein: ", INT_MAX);
			}
			cursor = findeMatrikelnummer(liste, matrikelnummerEingabe);
			if (cursor != NULL) {
				liste = loescheStudi(cursor);
				printf("\nDer Student mit der Matrikelnummer \"%d\" wurde geloescht!", matrikelnummerEingabe);
			}
			else
				printf("\nIn der Liste befindet sich kein Student mit der eingegebenen Matrikelnummer.");
			break;
		case 5:
			liste = loescheListe(liste);
			printf("\nProgramm beendet.\n");
			schleife = 0;
			break;

		default:
			printf("Unmoegliche Auswahl.\n");
		}
		printf("\n\n");
	}

	return 0;
}