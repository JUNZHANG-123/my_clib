#include "bleconnect.h"

BLEConnect::BLEConnect(QObject *parent) : QObject(parent)
{
    SendModeSelect=0;   //默认发送模式
    MsgRefresh();
    m_foundHeartRateService=false;
    isconnected=false;

    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(20000);
    connect(m_deviceDiscoveryAgent,SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this,
            SLOT(addDevice(QBluetoothDeviceInfo)));//
    connect(m_deviceDiscoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));
    connect(this, SIGNAL(returnAddress(QBluetoothDeviceInfo)), this, SLOT(createCtl(QBluetoothDeviceInfo)));
}

bool BLEConnect::checkPermission()
{
//    QtAndroid::PermissionResult r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
//    if(r == QtAndroid::PermissionResult::Denied)
//    {
//        QtAndroid::requestPermissionsSync( QStringList() << "android.permission.WRITE_EXTERNAL_STORAGE" );
//        r = QtAndroid::checkPermission("android.permission.WRITE_EXTERNAL_STORAGE");
//        if(r == QtAndroid::PermissionResult::Denied)
//        {
//            return false;
//        }
//    }
    return true;
}

void BLEConnect::MsgRefresh()
{
//    if(!checkPermission())
//    {
//        //        ui->bluemsg->append("安卓写权限获取失败");
//        emit fromBle("安卓写权限获取失败");
//    }
//    else
//    {
//        //        ui->bluemsg->append("安卓写权限获取成功");
//        emit fromBle("安卓写权限获取成功");
//    }

//    QAndroidJniEnvironment env;
//    //    ui->bluemsg->append(QString("SDK版本:%1").arg(QtAndroid::androidSdkVersion()));
    //    emit fromBle(QString("SDK版本:%1").arg(QtAndroid::androidSdkVersion()));
}

bool BLEConnect::PermissionApply(QString str)
{
//    QtAndroid::PermissionResult r = QtAndroid::checkPermission(str);

//    if(r == QtAndroid::PermissionResult::Denied)
//    {
//        QtAndroid::requestPermissionsSync(QStringList() << str);

//        r=QtAndroid::checkPermission(str);
//        if(r == QtAndroid::PermissionResult::Denied)
//        {
//            //            ui->bluemsg->append("权限申请失败");
//            emit fromBle("权限申请失败");
//            return false;
//        }
//    }
//    //    ui->bluemsg->append("权限申请成功");
//    emit fromBle("权限申请成功");
    return true;
}

bool BLEConnect::devExistCheck(QString mac)
{
    foreach(QString devMac, m_devList)
    {
        if (devMac == mac)
        {
            return true;
        }
    }
    return false;
}

void BLEConnect::disconnectDev()
{
    m_control->disconnectFromDevice();
}

void BLEConnect::addDevice(const QBluetoothDeviceInfo &info)
{
    qDebug() << __FUNCTION__ << info.coreConfigurations() << info.name()
             <<( info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) ;
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration)
    {//判断是否是BLE设备
        QString devMac = info.address().toString();
        QString devName = info.name();
        QString devRssi = QString::number(info.rssi(), 10);

        qDebug() << __FUNCTION__ << devName << devMac << devRssi;

        if (!devExistCheck(devMac) )
        {//不存在则添加至设备列表
            m_devList.append(devMac);
            emit addItems(devName, devMac, devRssi);
            m_devices.append(info);
        }
    }
}

void BLEConnect::on_blue_connect_clicked(QString mac)
{
    m_deviceDiscoveryAgent->stop();//停止搜索服务
    for (int i = 0; i<m_devices.count(); i++)
    {
        if(m_devices.at(i).address().toString() == mac)//地址对比
        {
            QBluetoothDeviceInfo choosenDevice = m_devices.at(i);
            emit returnAddress(choosenDevice);//发送设备信息
            break;
        }
    }
}

void BLEConnect::on_blue_stop_search_clicked()
{
    m_deviceDiscoveryAgent->stop();
}

void BLEConnect::on_blue_search_clicked(bool checked)
{
    m_deviceDiscoveryAgent->stop();
    m_devList.clear();
    m_deviceDiscoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BLEConnect::scanFinished()
{
    qDebug() << __FUNCTION__;
}

void BLEConnect::createCtl(QBluetoothDeviceInfo info)
{
    m_control = QLowEnergyController::createCentral(info, this);
    connect(m_control, &QLowEnergyController::serviceDiscovered,
            this,&BLEConnect::serviceDiscovered);

    connect(m_control, &QLowEnergyController::discoveryFinished,
            this, &BLEConnect::serviceScanDone);

    connect(m_control, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
            this, [this](QLowEnergyController::Error error) {
        Q_UNUSED(error);

        qDebug() << __FUNCTION__ << __LINE__ << error;
//        ui->bluemsg->append("Cannot connect to remote device.");
        emit fromBle("Cannot connect to remote device.");
    });

//    connect(m_control, &QLowEnergyController::connected, this, [this]() {
//        ui->bluemsg->append("Controller connected. Search services...\n");
//        emit fromBle("Controller connected. Search services...");
//        emit bleConnected();
//        m_control->discoverServices();
//        isconnected=true;
//        qDebug() << __FUNCTION__ << __LINE__ << "connected";
//    });

    connect(m_control, &QLowEnergyController::connected, this, &BLEConnect::ble_dev_tool_device_connected_slot);

    connect(m_control, &QLowEnergyController::disconnected, this, [this]() {
//        ui->bluemsg->append("LowEnergy controller disconnected");
        emit fromBle("LowEnergy controller disconnected");
        isconnected = false;
        emit bleDisconnected();
        qDebug() << __FUNCTION__ << __LINE__ << "disconnected";
    });

    //connect
//    ui->bluemsg->append("start to connect\n");

    qDebug() << __FUNCTION__ << __LINE__;
    emit fromBle("start to connect");

    m_uuidList.clear();
    m_control->connectToDevice();
}


void BLEConnect::ble_dev_tool_device_connected_slot()
{
    isconnected=true;
    QTimer::singleShot(500, this, [this](){
            ble_dev_tool_discover_service();
        });
}

void BLEConnect::ble_dev_tool_discover_service(void)
{
    m_control->discoverServices();
}


void BLEConnect::serviceDiscovered(const QBluetoothUuid &gatt)
{
//    ui->bluemsg->insertPlainText(QString("%1").arg(gatt.toString()));
    emit fromBle(QString("%1").arg(gatt.toString()));
//    m_foundHeartRateService = true;

    qDebug() << __FUNCTION__ << __LINE__ << gatt.toString();

    //将搜索到的服务的Uuid存到一个label中
    QString label = QString("%1").arg(gatt.toString());

    m_uuidList.append(gatt); //设备信息添加到自己的列表中

//    if (label == BLE_FILTER_SERVICE)
//    {
//        service_find_flag = true;


//        ble_dev_tool_serv_index = m_uuidList.count();
//    }

}

void BLEConnect::serviceScanDone()
{

    QTimer::singleShot(1000, this, [this](){
                ble_dev_tool_update_notify_get_details();
            });
}

void BLEConnect::bleServiceErrorOccurredSlot(QLowEnergyService::ServiceError error) //低功耗蓝牙服务产生错误
{
    if(QLowEnergyService::NoError == error)
    {
        qDebug() <<"没有发生错误。";
    }
    if(QLowEnergyService::OperationError== error)
    {
        qDebug() << "错误" << "当服务没有准备好时尝试进行操作!";
    }
    if(QLowEnergyService::CharacteristicReadError== error)
    {
        qDebug() << "错误" << "尝试读取特征值失败!";
    }
    if(QLowEnergyService::CharacteristicWriteError== error)
    {
        qDebug() << "错误" << "尝试为特性写入新值失败!";
    }
    if(QLowEnergyService::DescriptorReadError== error)
    {
        qDebug() << "错误" << "尝试读取描述符值失败!";
    }
    if(QLowEnergyService::DescriptorWriteError== error)
    {
        qDebug() << "错误" <<  "尝试向描述符写入新值失败!";
    }
    if(QLowEnergyService::UnknownError== error)
    {
        qDebug() << "错误" <<  "与服务交互时发生未知错误!";
    }

    if (QLowEnergyService::DescriptorReadError== error)
    {
        qDebug() << "错误" <<  "尝试读取描述符值失败!";
    }
    if(QLowEnergyService::DescriptorWriteError== error)
    {
        qDebug() << "错误" <<  "尝试向描述符写入新值失败!";
    }
    if(QLowEnergyService::UnknownError== error)
    {
        qDebug() << "错误" <<  "与服务交互时发生未知错误!";
    }
}


void BLEConnect::ble_dev_tool_update_notify_get_details(void)
{
    QBluetoothUuid serviceUuid = m_uuidList.at(0); //当前选中的服务的Uuid

    //创建服务
    m_service = m_control->createServiceObject(QBluetoothUuid(serviceUuid), this);

    //判断创建服务是否出现错误
    if(m_service == NULL)
    {
        //QMessageBox::warning(this, "警告", "创建服务失败!");
        qDebug() << __FUNCTION__ << __LINE__ << "警告,创建服务失败!";
    }
    else //创建服务成功;创建服务就相当于连接上了,执行完ServiceStateChangedSlot之后就可以正常通信了
    {
        //ui->te_ble_log->append("开始获取服务细节并使能notify");

        //监听服务状态变化
        connect(m_service, &QLowEnergyService::stateChanged, this, &BLEConnect::ble_dev_tool_service_state_changed_slot);
        //服务的characteristic变化,有数据传来
        connect(m_service, &QLowEnergyService::characteristicChanged, this, &BLEConnect::ble_dev_tool_service_characteristic_changed_slot);
        //错误处理
        void (QLowEnergyService:: *bleServiceErrorOccurred)(QLowEnergyService::ServiceError) = &QLowEnergyService::error;//有重载
        connect(m_service, bleServiceErrorOccurred, this, &BLEConnect::bleServiceErrorOccurredSlot);

        //描述符成功被写
        //connect(m_service, &QLowEnergyService::descriptorWritten, this, &BLEConnect::ble_dev_tool_service_descriptor_written_slot);
        connect(m_service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic,QByteArray)),
                this, SLOT(BleServiceCharacteristicWrite(QLowEnergyCharacteristic,QByteArray)));

        //触发服务详情发现函数
        QTimer::singleShot(1000, this, [this](){
            ble_dev_tool_discover_service_details();
        });
    }
}

void BLEConnect::ble_dev_tool_discover_service_details(void)
{
    qDebug() << __FUNCTION__ << __LINE__;
    m_service->discoverDetails();
}

void BLEConnect::ble_dev_tool_service_state_changed_slot(QLowEnergyService::ServiceState state) //服务状态改变
{
    QLowEnergyCharacteristic m_bleCharacteristic;
    qDebug() << __FUNCTION__ << __LINE__;
    //发现服务
    if(state == QLowEnergyService::ServiceDiscovered)
    {
        QList<QLowEnergyCharacteristic> list = m_service->characteristics();
        for(int i = 0; i < list.count(); i++)
        {
            //当前位置的bleCharacteritic
            m_bleCharacteristic = list.at(i);
            qDebug() << __FUNCTION__ << __LINE__ << m_bleCharacteristic.name() << m_bleCharacteristic.uuid().toString();

            //如果当前characteristic有效
            if(m_bleCharacteristic.isValid())
            {
                //描述符定义特征如何由特定客户端配置
                m_notificationDesc = m_bleCharacteristic.descriptor(QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);

                //如果descriptor有效
                if(m_notificationDesc.isValid())
                {
                    qDebug() << __FUNCTION__ << __LINE__;
                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                }

                if (m_bleCharacteristic.properties() & QLowEnergyCharacteristic::WriteNoResponse ||
                    m_bleCharacteristic.properties() & QLowEnergyCharacteristic::Write)
                {
                    qDebug() << __FUNCTION__ << __LINE__;
                    m_writeCharacteristic[0] = m_bleCharacteristic;
                }
            }
        }
    }
}

void BLEConnect::onServiceStateChanged(QLowEnergyService::ServiceState s)
{
    qDebug() << "serviceStateChanged, state: " << s;
    if (s == QLowEnergyService::ServiceDiscovered) {
        searchCharacteristic();
    }
}

void BLEConnect::ble_dev_tool_service_characteristic_changed_slot(QLowEnergyCharacteristic characteristic, QByteArray value)
{
    qDebug() <<"receive notification data from peripheral";
}

#if 0
void BLEConnect::serviceScanDone()
{
    //setInfo("Service scan done.");
//    ui->bluemsg->append("Service scan done.");
    emit fromBle("Service scan done.");

    qDebug() << __FUNCTION__ << __LINE__;
    m_service = m_control->createServiceObject(QBluetoothUuid(serviceUuid),
                                               this);
    if(m_service)
    {
//        ui->bluemsg->append("服务建立成功\n");
        emit fromBle("服务建立成功");

        m_service->discoverDetails();
    }
    else
    {
//        ui->bluemsg->append("Service not found");
        emit fromBle("Service not found");
        return;
    }
    // 监听服务状态变化
    connect(m_service, &QLowEnergyService::stateChanged, this,
            &BLEConnect::serviceStateChanged);
    // 服务的特征变化，有数据传来
    connect(m_service, &QLowEnergyService::characteristicChanged, this,
            &BLEConnect::BleServiceCharacteristicChanged);
    // 错误处理
    connect(m_service, &QLowEnergyService::characteristicRead, this,
            &BLEConnect::BleServiceCharacteristicRead);
    // 描述符成功被写
    connect(m_service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic,QByteArray)),
            this, SLOT(BleServiceCharacteristicWrite(QLowEnergyCharacteristic,QByteArray)));

    if(m_service->state()==QLowEnergyService::DiscoveryRequired)
    {
        m_service->discoverDetails();
    }
    else
    {
        searchCharacteristic();
    }
}
#endif

void BLEConnect::serviceStateChanged(QLowEnergyService::ServiceState s)
{
    qDebug() << __FUNCTION__ << __LINE__;
    if(s == QLowEnergyService::ServiceDiscovered)
    {
//        ui->bluemsg->append("服务已同步\n");
        emit fromBle("服务已同步");
qDebug() << __FUNCTION__ << __LINE__;
        searchCharacteristic();
    }
}

void BLEConnect::searchCharacteristic()
{
    qDebug() << __FUNCTION__ << __LINE__;

#if 0
    if(m_service)
    {
        qDebug() << __FUNCTION__ << __LINE__;
        QList<QLowEnergyCharacteristic> list=m_service->characteristics();
        qDebug()<<"list.count()="<<list.count();
        //characteristics 获取详细特性
        SendMaxMode=list.count();  //设置模式选择上限
        for(int i=0;i<list.count();i++)
        {

            QLowEnergyCharacteristic c=list.at(i);

            qDebug()<< "searchCharacteristic" << c.uuid().toString();

            /*如果QLowEnergyCharacteristic对象有效，则返回true，否则返回false*/
            if(c.isValid())
            {
                //                返回特征的属性。
                //                这些属性定义了特征的访问权限。
                if(c.properties() & QLowEnergyCharacteristic::WriteNoResponse || c.properties() & QLowEnergyCharacteristic::Write)
                    // if(c.properties() & QLowEnergyCharacteristic::Write)
                {
//                    ui->bluemsg->insertPlainText("具有写权限!\n");
                    emit fromBle("获取蓝牙写权限!");
                    m_writeCharacteristic[i] = c;  //保存写权限特性
                    if(c.properties() & QLowEnergyCharacteristic::WriteNoResponse)
                        //                        如果使用此模式写入特性，则远程外设不应发送写入确认。
                        //                        无法确定操作的成功，并且有效负载不得超过20个字节。
                        //                        一个特性必须设置QLowEnergyCharacteristic :: WriteNoResponse属性来支持这种写模式。
                        //                         它的优点是更快的写入操作，因为它可能发生在其他设备交互之间。
                        m_writeMode = QLowEnergyService::WriteWithoutResponse;
                    else
                        m_writeMode = QLowEnergyService::WriteWithResponse;
                    //如果使用此模式写入特性，则外设应发送写入确认。
                    //如果操作成功，则通过characteristicWritten（）信号发出确认。
                    //否则，发出CharacteristicWriteError。
                    //一个特性必须设置QLowEnergyCharacteristic :: Write属性来支持这种写模式。
                }
                if(c.properties() & QLowEnergyCharacteristic::Read)
                {
                    m_readCharacteristic = c; //保存读权限特性
                }
                //描述符定义特征如何由特定客户端配置。
                m_notificationDesc = c.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
                //值为真
                if(m_notificationDesc.isValid())
                {
                    //写描述符
                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                    //   m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("FEE1"));
//                    ui->bluemsg->insertPlainText("写描述符!\n");
                    emit fromBle("获取蓝牙写描述符!");
                }
            }
        }
    }
#endif

    if(m_service){
        foreach (QLowEnergyCharacteristic c, m_service->characteristics()) {
            if(c.isValid()){
                if (c.properties() & QLowEnergyCharacteristic::WriteNoResponse ||
                    c.properties() & QLowEnergyCharacteristic::Write) {
                    m_writeCharacteristic = c;
                    //update_connected(true);
                    if(c.properties() & QLowEnergyCharacteristic+::WriteNoResponse)
                        m_writeMode = QLowEnergyService::WriteWithoutResponse;
                    else
                        m_writeMode = QLowEnergyService::WriteWithResponse;

                }
                if (c.properties() & QLowEnergyCharacteristic::Read) {
                    m_readCharacteristic = c;
                    if(!m_readTimer){
                        m_readTimer = new QTimer(this);
                        connect(m_readTimer, &QTimer::timeout, this, &BLEInterface::read);
                        m_readTimer->start(READ_INTERVAL_MS);
                    }
                }
                m_notificationDesc = c.descriptor(
                            QBluetoothUuid::ClientCharacteristicConfiguration);
                if (m_notificationDesc.isValid()) {
                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                }
            }
        }
    }
}

void BLEConnect::BleServiceCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
//    ui->bluemsg->insertPlainText(QString(value));
    emit fromBle(QString(value));
}

void BLEConnect::BleServiceCharacteristicRead(const QLowEnergyCharacteristic &c, const QByteArray &value)
{

}

void BLEConnect::BleServiceCharacteristicWrite(const QLowEnergyCharacteristic &c, const QByteArray &value)
{
//    ui->bluemsg->append(QString("指令%1发送成功").arg(QString(value)));
    emit sendRquest(QString(value));
//    ui->bluemsg->append(QString().number(value.length()));
}

void BLEConnect::sendBleMsg(QString text)
{
    QByteArray array=text.toLocal8Bit();
    m_service->writeCharacteristic(m_writeCharacteristic[SendModeSelect],array, m_writeMode);
}
