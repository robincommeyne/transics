/*! \file */
#include "formatter.h"
#include "watchdog.h"
#include "config.h"

#include "compression.h"
#include <QJsonObject>
#include <QFile>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>


QJsonObject Formatter::ToJsonObject(CanData canData)
{
   QJsonObject canDataObject;
   canDataObject.insert("Description",canData.Description());
   canDataObject.insert("ID",canData.ID());
   canDataObject.insert("RAW",canData.RAW());
   canDataObject.insert("Value",canData.Value());
   canDataObject.insert("Timestamp",canData.Timestamp());

   return canDataObject;


}

QJsonDocument Formatter::ToJsonDocument(QList<CanData> FilteredList)
{



    QList<Message> MessageList;

    QJsonObject CompleteObject;

    QJsonArray CanDataArray;
    QJsonArray MessageArray;


    for(int i=0;i<FilteredList.length();i++)
    {
        CanDataArray.push_back(ToJsonObject(FilteredList[i]));
    }
    CompleteObject.insert("Data",CanDataArray);

    for(int i=0;i<MessageList.length();i++)
    {
        QJsonObject MessageObject;
        MessageObject.insert("Type",MessageList[i].Type);
        MessageObject.insert("Content",MessageList[i].Content);
        MessageObject.insert("Timestamp",MessageList[i].Timestamp);
        MessageArray.push_back(MessageObject);



    }
    CompleteObject.insert("Message",MessageArray);

    QJsonDocument doc(CompleteObject);

 return doc;
}

Config Formatter::ToObject(QFile &ReceivedConfig)
{
    Config config;
    Compression decompress;
    QStringList Descriptions;
    QList<bool> Values;

    ReceivedConfig.open(QIODevice::ReadOnly);
    QByteArray compressed = ReceivedConfig.readAll();

    if (ReceivedConfig.error() != QFile::NoError) {
            qDebug() << QString("Failed to read from file");
            //log.Log("debug","Failed to read from file");
            return config;
        }


    QByteArray uncompressed;
    decompress.UnZip(compressed,uncompressed);

    if (uncompressed.isEmpty()) {
            qDebug() << "No data was currently available for reading from file";

            return config;
        }

    QJsonDocument doc(QJsonDocument::fromJson(uncompressed));

    if (!doc.isObject()) {
            qDebug() << "Document is not an object";
            return config;
        }

    QJsonObject json = doc.object();

    QJsonValue jsonValue = json.value("Config");

    if (jsonValue.isUndefined()) {
        qDebug() << "Key id does not exist";
        return config;
    }

    config.ReadInterval = jsonValue.toInt();

    QJsonArray jsonArray = json["Filters"].toArray();

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        Descriptions.append(obj["Description"].toString());
        Values.append(obj["Value"].toBool());
    }


    QStringList myoptions;
    myoptions << "EngineLoad" << "EngineCoolantTemp" << "FuelPressure" << "IntakeMAPressure"
              << "EngineRPM" << "VehicleSpeed" << "TimingAdvance" << "IntakeAirTemp" << "MAFairFlowRate"
              << "ThrottlePosition" << "FuelLevel" << "BarometricPressure" << "EngineFuelRate";


    for(int i = 0; i <Descriptions.length();i++)
    {

    switch(myoptions.indexOf(Descriptions[i])){
      case 0:
        config.EngineLoad = Values[i];
        break;

      case 1:
        config.EngineCoolantTemp = Values[i];
        break;

      case 2:
        config.FuelPressure = Values[i];
        break;

      case 3:
        config.IntakeMAPressure = Values[i];
        break;

      case 4:
        config.EngineRPM = Values[i];
        break;

      case 5:
        config.VehicleSpeed = Values[i];
        break;

      case 6:
        config.TimingAdvance = Values[i];
        break;

      case 7:
        config.IntakeAirtemp = Values[i];
        break;

      case 8:
        config.MAFairFlowRate = Values[i];
        break;

      case 9:
        config.ThrottlePosition = Values[i];
        break;

      case 10:
        config.FuelLevel = Values[i];
        break;

      case 11:
        config.BarometricPressure = Values[i];
        break;

      case 12:
        config.EngineFuelRate = Values[i];
        break;

      default:
        qDebug() << "No Matching description found";
        break;
    }


    }

    return config;


}
