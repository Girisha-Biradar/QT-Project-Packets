#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startReceiving();
    void processPendingDatagrams();
    void processPacket(const QByteArray &packet);
    void on_retrieveButton_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QList<QString> packets;
};

#endif // MAINWINDOW_H
