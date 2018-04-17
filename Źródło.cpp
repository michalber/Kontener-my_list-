#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <map>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Windows.h>
#include <chrono>
#include "my_list.h"
#include <algorithm>

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

#pragma region zad1

void wyswietl_liste(list<int> lista) {
	list<int>::iterator ite;
	for (ite = lista.begin(); ite != lista.end(); ite++)
	{
		cout << *ite << " ";
	}
	cout << endl;
}

void zad1() {

	list<int> list_p;
	list<int> list_np;
	vector<int> liczby;

	int ilosc_liczb = rand()%50+1;

	srand(time(NULL));

	cout << "Wektor" << endl;
	for (int i = 0;i <= ilosc_liczb;i++) {
		liczby.push_back(rand() % 100 + 1);
		cout << liczby[i] << " ";
	}
	cout << endl;
	

	for (int i = 0; i < liczby.size();i++) {
		if (liczby[i] % 2 == 0) list_p.push_back(liczby[i]);
		else list_np.push_back(liczby[i]);
	}

	cout << "Lista parzysta" << endl;
	wyswietl_liste(list_p);
	cout << "Lista nieparzysta" << endl;
	wyswietl_liste(list_np);

	list_p.sort();
	list_np.sort();

	list_p.merge(list_np);
	cout << "Lista zlaczona posortowana" << endl;
	wyswietl_liste(list_p);


	list<int> lista_koncowa = list_p;
	lista_koncowa.unique();
	lista_koncowa.reverse();
	cout << "Lista koncowa (bez powtarzajacych sie elementow, ustawiona od najwiekszego elementu" << endl;
	wyswietl_liste(lista_koncowa);
}

#pragma endregion

#pragma region zad2
void wektor_pfront(vector<int>& vec,int val) {
	vec.insert(vec.begin(), val);
}

void zad2() {
	list<int> lista;
	vector<int> wektor;
	int size = 10;

	for (int i = 0;i < size;i++) wektor.push_back(i);
	for (int i = 0;i < size;i++) lista.push_back(i);


	cout << "Lista przed i po dodaniu elementu na przod listy" << endl;
	wyswietl_liste(lista);
	auto t1 = Clock::now();
	lista.push_front(100);
	auto t2 = Clock::now();
	wyswietl_liste(lista);
	cout << "Czas dodania do listy: " << chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << endl;
	auto list_time = chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	cout << endl;


	cout << "Wektor przed i po dodaniu elementu na przod wektora" << endl;
	for (int i = 0;i < wektor.size();i++) {
		cout << wektor[i] << " ";
	}
	cout << endl;
	t1 = Clock::now();
	wektor_pfront(wektor, 100);
	t2 = Clock::now();
	for (int i = 0;i < wektor.size();i++) {
		cout << wektor[i] << " ";
	}
	cout << endl;
	cout << "Czas dodania do wektora: " << chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << endl<<endl;

	auto vec_time = chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	
	cout << "Dodanie do wektora jest ~ " << (double)vec_time / list_time << " razy wolniejsze od dodania do listy" << endl;

}

#pragma endregion

#pragma region zad4
template <typename Iter>
void wypisz_na_cout(Iter b, int n)	// wypisz n liczb zaczynajπc od iteratora b
{
	while (n > 0) {
		cout << *b;
		++b;
		if (n > 1)
			cout << ' ';
		--n;
	}
	cout << endl;
}

template <typename Iter>
void wypisz_na_cout(Iter b, Iter e)
{
	while (b != e) {
		cout << *b;
		++b;
		if (b != e)
			cout << ' ';
	}
	cout << '\n';
}

void zad4() {
	int t[20];
	vector<int> v(20);

	for (int i = 0; i < 20; ++i) {
		t[i] = rand()%100+1;
		v[i] = t[i];
	}
	cout << "Cala tablica" << endl;
	wypisz_na_cout(t, t+20);
	cout << "20 elementow tablicy zaczynajac od 3 elementu" << endl;
	wypisz_na_cout(t+2, t+20);
	cout << endl;

	cout << "Caly wektor" << endl;
	wypisz_na_cout(v.begin(), v.size());
	cout << "Wektor zaczynajac od 3 elementu do polowy dlugosci wektora" << endl;
	wypisz_na_cout(v.begin()+2, v.size()/2);
}

#pragma endregion

#pragma region zad5

template <typename Iter, typename Cond, typename Oper>
void wykonaj(Iter b, Iter e, Cond cnd, Oper op)
//			  od	  do	 pod war.  czynnoúÊ
{
	while (b != e) {
		if (cnd(b->second.first,b->second.second))	
			op(b->second.first);	// wskaünik do pierwszego elementu z drugiego elementu mapy map<char,pair<int,bool>>
		++b;
	}
}

struct is_cheap_check
{
	bool operator() (double & val,bool & x)
	{
		if (val > 100 && x)
			return true;
		else
			return false;
	}
};

struct Promocja
{
	int ile_;

	Promocja(int ile) : ile_(ile)
	{ }

	inline void operator() (double & x)
	{
		x = x*(100-ile_) / 100;
	}
};

struct Podwyøka
{
	int ile_;

	Podwyøka(int ile) : ile_(ile)
	{ }

	inline void operator() (double & x)
	{
		x = x*(100 + ile_) / 100;
	}
};

struct VAT
{
	int ile_;

	VAT(int ile) : ile_(ile)
	{ }

	inline void operator() (double & x)
	{
		x = x*(100 + ile_) / 100;
	}
};

void wyswietl_mape(map<char, pair<double, bool>> & buff) {
	for (auto & t : buff)
		std::cout << t.first << " " << t.second.first << " " << t.second.second << "\n";
	cout << endl;
}

void zad5() {
	srand(time(NULL));

	const int liczba_sklepow = 20;

	map<char, pair<double, bool>> mapa;

	for (int i = 0;i < liczba_sklepow;i++) {
		if (i % 3 && i % 5)
			mapa.insert(make_pair('A' + i, make_pair(rand() % 200 + 1, true)));
		else
			mapa.insert(make_pair('A' + i, make_pair(rand() % 200 + 1, false)));
	}

	cout << "Ceny przed obnizka: " << endl;
	wyswietl_mape(mapa);

	VAT vat(23);
	Podwyøka podwyzka(5);
	wykonaj(mapa.begin(), mapa.end(), is_cheap_check(), vat);
	wykonaj(mapa.begin(), mapa.end(), is_cheap_check(), podwyzka);

	cout << "Ceny po dodaniu marzy i VAT: " << endl;
	wyswietl_mape(mapa);


	Promocja promo(20);
	wykonaj(mapa.begin(), mapa.end(), is_cheap_check(), promo);

	cout << "Ceny po obnizce: " << endl;
	wyswietl_mape(mapa);
}

#pragma endregion 


int main() {
	system("color F0");
	zad5();
	/*
	my_list<int> lista;
	lista.push_front(2);
	lista.push_front(1);
	lista.push_front(2);
	lista.push_front(1);
	wypisz_na_cout(lista.begin(), lista.end());

	lista.push_back(10);
	
	lista.push_back(2);

	wypisz_na_cout(lista.begin(), lista.end());

	typedef vector<double>::iterator it_wektora;
	//function_requires< ForwardIteratorConcept<it_wektora> >();

	typedef my_list<double>::iterator it_listy;
	//function_requires< ForwardIteratorConcept<it_listy> >();

	cout << "Wszystko OK.\n";
	*/
	getchar();
	return 0;
}