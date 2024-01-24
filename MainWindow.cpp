#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUdpSocket>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Initialize the UDP socket
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(12345); // Set the appropriate port number

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startReceiving);
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::processPendingDatagrams);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startReceiving() {
    ui->packetDisplayTextEdit->clear();
    packets.clear(); // Clear previous packets if any

    // Start listening for incoming packets
    // Note: This example assumes that each packet is a separate line of text
    // You may need to modify this based on your packet format
    udpSocket->open(QIODevice::ReadOnly);
}

void MainWindow::processPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        // Process the received packet
        processPacket(datagram);
    }
}

void MainWindow::processPacket(const QByteArray &packet) {
    static int serialNumber = 1;

    // Add serial number to the packet
    QString packetWithSerial = QString("Serial %1: %2").arg(serialNumber).arg(QString(packet));

    // Display the packet in the QTextEdit
    ui->packetDisplayTextEdit->append(packetWithSerial);

    // Store the packet in the list
    packets.append(packetWithSerial);

    // Increment the serial number
    serialNumber++;
}

void MainWindow::on_retrieveButton_clicked() {
    // Retrieve the packet based on the entered serial number
    int serial = ui->serialNumberLineEdit->text().toInt();
    if (serial > 0 && serial <= packets.size()) {
        QString retrievedPacket = packets.at(serial - 1);
        ui->packetDisplayTextEdit->setText(retrievedPacket);
    } else {
        ui->packetDisplayTextEdit->setText("Packet not found for the given serial number.");
    }
}

