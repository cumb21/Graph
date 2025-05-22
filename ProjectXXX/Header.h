#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <Windows.h> // ��� ������������� Windows Forms
#include <msclr/marshal.h>			
#include <msclr/marshal_cppstd.h>	
// ��� ���������� ��� ���������� ������ ����� ������������ � �������������� ������ (�������������� string � String^).
#include <unordered_set>			// ��� ������������� ���������� ��� �������� ���������� ���������.
#include <unordered_map>
#include <cmath> // ��� ������������� ������� cos � sin
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

