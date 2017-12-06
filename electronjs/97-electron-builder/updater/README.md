# electron-updater 的範例

本範例 fork 自 https://github.com/iffy/electron-updater-example

當你在 github 上 release 新版本時，已經釋出安裝好的軟體也會跟著更新。

記得要更新 package.json 中的 version 才會有新的釋出。

以下是更新畫面

![](img/updating.png)

記得您必須在 [releases](releases) 當中設定 draft 為 update release 之後，才會正式 release.

還有必須在環境變數中設定 [Environment]::SetEnvironmentVariable("GH_TOKEN","<YOUR_TOKEN_HERE>","User")

然後重新啟動 shell / cmd/powershell 之後，環境變數才會生效。

github 的 GH_TOKEN 可以在下列網址產生：

<https://github.com/settings/tokens/new>

--------------

This repo contains the **bare minimum code** to have an auto-updating Electron app using [`electron-updater`](https://github.com/electron-userland/electron-builder/tree/master/packages/electron-updater) with releases stored on GitHub.

If you can't use GitHub, you can use other providers:

- [Complete electron-updater HTTP example](https://gist.github.com/iffy/0ff845e8e3f59dbe7eaf2bf24443f104)
- [Complete electron-updater from gitlab.com private repo example](https://gist.github.com/Slauta/5b2bcf9fa1f6f6a9443aa6b447bcae05)

**NOTE:** If you want to run through this whole process, you will need to fork this repo on GitHub and replace all instances of `iffy` with your GitHub username before doing the following steps.

1. For macOS, you will need a code-signing certificate.
    
    Install Xcode (from the App Store), then follow [these instructions](https://developer.apple.com/library/content/documentation/IDEs/Conceptual/AppDistributionGuide/MaintainingCertificates/MaintainingCertificates.html#//apple_ref/doc/uid/TP40012582-CH31-SW6) to make sure you have a "Mac Developer" certificate.  If you'd like to export the certificate (for automated building, for instance) [you can](https://developer.apple.com/library/content/documentation/IDEs/Conceptual/AppDistributionGuide/MaintainingCertificates/MaintainingCertificates.html#//apple_ref/doc/uid/TP40012582-CH31-SW7).  You would then follow [these instructions](https://github.com/electron-userland/electron-builder/wiki/Code-Signing).

2. Adjust `package.json` if needed.

    By default, `electron-updater` will try to detect the GitHub settings (such as the repo name and owner) from reading the `.git/config` or from reading other attributes within `package.json`.  If the auto-detected settings are not what you want, configure the [`publish`](https://github.com/electron-userland/electron-builder/wiki/Publishing-Artifacts#PublishConfiguration) property as follows:

        {
            ...
            "build": {
                "publish": [{
                    "provider": "github",
                    "owner": "iffy",
                    "repo": "electron-updater-example"
                }],
                ...
            }
        }

3. Install necessary dependencies with:

        yarn
   
   or
   
        npm install

4. Generate a GitHub access token by going to <https://github.com/settings/tokens/new>.  The access token should have the `repo` scope/permission.  Once you have the token, assign it to an environment variable 

    On macOS/linux:

        export GH_TOKEN="<YOUR_TOKEN_HERE>"

    On Windows, run in powershell:

        [Environment]::SetEnvironmentVariable("GH_TOKEN","<YOUR_TOKEN_HERE>","User")

    Make sure to restart IDE/Terminal to inherit latest env variable.

5. Publish for your platform with:

        build -p always

   or

        npm run publish

   If you want to publish for more platforms, edit the `publish` script in `package.json`.  For instance, to build for Windows and macOS:

        ...
        "scripts": {
            "publish": "build --mac --win -p always"
        },
        ...
    
6. Release the release on GitHub by going to <https://github.com/iffy/electron-updater-example/releases>, editing the release and clicking "Publish release."

7. Download and install the app from <https://github.com/iffy/electron-updater-example/releases>.

8. Update the version in `package.json`, commit and push to GitHub.

9. Do steps 5 and 6 again.

10. Open the installed version of the app and see that it updates itself.

