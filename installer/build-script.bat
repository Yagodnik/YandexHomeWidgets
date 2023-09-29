del -Recurse ./build/deploy/
mkdir build/deploy/
xcopy .\build\release\release\YandexLampTray.exe .\build\deploy
xcopy .\build\release\release\libcrypto-1_1-x64.dll .\build\deploy
xcopy .\build\release\release\libssl-1_1-x64.dll .\build\deploy
cd build/deploy
windeployqt . --no-translations --qmldir ../../
cd ../../
del -Recurse .\installer\packages\com.artemyagodnik.yandexdevicewidgets\data
mkdir installer\packages\com.artemyagodnik.yandexdevicewidgets\data
xcopy .\build\deploy .\installer\packages\com.artemyagodnik.yandexdevicewidgets\data