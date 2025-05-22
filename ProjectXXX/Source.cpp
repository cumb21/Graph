#include "Header.h" 



// Функция для рисования взвешенного графа
void DrawGraph(Dictionary<Char, List<Tuple<Char, float>^>^>^ graph, Graphics^ graphics, PictureBox^ pictureBox)
{
    // Очистка области рисования
    graphics->Clear(Color::White);

    // Количество узлов
    int nodeCount = graph->Count;

    // Расчет радиуса окружности, на которой будут располагаться узлы
    float radius = Math::Min(pictureBox->Width, pictureBox->Height) / 2.5f;

    // Центр PictureBox
    float centerX = pictureBox->Width / 2.0f;
    float centerY = pictureBox->Height / 2.0f;

    // Создание списка узлов для определения порядка
    List<Char>^ nodes = gcnew List<Char>();
    for each (KeyValuePair<Char, List<Tuple<Char, float>^>^> nodePair in graph)
    {
        nodes->Add(nodePair.Key);
    }

    // Рисование узлов и ребер
    for (int i = 0; i < nodes->Count; ++i)
    {
        Char node = nodes[i];
        List<Tuple<Char, float>^>^ neighbors = graph[node];

        // Вычисление координат текущего узла
        float angle = 2 * 3.14159f * i / nodeCount;
        float nodeX = centerX + radius * cos(angle);
        float nodeY = centerY + radius * sin(angle);

        // Рисование узла
        graphics->FillEllipse(Brushes::Blue, nodeX - 10.0f, nodeY - 10.0f, 20.0f, 20.0f);
        graphics->DrawString(node.ToString(), gcnew Font(L"Arial", 10), Brushes::White, nodeX - 5.0f, nodeY - 10.0f);

        // Рисование ребер с весами
        for each (Tuple<Char, float> ^ neighbor in neighbors)
        {
            Char neighborNode = neighbor->Item1;
            float weight = neighbor->Item2;

            // Поиск индекса соседнего узла
            int neighborIndex = nodes->IndexOf(neighborNode);

            // Вычисление координат соседнего узла
            float neighborAngle = 2 * 3.14159f * neighborIndex / nodeCount;
            float neighborX = centerX + radius * cos(neighborAngle);
            float neighborY = centerY + radius * sin(neighborAngle);

            // Рисование ребра
            graphics->DrawLine(Pens::Black, nodeX, nodeY, neighborX, neighborY);

            // Вычисление координат для отображения веса
            float labelX = (nodeX + neighborX) / 2.0f;
            float labelY = (nodeY + neighborY) / 2.0f;

            // Рисование веса на ребре
            graphics->DrawString(weight.ToString(), gcnew Font(L"Arial", 8), Brushes::Red, labelX, labelY);
        }
    }
}



// Функция для поиска кратчайшего пути с использованием алгоритма Дейкстры
void FindShortestPath(Dictionary<Char, List<Tuple<Char, float>^>^>^ graph, Char startNode, Char endNode, List<Char>^% path, float% totalDistance)
{
    // Инициализация структур данных
    std::vector<float> distances(256, std::numeric_limits<float>::infinity());
    std::vector<Char> previousNodes(256, '\0');
    std::priority_queue<std::pair<float, Char>, std::vector<std::pair<float, Char>>, std::greater<std::pair<float, Char>>> pq;

    distances[startNode] = 0;
    pq.push(std::make_pair(0, startNode));

    while (!pq.empty())
    {
        Char currentNode = pq.top().second;
        float currentDistance = pq.top().first;
        pq.pop();

        if (currentNode == endNode)
        {
            break;
        }

        if (graph->ContainsKey(currentNode))
        {
            for each (Tuple<Char, float> ^ neighbor in graph[currentNode])
            {
                Char neighborNode = neighbor->Item1;
                float weight = neighbor->Item2;
                float distance = currentDistance + weight;

                if (distance < distances[neighborNode])
                {
                    distances[neighborNode] = distance;
                    previousNodes[neighborNode] = currentNode;
                    pq.push(std::make_pair(distance, neighborNode));
                }
            }
        }
    }

    // Восстановление пути
    path = gcnew List<Char>();
    for (Char at = endNode; at != '\0'; at = previousNodes[at])
    {
        path->Insert(0, at);
    }

    totalDistance = distances[endNode];
}


// Метод для проверки, является ли символ английской буквой
bool IsEnglishLetter(wchar_t ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

