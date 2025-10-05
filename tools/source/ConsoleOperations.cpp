#include "ConsoleOperations.h"
namespace Cfl {
	void DLLIMPORT Color (int a) { //白蓝绿紫红靛黄灰
		if (a == 0) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		if (a == 1) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);

		if (a == 2) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);

		if (a == 3) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);

		if (a == 4) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);

		if (a == 5) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);

		if (a == 6) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);

		if (a == 7) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	}

	void DLLIMPORT gotoxy (int x, int y) {
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), pos);
	}
};
