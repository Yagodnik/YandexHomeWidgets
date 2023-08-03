#ifndef YANDEXLAMP_H
#define YANDEXLAMP_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QColor>
#include <QRgb>

typedef enum {
    ON, OFF, UNKNOWN
} LampState;

class YandexLamp : public QObject
{
    Q_OBJECT
public:
    explicit YandexLamp(QString deviceId,
                        QString oauthTokeb,
                        QObject *parent = nullptr);
    ~YandexLamp();

    LampState getState();
    Q_INVOKABLE void on();
    Q_INVOKABLE void off();
    Q_INVOKABLE void setBrightness(int brightness);
    Q_INVOKABLE void setColor(QRgb color);

private:
    LampState _lampState;
    QString _deviceId;
    QString _oauthToken;
    QNetworkAccessManager *networkManager;

    QJsonObject generateRequest(QJsonObject action);
    QJsonObject generateAction(LampState lampState);
    QJsonObject generateAction(int brightness);
    QJsonObject generateAction(QRgb color);

    void sendPostRequest(QByteArray data);

private slots:
    void onReply(QNetworkReply *reply);
};

#endif // YANDEXLAMP_H
