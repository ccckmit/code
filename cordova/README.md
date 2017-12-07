# Cordova

安裝 Android SDK (Android Studio0) + Cordova

* You have not accepted the license agreements of the following SDK component
  * 解決方法: $ANDROID_HOME/tools/bin/sdkmanager --licenses
  * https://stackoverflow.com/questions/26739114/android-studio-sdk-location

```
cordova run android

```

https://spring.io/guides/gs/android/

Windows
set ANDROID_HOME=C:\<installation location>\android-sdk-windows
set PATH=%PATH%;%ANDROID_HOME%\tools;%ANDROID_HOME%\platform-tools

No target specified and no devices found, deploying to emulator
Error: No emulator images (avds) found.
1. Download desired System Image by running: "C:\Users\user\AppData\Local\Android\Sdk\tools\android.bat" sdk
2. Create an AVD by running: "C:\Users\user\AppData\Local\Android\Sdk\tools\android.bat" avd
HINT: For a faster emulator, use an Intel System Image and install the HAXM device driver

D:\test\cordovaAndroidApp>android avd
'android' 不是內部或外部命令、可執行的程式或批次檔。

## Configure On-Device Developer Options

手機必須啟用《開發人員模式》

* https://developer.android.com/studio/debug/dev-options.html

1. Open the Settings app.
2. (Only on Android 8.0 or higher) Select System.
3. Scroll to the bottom and select About phone.
4. Scroll to the bottom and tap Build number 7 times.
5. Return to the previous screen to find Developer options near the bottom.

## Run Apps on a Hardware Device

執行 Cordova run android

* https://developer.android.com/studio/run/device.html

我的電腦等級太低，沒有 Hyper-Threading 技術，因此跑 Emulator 很慢，只能在手機上直接測。

