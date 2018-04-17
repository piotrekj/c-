#include <iostream>
#include <cstdlib>
#define ROZMIAR 50


using namespace std;

class kalkulator_naukowy {
private:
	double wynik;

public:
	double pierwsza_dana;
	double druga_dana;
	kalkulator_naukowy(double pierwsza_dana = 1, double druga_dana = 1, double wynik = 1) {
		this->wynik = wynik;}                                                               //wskazuje obiekt, dla którego zostala wywolana metoda
	double dodawanie() {
		wynik = pierwsza_dana + druga_dana;
		return wynik;}
	double mnozenie() {
		wynik = pierwsza_dana * druga_dana;
		return wynik;}
	double dzielenie() {
		wynik = pierwsza_dana / druga_dana;
		return wynik;}
	void modulo() {
		while (pierwsza_dana >= druga_dana) {
			pierwsza_dana = pierwsza_dana - druga_dana;}
	}
};

int main() {
	kalkulator_naukowy kalk;
	double stos[ROZMIAR];
	int skladowa_stos = 0;
	char znak;

	while (true)
	{
		if (skladowa_stos == 0) {
			cin >> kalk.pierwsza_dana;
			stos[skladowa_stos++] = kalk.pierwsza_dana;
		}
		cin >> znak;
		switch (znak)
		{
		case '+':
			cin >> kalk.pierwsza_dana;
			stos[skladowa_stos++] = kalk.pierwsza_dana;
			break;
		case '-':
			cin >> kalk.pierwsza_dana;
			kalk.pierwsza_dana = (0 - kalk.pierwsza_dana);
			stos[skladowa_stos++] = kalk.pierwsza_dana;             //na stos wrzucamy z minusem
			break;
		case '*':
			cin >> kalk.druga_dana;
			--skladowa_stos;                                  //wykonujemy napisanie pierwszego argumentu,(jest na stosie)
			kalk.pierwsza_dana = kalk.mnozenie();
			stos[skladowa_stos++] = kalk.pierwsza_dana;
			break;
		case '/':
			cin >> kalk.druga_dana;
			if (kalk.druga_dana == 0) {
				cout << "Nie dzielimy przez 0" << endl;
				system("pause");
				cin.ignore(256, '\n');
				cin.clear();
				skladowa_stos = 0;
			}
			--skladowa_stos;
			kalk.pierwsza_dana = kalk.dzielenie();
			stos[skladowa_stos++] = kalk.pierwsza_dana;
			break;
		case '%':
			cin >> kalk.druga_dana;
			if (kalk.druga_dana == 0) {
				cout << "Blad: x % 0 ?!" << endl;
				system("pause");
				cin.ignore(256, '\n');
				cin.clear();
				skladowa_stos = 0;
			}
			--skladowa_stos;
			kalk.modulo();
			stos[skladowa_stos++] = kalk.pierwsza_dana;
			break;
		case '=':
			skladowa_stos = skladowa_stos - 2;
			for (; skladowa_stos >= 0; skladowa_stos--) {                      //zsumowanie liczb na stosie
				kalk.druga_dana = stos[skladowa_stos];
				kalk.pierwsza_dana = kalk.dodawanie();
				stos[skladowa_stos] = kalk.pierwsza_dana;
			}
			cout << kalk.pierwsza_dana << endl;
			system("pause");
			cin.clear();
			skladowa_stos = 0;                                               //dla  wprowadzania kolejnego dzialania
			system("cls");
			break;
		default:
			cout << "Wystapil blad!\n";
			break;}
	}
	return 0;
}
