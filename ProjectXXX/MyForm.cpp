#include "MyForm.h"
#include "Header.h"


using namespace ProjectXXX;
[STAThread]
int WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//// ������������� �������
	/*AllocConsole();
	freopen("CONOUT$", "w", stdout);*/

	// ��������� ��������� �������
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
