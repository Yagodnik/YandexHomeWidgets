# Yandex Home Widgets

![](./images/preview.gif)

Yandex Home Widgets - приложение, позволяющее управлять устройствами умного дома Яндекс, не отходя от вашего компьютера

# Установка
Скачать установщик можно вот тут (Для Windows и Linux):
![](./images/1.png)

# Сборка
Для сборки необходимо создать веб-приложение в https://oauth.yandex.ru/, при его создании необходимо разрешить приложению доступ к *API Яндекс ID* (портрету и имени пользователя), а так же выдать разрешение на управление *Яндекс Умный Дом*. \
В графе Redirect URI укажите http://127.0.0.1:1337, этот адрес будет использовать Qt OAuth для авторизации пользователей.

Создаём файл ```secrets.json``` в ```/assets/``` и заполняем его следующим образом:
```json
{
    "client_id": "<Ваш client id>",
    "client_secret": "<Ваш client secret>"
}
```
Далее идёт стандратный процесс сборки, за исключением того, что необходимо скопировать библиотеки ```libcrypto-1_1-x64.dll``` и ```libssl-1_1-x64.dll``` в папку сборки проекта.

# Поддерживаемые устройства
На данный момент поддерживается только лампочка и розетка
