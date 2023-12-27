#ifndef BLECONNECT_H
#define BLECONNECT_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QList>
#include <QBluetoothDeviceInfo>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QTime>
#include <QDataStream>
#include <QMap>
#include <QTimer>

#include <QDebug>

static const QLatin1String serviceUuid("{0000ff00-c243-40b9-ac41-a10ba3ad5d1a}");

class BLEConnect : public QObject
{
    Q_OBJECT
public:
    explicit BLEConnect(QObject *parent = nullptr);

    bool PermissionApply(QString);
    bool checkPermission();
    void MsgRefresh();
    bool devExistCheck(QString mac);
    Q_INVOKABLE void disconnectDev();
    void ble_dev_tool_discover_service(void);

signals:
    void fromBle(QString msg);
    void sendRquest(QString msg);
    void returnAddress(QBluetoothDeviceInfo);
    void addItems(QString name, QString mac, QString rssi);
    void bleConnected();
    void bleDisconnected();

private:
    bool m_foundHeartRateService;

    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;
    QList<QBluetoothDeviceInfo> m_devices;
    QLowEnergyController  *m_control;
    QLowEnergyService *m_service;

    QLowEnergyCharacteristic m_writeCharacteristic[5]; //写特性
    QLowEnergyService::WriteMode m_writeMode;
    QLowEnergyDescriptor m_notificationDesc;
    QLowEnergyCharacteristic m_readCharacteristic; //读特性
    int SendMaxMode; //发送模式
    int SendModeSelect;//选择发送模式
    bool isconnected;
    QList<QBluetoothUuid> m_uuidList;
    QStringList m_devList;


public slots:
    void addDevice(const QBluetoothDeviceInfo &device);

    void on_blue_connect_clicked(QString address);

    void on_blue_search_clicked(bool checked);
    void on_blue_stop_search_clicked();
    void scanFinished();
    void createCtl(QBluetoothDeviceInfo);

    void serviceDiscovered(const QBluetoothUuid &gatt);
    void serviceScanDone();
    void serviceStateChanged(QLowEnergyService::ServiceState s);

    void searchCharacteristic();
    void BleServiceCharacteristicChanged(const QLowEnergyCharacteristic &c,const QByteArray &value);
    void BleServiceCharacteristicRead(const QLowEnergyCharacteristic &c,
                                      const QByteArray &value);
    void BleServiceCharacteristicWrite(const QLowEnergyCharacteristic &c,
                                                   const QByteArray &value);
    void sendBleMsg(QString text);
    void ble_dev_tool_device_connected_slot();
    void ble_dev_tool_update_notify_get_details(void);
    void ble_dev_tool_discover_service_details(void);
    void ble_dev_tool_service_state_changed_slot(QLowEnergyService::ServiceState state);
    void ble_dev_tool_service_characteristic_changed_slot(QLowEnergyCharacteristic characteristic, QByteArray value);
    void bleServiceErrorOccurredSlot(QLowEnergyService::ServiceError error);
    void onServiceStateChanged(QLowEnergyService::ServiceState s);
};

#endif // BLECONNECT_H
