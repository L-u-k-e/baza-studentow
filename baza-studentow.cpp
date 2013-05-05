#include <iostream>
#include <string>

using namespace std;

struct przedmiot {
	string nazwa;
	przedmiot* nast;
};

struct ocena {
	string wartosc;
	przedmiot* przedmiot;
	ocena* nast;
};

struct student {
	string imie;
	string nazwisko;
	string album;
	ocena* p_ocena;
	ocena* poprz_ocena;
	student* nast;
};

student* st_poczatek;
student* st_poprz;
przedmiot* prz_poczatek;
przedmiot* prz_poprz;

void st_wyswietl(student* s = st_poczatek) {
	system("cls");
	cout << "--- LISTA STUDENTOW ---\n";
	if(s == NULL) {
		cout << "Brak studentow.\n\n";
		return;
	}
	int i = 1;
	do {
		cout << i++ << ". " << s->imie << " " << s->nazwisko << ", " << s->album << "\n";
		s = s->nast;
	} while(s);
	cout << "\n";
}

student* st_pobierz(int nr) {
	if(nr < 1) return NULL;
	student* s = st_poczatek;
	int i = 1;
	do {
		if(i++ == nr) return s;
		s = s->nast;
	} while(s);
	return NULL;
}
student* nowy_student(string imie, string nazwisko, string album) {
	student* s = new student;
	s->imie = imie;
	s->nazwisko = nazwisko;
	s->album = album;
	s->p_ocena = NULL;
	s->poprz_ocena = NULL;
	s->nast = NULL;
	return s; // zwracamy adres do nowo utworzonego studenta
}

void dodaj_studenta(string imie, string nazwisko, string album) {
	if(st_poczatek == NULL) {
		st_poprz = st_poczatek = nowy_student(imie, nazwisko, album);
	} else {
		st_poprz = st_poprz->nast = nowy_student(imie, nazwisko, album);
	}
}
void prz_wyswietl(przedmiot* p = prz_poczatek) {
	system("cls");
	cout << "--- LISTA PRZEDMIOTOW ---\n";
	if(p == NULL) {
		cout << "Brak przedmiotow.\n\n";
		return;
	}
	int i = 1;
	do {
		cout << i++ << ". " << p->nazwa << "\n";
		p = p->nast;
	} while(p);
	cout << "\n";
}

przedmiot* prz_pobierz(int nr) {
	if(nr < 1) return NULL;
	przedmiot* p = prz_poczatek;
	int i = 1;
	do {
		if(i++ == nr) return p;
		p = p->nast;
	} while(p);
	return NULL;
}

przedmiot* nowy_przedmiot(string nazwa) {
	przedmiot* p = new przedmiot;
	p->nazwa = nazwa;
	p->nast = NULL;
	return p; // zwracamy adres do nowo utworzonego przedmiotu
}

void dodaj_przedmiot(string nazwa) {
	if(prz_poczatek == NULL) {
		prz_poprz = prz_poczatek = nowy_przedmiot(nazwa);
	} else {
		prz_poprz = prz_poprz->nast = nowy_przedmiot(nazwa);
	}
}

void oc_wyswietl(student* s) {
	if(s == NULL) return;
	system("cls");
	cout << "--- LISTA OCEN DLA: " << s->imie << " " << s->nazwisko << " (" << s->album << ") ---\n";
	if(s->p_ocena == NULL) {
		cout << "Brak ocen do wyswietlenia.\n\n";
		return;
	}
	int i = 1;
	ocena* akt_ocena = s->p_ocena;
	do {
		cout << i++ << ". " << akt_ocena->przedmiot->nazwa << " - " << akt_ocena->wartosc << "\n";
		akt_ocena = akt_ocena->nast;
	} while(akt_ocena);
	cout << "\n";
}

ocena* oc_pobierz(student* s, int nr) {
	if(nr < 1 || s == NULL || s->p_ocena == NULL) return NULL;
	int i = 1;
	ocena* akt_ocena = s->p_ocena;
	do {
		if(i++ == nr) return akt_ocena;
		akt_ocena = akt_ocena->nast;
	} while(akt_ocena);
	return NULL;
}

ocena* nowa_ocena(przedmiot* p, string wartosc) {
	if(p == NULL) return NULL;
	ocena* o = new ocena;
	o->wartosc = wartosc;
	o->przedmiot = p;
	o->nast = NULL;
	return o; // zwracamy adres do nowo utworzonej oceny
}

void dodaj_ocene(student* s, przedmiot* p, string wartosc) {
	if(s == NULL) return;
	if(s->p_ocena == NULL) {
		s->poprz_ocena = s->p_ocena = nowa_ocena(p, wartosc);
	} else {
		s->poprz_ocena = s->poprz_ocena->nast = nowa_ocena(p, wartosc);
	}
}

void usun_ocene(student* s, ocena* o) {
	if(o == NULL) return;
	ocena* akt_ocena = s->p_ocena;
	ocena* poprz_ocena = NULL;
	do {
		if(akt_ocena == o) {
			if(poprz_ocena != NULL) {
				poprz_ocena->nast = akt_ocena->nast;
			} else {
				s->p_ocena = akt_ocena->nast;
			}
			if(s->poprz_ocena == akt_ocena) {
				s->poprz_ocena = poprz_ocena;
			}
			delete akt_ocena;
			return;
		}
		poprz_ocena = akt_ocena;
		akt_ocena = akt_ocena->nast;
	} while(akt_ocena);
}

int main(int argc, char *argv[]) {
	char wybor;
	do {
		cout << "--- MENU ---\n"
			 << "1. lista studentow\n"
			 << "2. nowy student\n"
			 << "3. lista przedmiotow\n"
			 << "4. nowy przedmiot\n"
			 << "5. lista ocen (dla danego studenta)\n"
			 << "6. nowa ocena\n"
			 << "7. usuwanie studenta\n"
			 << "8. usuwanie przedmiotu\n"
			 << "9. usuwanie oceny\n"
			 << "q. wyjdz\n";

		// Ratujemy sytuację, jeśli został wpisany nieodpowiedni znak
		// i pomijamy wszystkie znaki, które "zostały" (np. \n po pobierniu intów):
		if (cin.fail()) {
			cin.get();
		}
		cin.clear();
		cin.sync();

		cin >> wybor;

		// j.w.
		cin.clear();
		cin.sync();

		switch(wybor) {
			case '1': // lista studentow
				st_wyswietl();
				break;
			case '2': // nowy student
				{
					system("cls");
					cout << "--- DODAWANIE STUDENTA ---\n";
					string imie, nazwisko, album;
					cout << "Podaj imie studenta: ";
					getline(cin, imie);
					cout << "Podaj nazwisko studenta: ";
					getline(cin, nazwisko);
					cout << "Podaj nr albumu studenta: ";
					getline(cin, album);
					dodaj_studenta(imie, nazwisko, album);
					st_wyswietl();
				}
				break;
			case '3': // lista przedmiotow
				prz_wyswietl();
				break;
			case '4': // nowy przedmiot
				{
					system("cls");
					cout << "--- DODAWANIE PRZEDMIOTU ---\n";
					string nazwa;
					cout << "Podaj nazwe przedmiotu: ";
					getline(cin, nazwa);
					dodaj_przedmiot(nazwa);
					prz_wyswietl();
				}
				break;
			case '5': // lista ocen
				{
					int nr;
					st_wyswietl();
					cout << "Podaj numer studenta, ktorego oceny chcesz wyswietlic: ";
					cin >> nr;
					student* s = st_pobierz(nr);
					if(s != NULL) {
						oc_wyswietl(s);
					} else {
						cout << "Bledny numer.\n\n";
					}
				}
				break;
			case '6': // nowa ocena
				{
					int nr;
					string wartosc;
					st_wyswietl();
					cout << "Podaj numer studenta, dla ktorego chcesz dodac nowa ocene: ";
					cin >> nr;
					student* s = st_pobierz(nr);
					if(s != NULL) {
						prz_wyswietl();
						cout << "Podaj numer przedmiotu: ";
						cin >> nr;
						przedmiot* p = prz_pobierz(nr);
						if(p != NULL) {
							cout << "Wprowadz ocene: ";
							cin >> wartosc;
							dodaj_ocene(s, p, wartosc);
							oc_wyswietl(s);
						} else {
							cout << "Bledny numer.\n\n";
						}
					} else {
						cout << "Bledny numer.\n\n";
					}
				}
				break;
			case '7': // usuwanie studenta
				{
					int nr;
					st_wyswietl();
					cout << "Podaj numer studenta, ktorego chcesz usunac: ";
					cin >> nr;
					student* s = st_pobierz(nr);
					student* poprz = st_pobierz(nr-1); // to można ładniej...
					if(s != NULL) {
						if(s->p_ocena != NULL) {
							int i = 1;
							ocena* akt_ocena = s->p_ocena;
							do { // usuwamy wszystkie oceny studenta - zwalniamy pamięć
								ocena* tmp = akt_ocena->nast;
								delete akt_ocena;
								akt_ocena = tmp;
							} while(akt_ocena);
						}
						// usuwamy studenta - zwalniamy pamięć:
						if(poprz != NULL) {
							poprz->nast = s->nast;
						} else {
							st_poczatek = s->nast;
						}
						if(st_poprz == s) {
							st_poprz = poprz;
						}
						delete s;
						st_wyswietl();
					} else {
						cout << "Bledny numer.\n\n";
					}
				}
				break;
			case '8': // usuwanie przedmiotu
				{
					int nr;
					prz_wyswietl();
					cout << "Podaj numer przedmiotu, ktory chcesz usunac: ";
					cin >> nr;
					przedmiot* p = prz_pobierz(nr);
					przedmiot* poprz = prz_pobierz(nr-1);
					if(p != NULL) {
						// usuwanie po kolei wszystkich ocen z przypisanym usuwanym przedmiotem
						student* s = st_poczatek;
						if(s != NULL) {
							do {
								if(s->p_ocena != NULL) {
									ocena* akt_ocena = s->p_ocena;
									do {
										ocena* tmp = akt_ocena->nast;
										if(akt_ocena->przedmiot == p) {
											usun_ocene(s, akt_ocena);
										}
										akt_ocena = tmp;
									} while(akt_ocena);
								}
								s = s->nast;
							} while(s);
						}
						// usuwamy studenta - zwalniamy pamięć:
						if(poprz != NULL) {
							poprz->nast = p->nast;
						} else {
							prz_poczatek = p->nast;
						}
						if(prz_poprz == p) {
							prz_poprz = poprz;
						}
						delete p;
						prz_wyswietl();
					} else {
						cout << "Bledny numer.\n\n";
					}
				}
				break;
			case '9': // usuwanie oceny
				{
					int nr;
					st_wyswietl();
					cout << "Podaj numer studenta, ktorego ocene chcesz usunac: ";
					cin >> nr;
					student* s = st_pobierz(nr);
					if(s != NULL) {
						oc_wyswietl(s);
						cout << "Podaj numer oceny do usuniecia: ";
						cin >> nr;
						ocena* o = oc_pobierz(s, nr);
						if(o != NULL) {
							usun_ocene(s, o);
							oc_wyswietl(s);
						} else {
							cout << "Bledny numer.\n\n";
						}
					} else {
						cout << "Bledny numer.\n\n";
					}
				}
				break;
		}
	} while (wybor != 'q');
	return EXIT_SUCCESS;
}