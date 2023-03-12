#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QWidget>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QList>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QPushButton>
#include <QSpinBox>

#include <QTime>


namespace Ui {
class ServerDialog;
}

class ServerDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = 0);
    ~ServerDialog();

public slots:
    void onStartButtonClick();
    void onStopButtonClick();
    void onSendButtonClick();
    void onCleanButtonClick();
Q_SIGNALS:
    void closed();
private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void socketDisconnected();
    //void processBinaryMessage(QByteArray message);

private:
    QSpinBox* m_monitorSpinBox;
    QPushButton* m_startButton;
    QPushButton* m_stopButton;
    QTextEdit* m_sendTextedit;
    QPushButton* m_sendButton;
    QListWidget* m_linkclientListWidget;
    QPushButton* m_cleanButton;
    QTextEdit* m_receiveTextEdit;

    QWebSocketServer * m_WebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
    QWebSocket *pSocket;
    QDateTime *current_date_time;


private:
    Ui::ServerDialog *ui;
};




#endif // SERVERDIALOG_H
