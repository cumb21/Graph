#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <Windows.h> // Для использования Windows Forms
#include <msclr/marshal.h>			
#include <msclr/marshal_cppstd.h>	
// Две библиотеки для маршалинга данных между управляемыми и неуправляемыми типами (Преобразования string в String^).
#include <unordered_set>			// Для использования контейнера для хранения уникальных элементов.
#include <unordered_map>
#include <cmath> // Для использования функций cos и sin
#include <queue>
#include <limits>


using namespace std;
using namespace System;
using namespace msclr::interop;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

void DrawGraph(Dictionary<Char, List<Tuple<Char, float>^>^>^ graph, Graphics^ graphics, PictureBox^ pictureBox);
bool IsEnglishLetter(wchar_t ch);
void FindShortestPath(Dictionary<Char, List<Tuple<Char, float>^>^>^ graph, Char startNode, Char endNode, List<Char>^% path, float% totalDistance);

