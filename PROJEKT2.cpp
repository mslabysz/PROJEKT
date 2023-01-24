#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdio>
using namespace std;


void gotoxy(int x, int y) { //funkcja ustawiaj¹ca kursor w miejsce wspolrzednych
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void screensize(int& width, int& height) { //podana funkcja ustalaj¹ca wielkoœæ ekranu
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

void showASCII() { //dodatkowa funkcja pokazuj¹ca u¿ytkownikowi jaki znak otrzyma po wpisaniu danego kodu ASCII
	system("cls"); //wyczyszczenie ekranu
	int number;
	cout << "Podaj numer z tabeli ASCII: ";
	cin >> number;
	char character = (char)number; //zamiana numeru podanego przez uzytkownika na znak kodu ASCII
	cout << "Numer: " << number << endl;
	cout << "Symbol: " << character << endl;
}

void moveChar() //funkcja odpowiadaj¹ca za drukowanie i manipulowanie figur¹
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
	int x = width / 2, y = height / 2; //ustawienie œrodka ekranu
	while(true){
		
		if (GetAsyncKeyState(VK_UP)) { //sprawdzenie czy zostala wcisnieta strzalka w gore
			if (y > 0) y--; //sprawdzenie czy y znajduje sie w obszarze ekranu i zmiana wspolrzednej
			system("cls"); //wyczyszczenie ekranu
		}
		else if (GetAsyncKeyState(VK_DOWN)) { //sprawdzenie czy zostala wcisnieta strzalka w dó³
			if (y < height-1) y++; //sprawdzenie czy y znajduje sie w obszarze ekranu i zmiana wspolrzednej
			system("cls");
		}
		else if (GetAsyncKeyState(VK_RIGHT)) { //sprawdzenie czy zostala wcisnieta strzalka w prawo
			if (x < width-1) x++; //sprawdzenie czy x znajduje sie w obszarze ekranu i zmiana wspolrzednej
			system("cls"); //wyczyszczenie ekranu
		}
		else if (GetAsyncKeyState(VK_LEFT)) { //sprawdzenie czy zostala wcisnieta strzalka w lewo
			if (x > 0) x--; //sprawdzenie czy x znajduje sie w obszarze ekranu i zmiana wspolrzednej
			system("cls"); //wyczyszczenie ekranu
		}
		else if (GetAsyncKeyState(VK_OEM_PLUS)) { //sprawdzenie czy zostal wcisniety plus
			size++; //powiekszenie figury
			system("cls"); //wyczyszczenie ekranu
		}
		else if (GetAsyncKeyState(VK_OEM_MINUS)) { //sprawdzenie czy zostal wcisniety minus
			if(size > 2)size--; //pomniejszenie figury
			system("cls"); //wyczyszczenie ekranu
		}
		
		
		for (int i = 0; i <= size; i++) //petle rysuj¹ce figure znakiem
		{
			gotoxy(x + i, y - i); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
		}
		for (int i = 0; i < size; i++) //petle rysuj¹ce figure znakiem
		{
			gotoxy(x + i, y + i); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
		}
		for (int i = 0; i < size; i++) //petle rysuj¹ce figure znakiem
		{
			gotoxy(x - i, y-size); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
		}
		for (int i = 0; i < size; i++) //petle rysuj¹ce figure znakiem
		{
			gotoxy(x - i, y + size); //ustawienie kursora w punkcie w ktorym ma sie narysowac znak
			cout << character; //rysowanie znaku
		}


		gotoxy(0, 0); //ustawienie kursora w lewym gornym rogu ekranu
		Sleep(10); //zatrzymanie dzialania na 10 milisekund, efekt fizualny
	}
	cout << endl;
}

int main()
{
	cout << "NACISNIJ F1 ABY WYSWIETLIC ZNAK ASCII PO KODZIE. NACISNIJ F2 ABY WYSWIETLIC FIGURE.";
	_getch(); 
	if (GetAsyncKeyState(VK_F1) != 0) //sprawadzenie czy zostal nacisniety klawisz F1
		showASCII(); //wywo³anie funkcji
	if (GetAsyncKeyState(VK_F2) != 0) //sprawadzenie czy zostal nacisniety klawisz F2
		moveChar(); //wywo³anie funkcji
    return 0;
}
