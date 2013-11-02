#ifndef OURTRACKSERV_H
#define OURTRACKSERV_H

//-------------------------------------------------------------------

#include <QtNetwork>
#include "databasecontrol.h"

//-------------------------------------------------------------------

class ourtrackserv : public QObject
{
  Q_OBJECT

public:
  ourtrackserv(QObject *parent = 0);
  ~ourtrackserv();

  // ���������� ��������
  void on_starting();
  void on_stoping();

private slots:
  void slotNewUser();     // ���������� ��� ����� ����������
  void slotReadClient();  // ���������� ��� ������ ������ �������

  void FindQueryDissect(QTcpSocket *clientSocket);  // ������ �������� ������
  void AddQueryDissect(QTcpSocket *clientSocket);   // ������ ������� ���������� ������ ��������
  void LikeQueryDissect(QTcpSocket *clientSocket);  // ������ ���������� �����
  void GetLastQueryDissect(QTcpSocket *clientSocket);  // ������ ��������� ������

private:
  inline bool           SocketCheck();
  inline bool           SearchQueryCheck(const QString &query);
  QByteArray            Serialize(const QVector<MainListItem> &items);
  QVector<MainListItem> DeSerialize(const QByteArray &buffer);

  DatabaseControl         db_ctrl;      // ������ ������ � ��
  QTcpServer              *tcpServer;   // ������ ������ ����������
  QMap<int, QTcpSocket*>  SClients;     // ����������� �������

};

//-------------------------------------------------------------------

#endif // OURTRACKSERV_H
