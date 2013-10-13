#include "ourtrackserv.h"

//-------------------------------------------------------------------

QByteArray ourtrackserv::Serialize(QVector<MainListItem> &items)
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