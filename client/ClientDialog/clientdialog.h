#ifndef CLIENTDIALOG_HPP
#define CLIENTDIALOG_HPP
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QButtonGroup>
#include <QObject>
#include <QWidget>
#include <QUrl>
#include <QtWebSockets/QWebSocket>
#include <time.h>
#include <QTimer>
#include <QByteArray>

class ClientDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ClientDialog(const QUrl &url,bool debug = false, QWidget *parent=0);
    ~ClientDialog();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void connectToServer();
    void onTextMessageReceived(const QString &message);
    void closeConnection();

public slots:
    void stopClicked();
    void onconnected();
    void onSendButtonClicked();
    void onCleanButtonClicked();

private:
    QLineEdit *m_iplineedit;
    QSpinBox *m_portspinbox;
    QPushButton *m_linkbutton;
    QPushButton *m_disconnectbutton;
    QTextEdit *m_sendmessagetextedit;
    QPushButton *m_sendbutton;
    QTextEdit *m_receivemessageTextEdit;
    QPushButton *m_clean;
    QLabel *statusLabel;
    QButtonGroup *pButtonGroup;
    QUrl m_url;
    QWebSocket m_websocket;
    bool m_debug;
    QDateTime *current_date_time;
    QTimer    m_sendTimer;
    int       flag {10000};
};
#endif // CLIENTDIALOG_HPP
