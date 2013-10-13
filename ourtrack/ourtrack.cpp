#include "ourtrack.h"

//-------------------------------------------------------------------

ourtrack::ourtrack(QWidget *parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);    
  QObject::connect(ui.ButtonFind, SIGNAL(clicked()), this, SLOT(SendFindQuery()));

  // ����� ��� ���������� � ��������
  socket = new QTcpSocket(this);
  connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadServer()));
  // �������� ������-������� � ������
#ifdef PROXY_SERVER
  proxy_srv = new ProxyServer(socket);
  proxy_srv->start();
#endif
}

//-------------------------------------------------------------------

ourtrack::~ourtrack()
{
  socket->close();
  delete socket;
#ifdef PROXY_SERVER
  proxy_srv->stop();
  delete proxy_srv;
#endif
}

//-------------------------------------------------------------------

void ourtrack::ShowList()
{
  QTableWidget *table = ui.TableResult;

  if (!table) return;
  if (!items.size())
  {
    table->clear();
    return;
  }

  table->clear();
  table->setColumnCount(COL_COUNT);
  table->setRowCount(items.size());

  QStringList header_lst;
  header_lst << COL_HEADER;
  table->setHorizontalHeaderLabels(header_lst);

  for ( auto i = 0; i < items.size(); i++ )
    for ( auto j = 0; j < COL_COUNT; j++ )
    {
      auto *ListItem = new QTableWidgetItem(items[i].Data[j]);
      table->setItem(i, j, ListItem);
    }
}

//-------------------------------------------------------------------

void ourtrack::SendFindQuery()
{
  // �������� ������ � �����
  QString search_query = ui.EditFind->text();
  QByteArray sbuf(search_query.toStdString().c_str());

  // ����������� � ��������
  socket->connectToHost(SERVER_HOST, SERVER_PORT);
  if (!socket->waitForConnected(TIME_WAIT_FOR_CONNECT))
  {
    socket->close();
    return;
  }  

  // ���������� ��� ��������� ������
  socket->write(sbuf);
  if (!socket->waitForBytesWritten(TIME_WAIT_FOR_WRITTEN))
  {
    socket->close();
    return;
  }
}

//-------------------------------------------------------------------

void ourtrack::slotReadServer()
{
  // �������� ����� ����, ��� ������ �����
  QTcpSocket* socket = (QTcpSocket*)sender();

  // �������� ������ �� ������� � ������������� � ������ ��������� ������
  QByteArray recvbuff;
  recvbuff = socket->readAll();
  DeSerialize(recvbuff);
  
  socket->close();
  ShowList();
}

//-------------------------------------------------------------------
