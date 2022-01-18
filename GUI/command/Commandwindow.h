#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QSlider>
#include <QTcpSocket>
#include <QJsonDocument>

#include "Comm/Controlmessage.h"
#include "Comm/Accumulator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CommandWindow; }
QT_END_NAMESPACE

class CommandWindow : public QMainWindow, MessageInterpretor
{
    Q_OBJECT
public:
    CommandWindow(QWidget *parent = nullptr);
    ~CommandWindow();
    void sendJSon(QJsonDocument doc);
    void sendControlMessage(ControlMessage* msg);
    void sendControlMessage(ControlMessagefloatingPoint* msg);

    bool messageReceved(char* rawDataFrame,unsigned int lenght);
    bool sendCartesianPosition(QStringList command);
    bool sendJointPosition(QStringList command);

public slots:
    void sendJointParameters();
    void setHome();
    void goHome();
    void connectSocket();
    void readData();
    void loadFile();
    void saveFile();
    void runFile();
    void openFile();
    void saveFileAs();
    void zeroIn();
    void commandMoveHere();
    void commandGoHome();
    void commandSetHomeHere();
    void commandOpenGripper();
    void commandCloseGripper();
    void hideJoint();
    void hideCartesian();
    void openGripper();
    void closeGripper();
private:
    Ui::CommandWindow *ui;
    QTcpSocket* socket;
    Accumulator* acc;
    float home_joint[4] = {0, 0, 0, 0};
    float home_cart[3] = {0, 0, 0};
};
#endif // COMMANDWINDOW_H
