#include "ourtrack.h"

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