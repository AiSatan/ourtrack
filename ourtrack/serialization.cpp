#include "ourtrack.h"

//-------------------------------------------------------------------

QByteArray ourtrack::Serialize()
{
  // �������������� ������
  QByteArray buffer;
  QDataStream out(&buffer, QIODevice::WriteOnly);

  QMap<quint16, QVariant> m;  // ����� ��� ������ ��������� ������ ��� ����������� ������������
  int counter = 0;            // ���������� ������� � ����� (������������ ��� ����)

  // ��������� ���������� ��������� (����������� ��� ��������������)
  m.insert(counter++, items.size());

  // ��������� ��� ��������
  for (auto it = items.begin(); it != items.end(); ++it)
    for (int j = 0; j < COL_COUNT; j++)
      m.insert(counter++, it->Data[j]);

  out << m;
  return buffer;
}

//-------------------------------------------------------------------

void ourtrack::DeSerialize(QByteArray &buffer)
{
  // ������� ������������ ������ ��������� ��������� ������
  items.clear();

  QDataStream in(&buffer, QIODevice::ReadOnly);

  QMap<quint16, QVariant> m;  // ����� ��� ������ ��������� ������
  int counter = 0;            // ���������� ������� � ����� (������������ ��� ����)

  // ��������� �����
  in >> m;

  // �������� ���������� ���������
  int count = m.value(counter++).toInt();

  // ��������� ��� ��������
  for (int i = 0; i < count; i++)
  {
    MainListItem item;
    for (int j = 0; j < COL_COUNT; j++)
    {
      item.Data[j] = m.value(counter++).toString();
    }
    items.push_back(item);
  }
}

//-------------------------------------------------------------------