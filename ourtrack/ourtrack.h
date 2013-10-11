#ifndef OURTRACK_H
#define OURTRACK_H

#include "ui_ourtrack.h"
#include "proxyserver.h"
#include <QVector>

//-------------------------------------------------------------------

// ������� ��������� ������
#define COL_COUNT   7
#define COL_HEADER  "Category" << "Name" << "Date" << "Size" << "SE" << "LE" << "Magnet"

// �����������, ���������� ������ ����� ������ (��� ���������� - ����������������)
//#define PROXY_SERVER

//-------------------------------------------------------------------

// ������� ��������� ������
struct MainListItem
{
  QString Data[COL_COUNT];
};

//-------------------------------------------------------------------

class ourtrack : public QMainWindow
{
  Q_OBJECT

public:
  ourtrack(QWidget *parent = 0);
  ~ourtrack();

public slots:
  void SendFindQuery();
  void slotReadServer();
  void ShowList();

private:  

  // ������������ � �������������� ��������� ������ ( ������������� ������� items � ���� char )
  QByteArray  Serialize();
  void        DeSerialize(QByteArray &buffer);

  // ���������������� ���������
  Ui::ourtrackClass     ui;

  // ������ ��������� ��������� ������
  QVector<MainListItem> items;

  // ������ � �����
  QTcpSocket            *socket;
  ProxyServer           *proxy_srv;
};

//-------------------------------------------------------------------

#endif // OURTRACK_H
