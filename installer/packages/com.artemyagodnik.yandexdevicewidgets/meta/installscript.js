function Component()
{
	installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
}

Component.prototype.createOperations = function()
{
    try {
        component.createOperations();

        if (installer.value("os") == "win") { 
            try {
                component.addOperation("CreateShortcut", "@TargetDir@\\YandexLampTray.exe", "@StartMenuDir@/YandexHomeWidgets.lnk");
                component.addOperation("CreateShortcut", "@TargetDir@\\YandexLampTray.exe", "@StartMenuDir@/YandexHomeWidgets.lnk");
            } catch (e) {
                print(e)
            }
        }
    } catch (e) {
        print(e);
    }
}