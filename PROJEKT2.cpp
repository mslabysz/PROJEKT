#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdio>
using namespace std;


void gotoxy(int x, int y) { //funkcja ustawiająca kursor w miejsce wspolrzednych
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void screensize(int& width, int& height) { //podana funkcja ustalająca wielkość ekranu
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

void showASCII() { //dodatkowa funkcja pokazująca użytkownikowi jaki znak otrzyma po wpisaniu danego kodu ASCII
	system("cls"); //wyczyszczenie ekranu
	int number;
	cout << "Podaj numer z tabeli ASCII: ";
	cin >> number;
	char character = (char)number; //zamiana numeru podanego przez uzytkownika na znak kodu ASCII
	cout << "Numer: " << number << endl;
	cout << "Symbol: " << character << endl;
}

void draw(int size,char character,int x, int y){ //funkcja drugukąca figurę
	for (int i = 0; i < size; i++) //petla rysująca linie ukośne
		{
			gotoxy(x + i, y - i); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
			gotoxy(x + i, y + i); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
		}
	for (int i = 0; i < size*2; i++) //pętla rysująca linie poziome
		{
			gotoxy(x - i+size, y-size); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
			gotoxy(x - i+size, y + size); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
		}
}

void moveChar() //funkcja odpowiadająca za drukowanie i manipulowanie figurą
{
	int number;
	int size;
	
	cout<<endl;
	
	cout << "Podaj numer z tabeli ASCII: "<<endl;
	cin >> number;
	char character = (char)number;
	
	cout<< "Podaj wielkosc wzoru: ";
	cin>>size;
	
	system("cls"); //wyczyszczenie ekranu
	int width = 0, height = 0;
	screensize(width, height); 
	int x = width / 2, y = height / 2; //ustawienie środka ekranu
	
	while(true){
		
		if (GetAsyncKeyState(VK_UP)) { //sprawdzenie czy zostala wcisnieta strzalka w gore
			if (y - size > 0) y--; //sprawdzenie czy y znajduje sie w obszarze ekranu i zmiana wspolrzednej
			
		}
		else if (GetAsyncKeyState(VK_DOWN)) { //sprawdzenie czy zostala wcisnieta strzalka w dół
			if (y + size < height-1) y++; //sprawdzenie czy y znajduje sie w obszarze ekranu i zmiana wspolrzednej
			
		}
		else if (GetAsyncKeyState(VK_RIGHT)) { //sprawdzenie czy zostala wcisnieta strzalka w prawo
			if (x + size < width-1) x++; //sprawdzenie czy x znajduje sie w obszarze ekranu i zmiana wspolrzednej
			
		}
		else if (GetAsyncKeyState(VK_LEFT)) { //sprawdzenie czy zostala wcisnieta strzalka w lewo
			if (x - size > 0) x--; //sprawdzenie czy x znajduje sie w obszarze ekranu i zmiana wspolrzednej
			
		}
		else if (GetAsyncKeyState(VK_OEM_PLUS)) { //sprawdzenie czy zostal wcisniety plus
			if(y - size>0 && y + size<height-1 && x + size<width-1 && x - size>0) size++; //sprawdzenie czy figura mieści się w granicach i jeżeli tak, powiększenie
			
		}
		else if (GetAsyncKeyState(VK_OEM_MINUS)) { //sprawdzenie czy zostal wcisniety minus
			if(size > 2) size--; //pomniejszenie figury
		}
		system("cls"); //wyczyszczenie ekranu
		
		draw(size,character,x,y); //wywołanie funkcji rysującej figure

		gotoxy(x, y); //ustawienie kursora w lewym gornym rogu ekranu
		Sleep(10); //zatrzymanie dzialania na 10 milisekund, efekt fizualny
	}
	cout << endl;
}

int main()
{
	cout << "NACISNIJ F1 ABY WYSWIETLIC ZNAK ASCII PO KODZIE. NACISNIJ F2 ABY WYSWIETLIC FIGURE.";
	_getch(); 
	if (GetAsyncKeyState(VK_F1) != 0) //sprawadzenie czy zostal nacisniety klawisz F1
		showASCII(); //wywołanie funkcji
	if (GetAsyncKeyState(VK_F2) != 0) //sprawadzenie czy zostal nacisniety klawisz F2
		moveChar(); //wywołanie funkcji
    return 0;
}
