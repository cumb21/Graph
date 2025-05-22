#include "MyForm.h"
#include "Header.h"


using namespace ProjectXXX;
[STAThread]
int WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//// Инициализация консоли
	/*AllocConsole();
	freopen("CONOUT$", "w", stdout);*/

	// Настройка кодировки консоли
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm);
	setlocale(LC_ALL, "Rus");
	unordered_map<char, vector<pair<char, float>>> graph = {
	};
	return 0;
}
