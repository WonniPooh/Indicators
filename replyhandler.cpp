#include "replyhandler.h"

ReplyHandler::ReplyHandler(QObject *pobj): QObject(pobj)
{
    reply_counter = 0;
}

void ReplyHandler::slotHandleReply()
{
    QNetworkReply* reply = (QNetworkReply*)sender();
    int current_timeframe = 0;

    QString current_url = reply->url().toString();
    current_timeframe = current_url.mid(current_url.lastIndexOf('=') + 1,
                                        current_url.length() - current_url.lastIndexOf('=') - 1).toInt();

    QString reply_data = reply->readAll();

    if(reply_data.length() == 0)
    {
        reply->deleteLater();

        if(++reply_counter == 5)
        {
            reply_counter = 0;
            emit doItAgain();
        }
        qDebug() << current_url;
        qDebug() << "request skipped";
        return;
    }

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply_data.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    QJsonObject quote_obj;
    QString technicalSummary;
    int quote = 0;
    int maBuy = 0;
    int maSell = 0;
    int tiBuy = 0;
    int tiSell = 0;

    QJsonObject::iterator end = jsonObject.end();
    end--;

    for (QJsonObject::iterator it = jsonObject.begin(); it != end; it++)
    {
        quote = it.key().toInt();

        quote_obj = it.value().toObject();
        maBuy = quote_obj["maBuy"].toInt();
        maSell = quote_obj["maSell"].toInt();
        tiBuy = quote_obj["tiBuy"].toInt();
        tiSell = quote_obj["tiSell"].toInt();
        technicalSummary = quote_obj["technicalSummary"].toString();

        QJsonObject json_obj;
        json_obj.insert(QString("quote"), QJsonValue(QString::number(quote)));
        json_obj.insert(QString("timeFrame"), QJsonValue(QString::number(current_timeframe)));
        json_obj.insert(QString("technicalSummary"), QJsonValue(technicalSummary));
        json_obj.insert(QString("maBuy"), QJsonValue(QString::number(maBuy)));
        json_obj.insert(QString("maSell"), QJsonValue(QString::number(maSell)));
        json_obj.insert(QString("tiBuy"), QJsonValue(QString::number(tiBuy)));
        json_obj.insert(QString("tiSell"), QJsonValue(QString::number(tiSell)));

        QJsonDocument doc(json_obj);
        QString str_json(doc.toJson(QJsonDocument::Compact));

        if(prev_data.contains(quote))
        {
            if(prev_data.value(quote) != str_json)
            {
                prev_data.insert(quote, str_json);
                //Forvard data
            }
        }
        else
        {
            prev_data.insert(quote, str_json);
            //Forvard data
        }
    }

    reply->deleteLater();

    if(++reply_counter == 5)
    {
        reply_counter = 0;
        emit doItAgain();
    }
}
