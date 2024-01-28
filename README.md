# Yandex Home Widgets

![](./images/preview.gif)

Yandex Home Widgets - приложение, позволяющее управлять устройствами умного дома Яндекс, не отходя от вашего компьютера
Демо: https://www.youtube.com/watch?v=p_cD33zuICs
# Установка
Скачать установщик можно вот тут (Для Windows):
![](./images/1.png)

P.S. А если вы хотите версию под MacOS вам нужно всего лишь любезно отдать мне свой мак

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

## Флаги
1. ```-allow-several-instances``` Отключает проверку на единственность исполняемого файла
2. ```-disable-updates``` Отключает проверку на обновления (Стоит включить, если хотите что-то дополнить, иначе в папку сборки закачается много лишнего) (на данный момент бесполезна)
3. ```-no-autostart``` Отключает добавление приложения в автозапуск (указывать при первом старте, если хотите отключить эту фичу)

# Поддерживаемые устройства
На данный момент поддерживается только лампочка и розетка
