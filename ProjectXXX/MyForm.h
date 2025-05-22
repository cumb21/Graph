#pragma once
#include "Header.h"

namespace ProjectXXX {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace msclr::interop;
    using namespace System::Collections::Generic;

    // ���������� ������ AddEdgeForm
    public ref class AddEdgeForm : public Form
    {
    public:
        AddEdgeForm(Dictionary<Char, List<Tuple<Char, float>^>^>^ graph)
        {
            InitializeComponent();
            this->graph = graph;

            // ���������� ComboBox ������ �����
            for each (Char node in graph->Keys)
            {
                fromComboBox->Items->Add(node);
                toComboBox->Items->Add(node);
            }

            // ��������� ����� � ���������� � ComboBox
            fromComboBox->KeyPress += gcnew KeyPressEventHandler(this, &AddEdgeForm::ComboBox_KeyPress);
            toComboBox->KeyPress += gcnew KeyPressEventHandler(this, &AddEdgeForm::ComboBox_KeyPress);
        }

        // ����� ��� ��������� ������ ��������������
        void SetEditMode(String^ isEditMode)
        {
            if (isEditMode == "Add") {
                this->Text = "���������� �����";
                this->addEdgeButton->Visible = true;
                this->editEdgeButton->Visible = false;
                this->deleteEdgeButton->Visible = false;
                this->findRouteButton->Visible = false;
            }
            if (isEditMode == "Edit")
            {
                this->Text = "��������� �����";
                this->addEdgeButton->Visible = false;
                this->editEdgeButton->Visible = true;
                this->deleteEdgeButton->Visible = false;
                this->findRouteButton->Visible = false;
            }
            if (isEditMode == "Delete")
            {
                this->deleteEdgeButton->Visible = true;
                this->Text = "�������� �����";
                this->addEdgeButton->Visible = false;
                this->editEdgeButton->Visible = false;
                this->weightLabel->Visible = false;
                this->weightTextBox->Visible = false;
                this->findRouteButton->Visible = false;
            }
            if (isEditMode == "Find") {
                this->deleteEdgeButton->Visible = false;
                this->Text = "����� ��������";
                this->addEdgeButton->Visible = false;
                this->editEdgeButton->Visible = false;
                this->weightLabel->Visible = false;
                this->weightTextBox->Visible = false;
            }
        }

    protected:
        ~AddEdgeForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        ComboBox^ fromComboBox;
        ComboBox^ toComboBox;
        TextBox^ weightTextBox;
        Button^ addEdgeButton;
        Button^ findRouteButton;
        Button^ editEdgeButton;
        Button^ deleteEdgeButton;
        Label^ fromLabel;
        Label^ toLabel;
        Label^ weightLabel;
        System::ComponentModel::Container^ components;
        Dictionary<Char, List<Tuple<Char, float>^>^>^ graph;

        void InitializeComponent()
        {
            this->components = gcnew System::ComponentModel::Container();
            this->fromComboBox = gcnew ComboBox();
            this->toComboBox = gcnew ComboBox();
            this->weightTextBox = gcnew TextBox();
            this->addEdgeButton = gcnew Button();
            this->findRouteButton = gcnew Button();
            this->editEdgeButton = gcnew Button();
            this->deleteEdgeButton = gcnew Button();
            this->fromLabel = gcnew Label();
            this->toLabel = gcnew Label();
            this->weightLabel = gcnew Label();
            this->SuspendLayout();

            // ��������� Label ��� ������ �������
            this->fromLabel->Text = "������ ������� �����";
            this->fromLabel->Location = System::Drawing::Point(80, 27);

            // ��������� ComboBox ��� ������ ������ �������
            this->fromComboBox->Location = System::Drawing::Point(80, 50);

            // ��������� Label ��� ������ �������
            this->toLabel->Text = "������ ������� �����";
            this->toLabel->Location = System::Drawing::Point(80, 77);

            // ��������� ComboBox ��� ������ ������ �������
            this->toComboBox->Location = System::Drawing::Point(80, 100);

            // ��������� Label ��� ���� �����
            this->weightLabel->Text = "��� �����";
            this->weightLabel->Location = System::Drawing::Point(80, 127);

            // ��������� TextBox ��� ����� ����
            this->weightTextBox->Location = System::Drawing::Point(80, 150);

            // ��������� ������ ��� ���������� �����
            this->addEdgeButton->Text = "�������� �����";
            this->addEdgeButton->Location = System::Drawing::Point(80, 200);
            this->addEdgeButton->Click += gcnew System::EventHandler(this, &AddEdgeForm::AddEdgeButton_Click);

            // ��������� ������ ��� ��������� �����
            this->editEdgeButton->Text = "�������� �����";
            this->editEdgeButton->Location = System::Drawing::Point(80, 200);
            this->editEdgeButton->Click += gcnew System::EventHandler(this, &AddEdgeForm::EditEdgeButton_Click);

            // ��������� ������ ��� �������� �����
            this->deleteEdgeButton->Text = "������� �����";
            this->deleteEdgeButton->Location = System::Drawing::Point(80, 200);
            this->deleteEdgeButton->Click += gcnew System::EventHandler(this, &AddEdgeForm::DeleteEdgeButton_Click);

            // ��������� ������ ��� ������ ����������� ��������
            this->findRouteButton->Text = "����� �������";
            this->findRouteButton->Location = System::Drawing::Point(80, 200);
            this->findRouteButton->Click += gcnew System::EventHandler(this, &AddEdgeForm::FindRouteButton_Click);

            // ���������� ��������� �� �����
            this->Controls->Add(this->fromLabel);
            this->Controls->Add(this->fromComboBox);
            this->Controls->Add(this->toLabel);
            this->Controls->Add(this->toComboBox);
            this->Controls->Add(this->weightLabel);
            this->Controls->Add(this->weightTextBox);
            this->Controls->Add(this->addEdgeButton);
            this->Controls->Add(this->findRouteButton);
            this->Controls->Add(this->editEdgeButton);
            this->Controls->Add(this->deleteEdgeButton);
            this->Text = "���������� �����";
            this->AutoSize = true;
            this->ClientSize = System::Drawing::Size(280, 250);
            this->StartPosition = FormStartPosition::CenterScreen; // Center the form
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void ComboBox_KeyPress(System::Object^ sender, KeyPressEventArgs^ e)
        {
            // ��������� ���� ������ ���������� ����
            if (!Char::IsLetter(e->KeyChar) || e->KeyChar == ' ')
            {
                e->Handled = true;
            }
        }

        void AddEdgeButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // ��������� ��������� ������ � ����
            if (fromComboBox->SelectedItem != nullptr && toComboBox->SelectedItem != nullptr && !String::IsNullOrWhiteSpace(weightTextBox->Text))
            {
                Char fromNode = safe_cast<Char>(fromComboBox->SelectedItem);
                Char toNode = safe_cast<Char>(toComboBox->SelectedItem);
                // ��������, ����� ������� �� ���� �����������
                if (fromNode == toNode)
                {
                    MessageBox::Show("������ � ������ ������� �� ����� ���� �����������.");
                    return;
                }

                String^ inputText = weightTextBox->Text;
                float weight;

                // �������� ������������ ����� ����
                if (!Single::TryParse(inputText, weight))
                {
                    MessageBox::Show("��� ����� ������ ���� ������.");
                    return;
                }

                // �������� ������������� ����� � ����� ������������
                bool edgeExists = false;
                for each (Tuple<Char, float> ^ edge in graph[fromNode])
                {
                    if (edge->Item1 == toNode)
                    {
                        edgeExists = true;
                        break;
                    }
                }
                if (!edgeExists)
                {
                    for each (Tuple<Char, float> ^ edge in graph[toNode])
                    {
                        if (edge->Item1 == fromNode)
                        {
                            edgeExists = true;
                            break;
                        }
                    }
                }

                if (!edgeExists)
                {
                    // ���������� ����� � ����
                    graph[fromNode]->Add(gcnew Tuple<Char, float>(toNode, weight));
                    graph[toNode]->Add(gcnew Tuple<Char, float>(fromNode, weight));
                    MessageBox::Show("����� ������� ���������.");
                    this->Close();
                }
                else
                {
                    MessageBox::Show("����� ��� ����������.");
                }
            }
            else
            {
                MessageBox::Show("����������, �������� ��� ������� � ������� ���.");
            }
        }

        // ���������� ������� Click ��� ������ EditEdgeButton
        void EditEdgeButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // ��������� ��������� ������ � ������ ����
            if (fromComboBox->SelectedItem != nullptr && toComboBox->SelectedItem != nullptr && !String::IsNullOrWhiteSpace(weightTextBox->Text))
            {
                Char fromNode = safe_cast<Char>(fromComboBox->SelectedItem);
                Char toNode = safe_cast<Char>(toComboBox->SelectedItem);
                float newWeight;

                // �������� ������������ ����� ����
                if (!Single::TryParse(weightTextBox->Text, newWeight))
                {
                    MessageBox::Show("��� ����� ������ ���� ������.");
                    return;
                }

                // �������� ������������� ����� � ����� ������������
                bool edgeExists = false;
                for each (Tuple<Char, float> ^ edge in graph[fromNode])
                {
                    if (edge->Item1 == toNode)
                    {
                        // ��������� ���� �����
                        graph[fromNode]->Remove(edge);
                        graph[fromNode]->Add(gcnew Tuple<Char, float>(toNode, newWeight));
                        graph[toNode]->Remove(gcnew Tuple<Char, float>(fromNode, edge->Item2));
                        graph[toNode]->Add(gcnew Tuple<Char, float>(fromNode, newWeight));
                        MessageBox::Show("��� ����� ������� �������.");
                        edgeExists = true;
                        this->Close();
                        break;
                    }
                }
                if (!edgeExists)
                {
                    for each (Tuple<Char, float> ^ edge in graph[toNode])
                    {
                        if (edge->Item1 == fromNode)
                        {
                            // ��������� ���� �����
                            graph[toNode]->Remove(edge);
                            graph[toNode]->Add(gcnew Tuple<Char, float>(fromNode, newWeight));
                            graph[fromNode]->Remove(gcnew Tuple<Char, float>(toNode, edge->Item2));
                            graph[fromNode]->Add(gcnew Tuple<Char, float>(toNode, newWeight));
                            MessageBox::Show("��� ����� ������� �������.");
                            edgeExists = true;
                            this->Close();
                            break;
                        }
                    }
                }

                if (!edgeExists)
                {
                    MessageBox::Show("����� �� ����������.");
                }
            }
            else
            {
                MessageBox::Show("����������, �������� ��� ������� � ������� ����� ���.");
            }
        }

        void DeleteEdgeButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // ��������� ��������� ������
            if (fromComboBox->SelectedItem != nullptr && toComboBox->SelectedItem != nullptr)
            {
                Char fromNode = safe_cast<Char>(fromComboBox->SelectedItem);
                Char toNode = safe_cast<Char>(toComboBox->SelectedItem);

                // �������� ����� � ����� ������������
                bool edgeExists = false;

                // �������� ����� �� fromNode � toNode
                for each (Tuple<Char, float> ^ edge in graph[fromNode])
                {
                    if (edge->Item1 == toNode)
                    {
                        graph[fromNode]->Remove(edge);
                        edgeExists = true;
                        break;
                    }
                }

                // �������� ����� �� toNode � fromNode
                if (edgeExists)
                {
                    for each (Tuple<Char, float> ^ reverseEdge in graph[toNode])
                    {
                        if (reverseEdge->Item1 == fromNode)
                        {
                            graph[toNode]->Remove(reverseEdge);
                            break;
                        }
                    }

                    MessageBox::Show("����� ������� �������.");
                    this->Close();
                }
                else
                {
                    MessageBox::Show("����� �� ����������.");
                }
            }
            else
            {
                MessageBox::Show("����������, �������� ��� �������.");
            }
        }

        // ���������� ������� ������� �� ������ FindRouteButton
        void FindRouteButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // ��������� ��������� ������
            Char startNode = safe_cast<Char>(fromComboBox->SelectedItem);
            Char endNode = safe_cast<Char>(toComboBox->SelectedItem);

            // �������� ������������ ������ ������
            if (startNode == '\0' || endNode == '\0' || startNode == endNode)
            {
                MessageBox::Show("����������, �������� ��� ������ �������.");
                return;
            }

            // ����� ����������� ����
            List<Char>^ path;
            float totalDistance;
            FindShortestPath(graph, startNode, endNode, path, totalDistance);

            // ����������� ����������
            if (path->Count > 0)
            {
                String^ pathStr = "���������� �������: ";
                for each (Char node in path)
                {
                    pathStr += node + " -> ";
                }
                pathStr = pathStr->TrimEnd(gcnew cli::array<wchar_t>{' ', '>', '-'});
                pathStr += "\n����� ����� ��������: " + totalDistance;
                MessageBox::Show(pathStr);
            }
            else
            {
                MessageBox::Show("������� ����� ���������� ��������� �� ������.");
            }
        }
    };

    /// <summary>
    /// ������ ��� MyForm
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            // ������������� �����
            graph = gcnew Dictionary<Char, List<Tuple<Char, float>^>^>();

            // ������������� ������� Graphics
            graphics = pictureBox1->CreateGraphics();
        }

        void EnableButton(int VertCount, int EdgeCount)
        {
            if (VertCount <= 2) {
                AddEdge->Enabled = false;
                EditEdge->Enabled = false;
                DeleteEdge->Enabled = false;
                FindRoute->Enabled = false;
            }
            if (VertCount >= 2 && EdgeCount < 1) {
                AddEdge->Enabled = true;
                EditEdge->Enabled = false;
                DeleteEdge->Enabled = false;
                FindRoute->Enabled = false;
            }
            if (VertCount >= 2 && EdgeCount >= 1) {
                AddEdge->Enabled = true;
                EditEdge->Enabled = true;
                DeleteEdge->Enabled = true;
                FindRoute->Enabled = true;
            }
        }

    private:
        void UpdateButtonsState()
        {
            int edgeCount = 0;
            // ������� ���� ������� ����� � �����
            for each (List<Tuple<Char, float>^> ^ edges in graph->Values)
            {
                // ���������� ���������� ����� �� �������� ������ � ������ ����� �����
                edgeCount += edges->Count;
            }
            EnableButton(graph->Count, edgeCount);
        }

        Graphics^ graphics;

    protected:
        /// <summary>
        /// ���������� ��� ������������ �������.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    protected:
    private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
    private: System::Windows::Forms::Button^ OpenButton;
    private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
    private: System::Windows::Forms::Button^ InfoButton1;
    private: System::Windows::Forms::GroupBox^ groupBoxOpen;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::GroupBox^ EdgeBox;
    private: System::Windows::Forms::Button^ SaveButton;
    private: System::Windows::Forms::Button^ DeleteEdge;
    private: System::Windows::Forms::Button^ EditEdge;
    private: System::Windows::Forms::Button^ AddEdge;
    private: System::Windows::Forms::GroupBox^ VertBox;
    private: System::Windows::Forms::Button^ AddVert;
    private: System::Windows::Forms::Button^ FindRoute;
    private: System::Windows::Forms::TextBox^ AddVertTBox;
    private: System::Windows::Forms::TextBox^ DeleteVertTBox;
    private: System::Windows::Forms::Button^ DeleteVert;
    private: System::Windows::Forms::Button^ ClearGraphButton; // ������ ������� �����
    private:
        /// <summary>
        /// ������������ ���������� ������������.
        /// </summary>
        System::ComponentModel::Container^ components;
    private: System::Windows::Forms::Label^ VertInfoBox;

           // ���������� ����� ��� ����� ������
           // ���������� ����� � �������������� ����������� �����������
           System::Collections::Generic::Dictionary<Char, System::Collections::Generic::List<Tuple<Char, float>^>^>^ graph;

#pragma region Windows Form Designer generated code
           /// <summary>
           /// ��������� ����� ��� ��������� ������������ � �� ���������
           /// ���������� ����� ������ � ������� ��������� ����.
           /// </summary>
           void InitializeComponent(void)
           {
               this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
               this->OpenButton = (gcnew System::Windows::Forms::Button());
               this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
               this->InfoButton1 = (gcnew System::Windows::Forms::Button());
               this->groupBoxOpen = (gcnew System::Windows::Forms::GroupBox());
               this->SaveButton = (gcnew System::Windows::Forms::Button());
               this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
               this->EdgeBox = (gcnew System::Windows::Forms::GroupBox());
               this->DeleteEdge = (gcnew System::Windows::Forms::Button());
               this->EditEdge = (gcnew System::Windows::Forms::Button());
               this->AddEdge = (gcnew System::Windows::Forms::Button());
               this->VertBox = (gcnew System::Windows::Forms::GroupBox());
               this->VertInfoBox = (gcnew System::Windows::Forms::Label());
               this->DeleteVertTBox = (gcnew System::Windows::Forms::TextBox());
               this->DeleteVert = (gcnew System::Windows::Forms::Button());
               this->AddVertTBox = (gcnew System::Windows::Forms::TextBox());
               this->AddVert = (gcnew System::Windows::Forms::Button());
               this->FindRoute = (gcnew System::Windows::Forms::Button());
               this->ClearGraphButton = (gcnew System::Windows::Forms::Button()); // ������������� ������ ������� �����
               this->groupBoxOpen->SuspendLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
               this->EdgeBox->SuspendLayout();
               this->VertBox->SuspendLayout();
               this->SuspendLayout();
               //
               // OpenButton
               //
               this->OpenButton->Location = System::Drawing::Point(45, 33);
               this->OpenButton->Name = L"OpenButton";
               this->OpenButton->Size = System::Drawing::Size(134, 23);
               this->OpenButton->TabIndex = 1;
               this->OpenButton->Text = L"������� ����";
               this->OpenButton->UseVisualStyleBackColor = true;
               this->OpenButton->Click += gcnew System::EventHandler(this, &MyForm::OpenButton_Click);
               //
               // openFileDialog1
               //
               this->openFileDialog1->FileName = L"openFileDialog1";
               //
               // InfoButton1
               //
               this->InfoButton1->Location = System::Drawing::Point(196, 11);
               this->InfoButton1->Name = L"InfoButton1";
               this->InfoButton1->Size = System::Drawing::Size(22, 22);
               this->InfoButton1->TabIndex = 14;
               this->InfoButton1->Text = L"\?";
               this->InfoButton1->UseVisualStyleBackColor = true;
               this->InfoButton1->Click += gcnew System::EventHandler(this, &MyForm::InfoButton_Click);
               //
               // groupBoxOpen
               //
               this->groupBoxOpen->Controls->Add(this->SaveButton);
               this->groupBoxOpen->Controls->Add(this->OpenButton);
               this->groupBoxOpen->Controls->Add(this->InfoButton1);
               this->groupBoxOpen->Location = System::Drawing::Point(49, 297);
               this->groupBoxOpen->Name = L"groupBoxOpen";
               this->groupBoxOpen->Size = System::Drawing::Size(224, 100);
               this->groupBoxOpen->TabIndex = 15;
               this->groupBoxOpen->TabStop = false;
               this->groupBoxOpen->Text = L"�������������� � �������";
               //
               // SaveButton
               //
               this->SaveButton->Location = System::Drawing::Point(45, 62);
               this->SaveButton->Name = L"SaveButton";
               this->SaveButton->Size = System::Drawing::Size(134, 23);
               this->SaveButton->TabIndex = 15;
               this->SaveButton->Text = L"��������� � ����";
               this->SaveButton->UseVisualStyleBackColor = true;
               this->SaveButton->Click += gcnew System::EventHandler(this, &MyForm::SaveButton_Click);
               //
               // pictureBox1
               //
               this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
               this->pictureBox1->Location = System::Drawing::Point(329, 45);
               this->pictureBox1->Name = L"pictureBox1";
               this->pictureBox1->Size = System::Drawing::Size(317, 173);
               this->pictureBox1->TabIndex = 16;
               this->pictureBox1->TabStop = false;
               //
               // EdgeBox
               //
               this->EdgeBox->Controls->Add(this->DeleteEdge);
               this->EdgeBox->Controls->Add(this->EditEdge);
               this->EdgeBox->Controls->Add(this->AddEdge);
               this->EdgeBox->Cursor = System::Windows::Forms::Cursors::Default;
               this->EdgeBox->Location = System::Drawing::Point(49, 164);
               this->EdgeBox->Name = L"EdgeBox";
               this->EdgeBox->Size = System::Drawing::Size(224, 110);
               this->EdgeBox->TabIndex = 17;
               this->EdgeBox->TabStop = false;
               this->EdgeBox->Text = L"�������������� �����";
               //
               // DeleteEdge
               //
               this->DeleteEdge->Enabled = false;
               this->DeleteEdge->Location = System::Drawing::Point(45, 77);
               this->DeleteEdge->Name = L"DeleteEdge";
               this->DeleteEdge->Size = System::Drawing::Size(134, 23);
               this->DeleteEdge->TabIndex = 2;
               this->DeleteEdge->Text = L"������� �����";
               this->DeleteEdge->UseVisualStyleBackColor = true;
               this->DeleteEdge->Click += gcnew System::EventHandler(this, &MyForm::DeleteEdge_Click);
               //
               // EditEdge
               //
               this->EditEdge->Enabled = false;
               this->EditEdge->Location = System::Drawing::Point(45, 48);
               this->EditEdge->Name = L"EditEdge";
               this->EditEdge->Size = System::Drawing::Size(134, 23);
               this->EditEdge->TabIndex = 1;
               this->EditEdge->Text = L"�������� ���";
               this->EditEdge->UseVisualStyleBackColor = true;
               this->EditEdge->Click += gcnew System::EventHandler(this, &MyForm::EditEdge_Click);
               //
               // AddEdge
               //
               this->AddEdge->Enabled = false;
               this->AddEdge->Location = System::Drawing::Point(45, 19);
               this->AddEdge->Name = L"AddEdge";
               this->AddEdge->Size = System::Drawing::Size(134, 23);
               this->AddEdge->TabIndex = 0;
               this->AddEdge->Text = L"�������� �����";
               this->AddEdge->UseVisualStyleBackColor = true;
               this->AddEdge->Click += gcnew System::EventHandler(this, &MyForm::AddEdge_Click);
               //
               // VertBox
               //
               this->VertBox->Controls->Add(this->VertInfoBox);
               this->VertBox->Controls->Add(this->DeleteVertTBox);
               this->VertBox->Controls->Add(this->DeleteVert);
               this->VertBox->Controls->Add(this->AddVertTBox);
               this->VertBox->Controls->Add(this->AddVert);
               this->VertBox->Location = System::Drawing::Point(49, 21);
               this->VertBox->Name = L"VertBox";
               this->VertBox->Size = System::Drawing::Size(224, 127);
               this->VertBox->TabIndex = 18;
               this->VertBox->TabStop = false;
               this->VertBox->Text = L"�������������� ������";
               //
               // VertInfoBox
               //
               this->VertInfoBox->Location = System::Drawing::Point(6, 16);
               this->VertInfoBox->Name = L"VertInfoBox";
               this->VertInfoBox->Size = System::Drawing::Size(212, 43);
               this->VertInfoBox->TabIndex = 0;
               this->VertInfoBox->Text = L"������� ������ ����������� ��������\n(A-Z) ��� ���������� ��� �������� �������.";
               //
               // DeleteVertTBox
               //
               this->DeleteVertTBox->Location = System::Drawing::Point(123, 92);
               this->DeleteVertTBox->MaxLength = 1;
               this->DeleteVertTBox->Name = L"DeleteVertTBox";
               this->DeleteVertTBox->Size = System::Drawing::Size(67, 20);
               this->DeleteVertTBox->TabIndex = 20;
               this->DeleteVertTBox->TextChanged += gcnew System::EventHandler(this, &MyForm::DeleteVertTBox_TextChanged);
               //
               // DeleteVert
               //
               this->DeleteVert->Enabled = false;
               this->DeleteVert->Location = System::Drawing::Point(16, 91);
               this->DeleteVert->Name = L"DeleteVert";
               this->DeleteVert->Size = System::Drawing::Size(100, 23);
               this->DeleteVert->TabIndex = 19;
               this->DeleteVert->Text = L"������� �������";
               this->DeleteVert->UseVisualStyleBackColor = true;
               this->DeleteVert->Click += gcnew System::EventHandler(this, &MyForm::DeleteVert_Click);
               //
               // AddVertTBox
               //
               this->AddVertTBox->Location = System::Drawing::Point(123, 63);
               this->AddVertTBox->MaxLength = 1;
               this->AddVertTBox->Name = L"AddVertTBox";
               this->AddVertTBox->Size = System::Drawing::Size(67, 20);
               this->AddVertTBox->TabIndex = 17;
               this->AddVertTBox->TextChanged += gcnew System::EventHandler(this, &MyForm::AddVertTBox_TextChanged);
               //
               // AddVert
               //
               this->AddVert->Enabled = false;
               this->AddVert->Location = System::Drawing::Point(16, 62);
               this->AddVert->Name = L"AddVert";
               this->AddVert->Size = System::Drawing::Size(100, 23);
               this->AddVert->TabIndex = 0;
               this->AddVert->Text = L"�������� �������";
               this->AddVert->UseVisualStyleBackColor = true;
               this->AddVert->Click += gcnew System::EventHandler(this, &MyForm::AddVert_Click);
               //
               // FindRoute
               //
               this->FindRoute->Enabled = false;
               this->FindRoute->Location = System::Drawing::Point(408, 297);
               this->FindRoute->Name = L"FindRoute";
               this->FindRoute->Size = System::Drawing::Size(150, 46);
               this->FindRoute->TabIndex = 19;
               this->FindRoute->Text = L"����� ���������� �������";
               this->FindRoute->UseVisualStyleBackColor = true;
               this->FindRoute->Click += gcnew System::EventHandler(this, &MyForm::FindRoute_Click);
               //
               // ClearGraphButton
               //
               this->ClearGraphButton->Location = System::Drawing::Point(408, 350);
               this->ClearGraphButton->Name = L"ClearGraphButton";
               this->ClearGraphButton->Size = System::Drawing::Size(150, 46);
               this->ClearGraphButton->TabIndex = 20;
               this->ClearGraphButton->Text = L"�������� ����";
               this->ClearGraphButton->UseVisualStyleBackColor = true;
               this->ClearGraphButton->Click += gcnew System::EventHandler(this, &MyForm::ClearGraphButton_Click);
               //
               // MyForm
               //
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
               this->AutoSize = true;
               this->ClientSize = System::Drawing::Size(684, 426);
               this->Controls->Add(this->ClearGraphButton);
               this->Controls->Add(this->FindRoute);
               this->Controls->Add(this->VertBox);
               this->Controls->Add(this->EdgeBox);
               this->Controls->Add(this->pictureBox1);
               this->Controls->Add(this->groupBoxOpen);
               this->StartPosition = FormStartPosition::CenterScreen; // Center the form
               this->ForeColor = System::Drawing::SystemColors::ControlText;
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
               this->MaximizeBox = false;
               this->Name = L"MyForm";
               this->Text = L"����� ����������� �������� � ������������ �����";
               this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
               this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
               this->groupBoxOpen->ResumeLayout(false);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
               this->EdgeBox->ResumeLayout(false);
               this->VertBox->ResumeLayout(false);
               this->VertBox->PerformLayout();
               this->ResumeLayout(false);

           }
#pragma endregion

    private: System::Void OpenButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // ������ ��������� OpenFileDialog
        OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
        openFileDialog->Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
        openFileDialog->Title = "������� ���� � ������";

        // ���������� ������ �������� �����
        if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            // �������� ��������� ������������� ���� � �����
            String^ filePath = openFileDialog->FileName;

            // ���������, ��� ���� ����� ���������� .txt
            if (!filePath->EndsWith(".txt", StringComparison::OrdinalIgnoreCase))
            {
                MessageBox::Show("����������, �������� ���� � ����������� .txt", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try
            {
                // ������ ��� ���������� ����� � ���� ������
                String^ fileContent = System::IO::File::ReadAllText(filePath);

                // �������� ������� �����
                if (!IsValidGraphFileFormat(fileContent))
                {
                    MessageBox::Show("���� ����� �������� ������.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                // ������� ������� ����
                graph->Clear();

                // ��������� ���������� ����� �� ������
                cli::array<String^>^ lines = fileContent->Split(Environment::NewLine->ToCharArray());

                // ���������� ��� �������� �������� ����
                Char currentNode = '\0';

                // ������������ ������ ������
                for each (String ^ line in lines)
                {
                    // ���������� ������ ������
                    if (String::IsNullOrWhiteSpace(line))
                    {
                        continue;
                    }

                    // ����������, �������� �� ������ �����
                    if (line->StartsWith("����:"))
                    {
                        // ��������� ��� ����
                        currentNode = line->Split(':')[1]->Trim()[0];

                        // ���� ���� ��� �� ���������� � �����, ��������� ���
                        if (!graph->ContainsKey(currentNode))
                        {
                            graph[currentNode] = gcnew List<Tuple<Char, float>^>();
                        }
                    }
                    // ����������, �������� �� ������ ������
                    else if (line->Trim()->StartsWith("->"))
                    {
                        // ��������� ���������� � �����
                        cli::array<String^>^ parts = line->Trim()->Split(',');
                        if (parts->Length == 2)
                        {
                            cli::array<String^>^ nodePart = parts[0]->Trim()->Split(':');
                            cli::array<String^>^ weightPart = parts[1]->Trim()->Split(':');

                            if (nodePart->Length == 2 && weightPart->Length == 2)
                            {
                                Char toNode = nodePart[1]->Trim()[0];
                                float weight;

                                // ������� ������������� ��� � float
                                if (Single::TryParse(weightPart[1]->Trim(), weight))
                                {
                                    // ��������� ����� � ����
                                    graph[currentNode]->Add(gcnew Tuple<Char, float>(toNode, weight));

                                    // ���������, ���������� �� �������� �����, � ��������� ���, ���� ���
                                    if (!graph->ContainsKey(toNode))
                                    {
                                        graph[toNode] = gcnew List<Tuple<Char, float>^>();
                                    }
                                    bool reverseEdgeExists = false;
                                    for each (Tuple<Char, float> ^ edge in graph[toNode])
                                    {
                                        if (edge->Item1 == currentNode && edge->Item2 == weight)
                                        {
                                            reverseEdgeExists = true;
                                            UpdateButtonsState();
                                            break;
                                        }
                                    }
                                    if (!reverseEdgeExists)
                                    {
                                        graph[toNode]->Add(gcnew Tuple<Char, float>(currentNode, weight));
                                    }
                                }
                                else
                                {
                                    MessageBox::Show("������ ��� ������ ���� ����� �� �����.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
                                }
                            }
                            else
                            {
                                MessageBox::Show("������ ������� ������ ����� � �����.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
                            }
                        }
                        else
                        {
                            MessageBox::Show("������ ������� ������ ����� � �����.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        }
                    }
                }

                // ���������� ��������� � ���������� ��������
                MessageBox::Show("���� ������� �������� �� ����� " + filePath, "�������� ���������", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (Exception^ ex)
            {
                // ��������� ������ ������ �����
                MessageBox::Show("������ ��� ������ �����: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

private: bool IsValidGraphFileFormat(String^ fileContent)
{
    // ��������� ���������� ����� �� ������
    cli::array<String^>^ lines = fileContent->Split(Environment::NewLine->ToCharArray());

    // ���������� ��� �������� �������� ����
    Char currentNode = '\0';

    // ������������ ������ ������
    for each (String ^ line in lines)
    {
        // ���������� ������ ������
        if (String::IsNullOrWhiteSpace(line))
        {
            continue;
        }

        // ����������, �������� �� ������ �����
        if (line->StartsWith("����:"))
        {
            // ��������� ��� ����
            currentNode = line->Split(':')[1]->Trim()[0];
        }
        // ����������, �������� �� ������ ������
        else if (line->Trim()->StartsWith("->"))
        {
            // ��������� ���������� � �����
            cli::array<String^>^ parts = line->Trim()->Split(',');
            if (parts->Length == 2)
            {
                cli::array<String^>^ nodePart = parts[0]->Trim()->Split(':');
                cli::array<String^>^ weightPart = parts[1]->Trim()->Split(':');

                if (nodePart->Length == 2 && weightPart->Length == 2)
                {
                    Char toNode = nodePart[1]->Trim()[0];
                    float weight;

                    // ������� ������������� ��� � float
                    if (!Single::TryParse(weightPart[1]->Trim(), weight))
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

    private: System::Void InfoButton_Click(System::Object^ sender, System::EventArgs^ e) {
        MessageBox::Show(this, "�������� ���� � ����������� 'txt' � ���������� UTF-8. \n���������� � ����� ������ ����������� � ��������� ����: \n����: a \n  ->����: d, ��� : 3 \n  ->���� : f, ��� : 76 \n ���� : d \n  ->���� : a, ��� : 3 \n  ->���� : f, ��� : 5", "���������", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
    }

    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

    }

    private: System::Void AddVertTBox_TextChanged(System::Object^ sender, System::EventArgs^ e)
    {
        // ��������, �������� �� ��������� ������ ���������� ������
        if (AddVertTBox->Text->Length == 1 && IsEnglishLetter(AddVertTBox->Text[0]))
        {// ��������� ������, ���� ������ ���� ���������� ������
            AddVert->Enabled = true;
        }
        else
        {    // ����������� ������, ���� ���� �� ������������� ��������
            AddVert->Enabled = false;
        }

        // �������� ����� �����
        if (AddVertTBox->Text->Length > 1)
        {    // �������� ������ ��������
            AddVertTBox->Text = AddVertTBox->Text->Substring(0, 1);
            // ��������� ������� � ����� ������
            AddVertTBox->SelectionStart = AddVertTBox->Text->Length;
        }
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

    private: System::Void AddVert_Click(System::Object^ sender, System::EventArgs^ e) {
        // ��������� ���������� �������
        if (AddVertTBox->Text->Length == 1)
        {
            Char node = AddVertTBox->Text[0];

            // ��������, ���������� �� ��� ����� �������
            if (!graph->ContainsKey(node))
            {
                // ���������� ����� ������� � ����
                graph[node] = gcnew List<Tuple<Char, float>^>();
                MessageBox::Show("������� '" + node + "' ������� ���������.");
                // ���������� ��������� ������
                UpdateButtonsState();
            }
            else
            {
                MessageBox::Show("������� '" + node + "' ��� ���������� � �����.");
            }

            // ������� TextBox ����� ���������� �������
            AddVertTBox->Text = "";
            AddVert->Enabled = false;
        }
        else
        {
            MessageBox::Show("����������, ������� ���� ���������� �����.");
        }
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

    private: System::Void FindRoute_Click(System::Object^ sender, System::EventArgs^ e) {
        // �������� � ����������� ����� ��� �������������� �����
        AddEdgeForm^ addEdgeForm = gcnew AddEdgeForm(graph);
        addEdgeForm->SetEditMode("Find");
        addEdgeForm->ShowDialog();
    }

    private: System::Void DeleteVertTBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        // ��������, �������� �� ��������� ������ ���������� ������
        if (DeleteVertTBox->Text->Length == 1 && IsEnglishLetter(DeleteVertTBox->Text[0]))
        {// ��������� ������, ���� ������ ���� ���������� ������
            DeleteVert->Enabled = true;
        }
        else
        {    // ����������� ������, ���� ���� �� ������������� ��������
            DeleteVert->Enabled = false;
        }

        // �������� ����� �����
        if (DeleteVertTBox->Text->Length > 1)
        {    // �������� ������ ��������
            DeleteVertTBox->Text = DeleteVertTBox->Text->Substring(0, 1);
            // ��������� ������� � ����� ������
            DeleteVertTBox->SelectionStart = DeleteVertTBox->Text->Length;
        }
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

    private: System::Void DeleteVert_Click(System::Object^ sender, System::EventArgs^ e) {
        // ��������� ���������� �������
        if (DeleteVertTBox->Text->Length == 1)
        {
            Char node = DeleteVertTBox->Text[0];

            // �������� ������� �� �����
            // ��������, ���������� �� �������
            if (graph->ContainsKey(node))
            {
                // �������� ������� �����
                if (graph[node]->Count > 0)
                {
                    // �������������� ������������
                    System::Windows::Forms::DialogResult result = MessageBox::Show("� ������� '" + node + "' ���� �����. �� ������������� ������ �� �������?", "������������� ��������", MessageBoxButtons::YesNo);
                    if (result == System::Windows::Forms::DialogResult::Yes)
                    {
                        // �������� �������
                        graph->Remove(node);
                        MessageBox::Show("������� '" + node + "' ������� �������.");
                        // ���������� ��������� ������
                        UpdateButtonsState();
                    }
                }
                else
                {
                    // �������� �������
                    graph->Remove(node);
                    MessageBox::Show("������� '" + node + "' ������� �������.");
                }
            }
            else
            {
                MessageBox::Show("������� '" + node + "' �� ������� � �����.");
            }

            // ������� TextBox ����� �������� �������
            DeleteVertTBox->Text = "";
            DeleteVert->Enabled = false;
        }
        else
        {
            MessageBox::Show("����������, ������� ���� ���������� �����.");
        }
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

    private: System::Void AddEdge_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // �������� � ����������� ����� ��� ���������� �����
        AddEdgeForm^ addEdgeForm = gcnew AddEdgeForm(graph);
        addEdgeForm->SetEditMode("Add");
        addEdgeForm->ShowDialog();
        UpdateButtonsState();
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

    private: System::Void EditEdge_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // �������� � ����������� ����� ��� �������������� �����
        AddEdgeForm^ addEdgeForm = gcnew AddEdgeForm(graph);
        addEdgeForm->SetEditMode("Edit");
        addEdgeForm->ShowDialog();
        UpdateButtonsState();
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

    private: System::Void DeleteEdge_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // �������� � ����������� ����� ��� �������� �����
        AddEdgeForm^ addEdgeForm = gcnew AddEdgeForm(graph);
        addEdgeForm->SetEditMode("Delete");
        addEdgeForm->ShowDialog();
        UpdateButtonsState();
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }

    private: System::Void ClearGraphButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // ������������� �������� �����
        System::Windows::Forms::DialogResult result = MessageBox::Show("�� �������, ��� ������ �������� ����?", "������������� ��������", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
        if (result == System::Windows::Forms::DialogResult::Yes)
        {
            // ������� �����
            graph->Clear();
            // ���������� ��������� ������
            UpdateButtonsState();
            // ����� ������� ��� ��������� �����
            DrawGraph(graph, graphics, pictureBox1);
        }
    }


    private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // ������ ��������� SaveFileDialog
        SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
        saveFileDialog->Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
        saveFileDialog->Title = "��������� ���� ���";

        // ���������� ������ ���������� �����
        if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            // �������� ��������� ������������� ���� � �����
            String^ filePath = saveFileDialog->FileName;

            // ������ StreamWriter ��� ������ � ����
            System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(filePath);

            try
            {
                // ���������� ��������� ��� ������������ ���������� ����
                std::unordered_set<std::string> writtenEdges;

                // �������� �� ������� ���� � �����
                for each (KeyValuePair<Char, List<Tuple<Char, float>^>^> node in graph)
                {
                    // ���������� ���� � ����
                    sw->WriteLine("����: " + node.Key);

                    // �������� �� ������� �����, ���������� � �����
                    for each (Tuple<Char, float> ^ edge in node.Value)
                    {
                        // ��������� ������ ��� �����
                        std::string edgeKey = (char)node.Key + std::to_string(edge->Item1);

                        // ���������, �� ���� �� ��� �������� �������� �����
                        if (writtenEdges.find(edgeKey) == writtenEdges.end())
                        {
                            // ���������� ����� � ����
                            sw->WriteLine("  -> ����: " + edge->Item1 + ", ���: " + edge->Item2);

                            // ��������� ����� � ��� �������� � ��������� ���������� ����
                            writtenEdges.insert(edgeKey);
                            writtenEdges.insert(std::to_string(edge->Item1) + (char)node.Key);
                        }
                    }
                }

                // ���������� ��������� � ���������� ����������
                MessageBox::Show("���� ������� �������� � ���� " + filePath, "���������� ���������", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            finally
            {
                // ��������, ��� StreamWriter ������
                if (sw)
                {
                    sw->Close();
                }
            }
        }
        // ����� ������� ��� ��������� �����
        DrawGraph(graph, graphics, pictureBox1);
    }


    private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
    {
        // ����������� ��������� ���� ��� �������� ���������
        if (graph->Count > 0)
        {
            System::Windows::Forms::DialogResult result = MessageBox::Show("��������� ���� ����� ���������?", "���������� �����", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
            if (result == System::Windows::Forms::DialogResult::Yes)
            {
                SaveButton_Click(sender, e);
            }
            else if (result == System::Windows::Forms::DialogResult::Cancel)
            {
                e->Cancel = true;
            }
        }
    }
    };
}
