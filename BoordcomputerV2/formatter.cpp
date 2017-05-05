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

namespace cangateway {

    QJsonObject Formatter::ToJsonObject(CanData _canData)
    {
       QJsonObject _canDataObject;
       _canDataObject.insert("Description",_canData.Description());
       _canDataObject.insert("ID",_canData.ID());
       _canDataObject.insert("RAW",_canData.RAW());
       _canDataObject.insert("Value",_canData.Value());
       _canDataObject.insert("Timestamp",_canData.Timestamp());

       return _canDataObject;
    }

    QJsonDocument Formatter::ToJsonDocument(QList<CanData> _filteredList)
    {

        QList<Message> _messageList;
        QJsonObject _completeObject;
        QJsonArray _canDataArray;
        QJsonArray _messageArray;

        for(int i=0;i<_filteredList.length();i++)
            {
                _canDataArray.push_back(ToJsonObject(_filteredList[i]));
            }
            _completeObject.insert("Data",_canDataArray);

            for(int i=0;i<_messageList.length();i++)
            {
                QJsonObject MessageObject;
                MessageObject.insert("Type",_messageList[i].Type());
                MessageObject.insert("Content",_messageList[i].Content());
                MessageObject.insert("Timestamp",_messageList[i].Timestamp());
                _messageArray.push_back(MessageObject);
            }
            _completeObject.insert("Message",_messageArray);

            QJsonDocument doc(_completeObject);

         return doc;
    }

    Config Formatter::CompressedToObject(QFile &_receivedConfig)
    {
        Config _config;
        Compression _decompress;
        QStringList _descriptions;
        QStringList _configDescriptions;
        QList<int> _configValues;
        QList<bool> _values;

        _receivedConfig.open(QIODevice::ReadOnly);
        QByteArray compressed = _receivedConfig.readAll();


        if (_receivedConfig.error() != QFile::NoError) {
            qDebug() << QString("Failed to read from file");
            return _config;
        }
        _receivedConfig.close();

        QByteArray uncompressed;
        _decompress.UnZip(compressed,uncompressed);

        if (uncompressed.isEmpty()) {
            qDebug() << "No data was currently available for reading from file";
            return _config;
        }

        QJsonDocument doc(QJsonDocument::fromJson(uncompressed));
        if (!doc.isObject()) {
           qDebug() << "Document is not an object";
           return _config;
        }

        QJsonObject json = doc.object();
        QJsonArray ConfigArray = json["Config"].toArray();

        foreach (const QJsonValue & value, ConfigArray) {
            QJsonObject obj = value.toObject();
            _configDescriptions.append(obj["Description"].toString());
            _configValues.append(obj["Value"].toInt());
        }

        for(int i = 0; i <_configDescriptions.length();i++)
        {
            if((_configDescriptions[i]) == "ReadInterval")
            {
                _config.set_readinterval(_configValues[i]);
            }
        }

        QJsonArray jsonArray = json["Filters"].toArray();

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            _descriptions.append(obj["Description"].toString());
            _values.append(obj["Value"].toBool());
        }

        QMap<QString, bool> hulpmap = _config.get_configmap();

        for(int i = 0; i <_descriptions.length();i++)
        {
            if(hulpmap.contains(_descriptions[i]))
            {
                hulpmap.insert(_descriptions[i],_values[i]);
            }
        }
        _config.set_configmap(hulpmap);

        return _config;


    }

    Config Formatter::ToObject(QFile &_receivedConfig)
    {
        Config _config;
        QStringList _descriptions;
        QStringList _configDescriptions;
        QList<int> _configValues;
        QList<bool> _values;

        _receivedConfig.open(QIODevice::ReadOnly);
        QByteArray file = _receivedConfig.readAll();

        if (_receivedConfig.error() != QFile::NoError) {
            qDebug() << QString("Failed to read from file");
            return _config;
        }
        _receivedConfig.close();

        if (file.isEmpty()) {
            qDebug() << "No data was currently available for reading from file";
            return _config;
        }

        QJsonDocument doc(QJsonDocument::fromJson(file));

        if (!doc.isObject()) {
            qDebug() << "Document is not an object";
            return _config;
        }

        QJsonObject json = doc.object();
        QJsonArray ConfigArray = json["Config"].toArray();

        foreach (const QJsonValue & value, ConfigArray) {
            QJsonObject obj = value.toObject();
            _configDescriptions.append(obj["Description"].toString());
            _configValues.append(obj["Value"].toInt());
        }

        for(int i = 0; i <_configDescriptions.length();i++)
        {
            if((_configDescriptions[i]) == "ReadInterval")
            {
                _config.set_readinterval(_configValues[i]);
            }
        }

        QJsonArray jsonArray = json["Filters"].toArray();

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            _descriptions.append(obj["Description"].toString());
            _values.append(obj["Value"].toBool());
        }


        QMap<QString, bool> hulpmap = _config.get_configmap();

        for(int i = 0; i <_descriptions.length();i++)
        {
            if(hulpmap.contains(_descriptions[i]))
            {
                hulpmap.insert(_descriptions[i],_values[i]);
            }
        }
        _config.set_configmap(hulpmap);
        return _config;


    }
}


