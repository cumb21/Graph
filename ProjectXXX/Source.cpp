#include "Header.h" 



// ������� ��� ��������� ����������� �����
void DrawGraph(Dictionary<Char, List<Tuple<Char, float>^>^>^ graph, Graphics^ graphics, PictureBox^ pictureBox)
{
    // ������� ������� ���������
    graphics->Clear(Color::White);

    // ���������� �����
    int nodeCount = graph->Count;

    // ������ ������� ����������, �� ������� ����� ������������� ����
    float radius = Math::Min(pictureBox->Width, pictureBox->Height) / 2.5f;

    // ����� PictureBox
    float centerX = pictureBox->Width / 2.0f;
    float centerY = pictureBox->Height / 2.0f;

    // �������� ������ ����� ��� ����������� �������
    List<Char>^ nodes = gcnew List<Char>();
    for each (KeyValuePair<Char, List<Tuple<Char, float>^>^> nodePair in graph)
    {
        nodes->Add(nodePair.Key);
    }

    // ��������� ����� � �����
    for (int i = 0; i < nodes->Count; ++i)
    {
        Char node = nodes[i];
        List<Tuple<Char, float>^>^ neighbors = graph[node];

        // ���������� ��������� �������� ����
        float angle = 2 * 3.14159f * i / nodeCount;
        float nodeX = centerX + radius * cos(angle);
        float nodeY = centerY + radius * sin(angle);

        // ��������� ����
        graphics->FillEllipse(Brushes::Blue, nodeX - 10.0f, nodeY - 10.0f, 20.0f, 20.0f);
        graphics->DrawString(node.ToString(), gcnew Font(L"Arial", 10), Brushes::White, nodeX - 5.0f, nodeY - 10.0f);

        // ��������� ����� � ������
        for each (Tuple<Char, float> ^ neighbor in neighbors)
        {
            Char neighborNode = neighbor->Item1;
            float weight = neighbor->Item2;

            // ����� ������� ��������� ����
            int neighborIndex = nodes->IndexOf(neighborNode);

            // ���������� ��������� ��������� ����
            float neighborAngle = 2 * 3.14159f * neighborIndex / nodeCount;
            float neighborX = centerX + radius * cos(neighborAngle);
            float neighborY = centerY + radius * sin(neighborAngle);

            // ��������� �����
            graphics->DrawLine(Pens::Black, nodeX, nodeY, neighborX, neighborY);

            // ���������� ��������� ��� ����������� ����
            float labelX = (nodeX + neighborX) / 2.0f;
            float labelY = (nodeY + neighborY) / 2.0f;

            // ��������� ���� �� �����
            graphics->DrawString(weight.ToString(), gcnew Font(L"Arial", 8), Brushes::Red, labelX, labelY);
        }
    }
}



// ������� ��� ������ ����������� ���� � �������������� ��������� ��������
void FindShortestPath(Dictionary<Char, List<Tuple<Char, float>^>^>^ graph, Char startNode, Char endNode, List<Char>^% path, float% totalDistance)
{
    // ������������� �������� ������
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

    // �������������� ����
    path = gcnew List<Char>();
    for (Char at = endNode; at != '\0'; at = previousNodes[at])
    {
        path->Insert(0, at);
    }

    totalDistance = distances[endNode];
}


// ����� ��� ��������, �������� �� ������ ���������� ������
bool IsEnglishLetter(wchar_t ch)
{
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

