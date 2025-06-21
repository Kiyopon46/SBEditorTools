[日本語](docs/ja/README-ja.md) | English

# SBEditorTools

## Introduction

**SBEditorTools** is a plugin for Unreal Engine 4.26 Editor that enables the use of **SBDataTable**, a tool for overwriting DataTable assets in the PC version of *Stellar Blade*.  
Using a tool called **FModel**, you can extract in-game DataTable assets as `.json` files, edit them, and re-import them into the UE4 Editor through this plugin.

This project consists of two related GitHub repositories:

1. [SBEditorTools](https://github.com/Kiyopon46/SBEditorTools/) – The UE4 Editor plugin (this repository)
2. [SBDataTable](https://github.com/Kiyopon46/SBDataTable/) – Contains definitions for each DataTable and the import logic

Most updates—such as the addition of new DataTables—are applied to the [SBDataTable](https://github.com/Kiyopon46/SBDataTable/) repository.  
This repository serves as the **menu-based interface** that makes SBDataTable available from within the UE4 Editor.

---

Follow the steps below to install.  
**For detailed installation steps with screenshots → [Installation Guide](./docs/install-guide.md)**

1. Create a new project in Unreal Engine 4.26 with any name. You can use either Blueprint or C++ (if using Blueprint, additional steps are required later).

2. In the menu bar, click File → New C++ Class... and create a C++ class with any name.

3. When Visual Studio launches, you can simply close it. If necessary, delete the class created in step 2 from the solution.

4. A Source folder will be created in your project root. Extract the ZIP of this repository or clone a desired commit into it.

5. Create a Plugins folder and extract the ZIP of SBEditorTools or clone a desired commit into it.

6. The folder structure should now look like this:

```
/YourProjectName/
├── Plugins/
│ └── SBEditorTools/
└── Source/
  └── SBDataTable/
```

7. If UE4 Editor is running, close it and restart.

8. When UE4 Editor starts, it will prompt you to build SBEditor Plugin. Proceed with the build.

9. In the UE4 Editor menu, go to Edit → Plugins, search for SB, and enable SBEditorTools.

10. You will be prompted to restart the editor. Please do so.

11. Once restarted, if the SB Tools menu appears in the menu bar, the setup is complete.


## How to Use

The basic usage is outlined below.  
**For a step-by-step guide with screenshots → [How to Use Guide](./docs/how-to-use.md)**  


1. In the UE4 Editor menu, go to SB Tools → DataTable → (Select the desired DataTable name).

    - If the DataTable does not exist in the editor:
A file dialog will open for selecting a .json file.

    - If the DataTable already exists:
A confirmation dialog will appear. Selecting "Yes" will delete the existing asset and proceed to the file selection (⚠️ use caution).

2. Once a .json file is selected, the DataTable asset will be generated based on its content.
Normally, it will be created under Content/Local/Data/.
Make sure to select a .json file that matches the desired DataTable type.

    - Sample .json files from Stellar Blade PC version v1.1.2 are included under the Resources/json/ folder.

3. Finally, include the created DataTable in your chunk and package as usual.


## ⚠️ Important Notes

There may be security issues during compilation or packaging.

### Smart App Control Blocking During Packaging

In Windows 11, the following issues may occur when packaging a C++ project:

- Temporary DLL files generated under `AppData/Local/Temp/UAT` fail to load
- Packaging process is interrupted

This issue arises due to **Smart App Control (SAC)** or **SmartScreen** blocking unsigned temporary files.  
The `Output Log` may contain errors like the following:

```
ERROR: System.IO.FileLoadException: ファイルまたはアセンブリ 'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll'、またはその依存関係の 1 つが読み込めませんでした。アプリケーション制御ポリシーによってこのファイルがブロックされました。 (HRESULT からの例外:0x800711C7)
       ファイル名 'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll' です。'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll'
       ......

PackagingResults: Error: System.IO.FileLoadException: ファイルまたはアセンブリ 'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll'、またはその依存関係の 1 つが読み込めませんでした。アプリケーション制御ポリシーによってこのファイルがブロックされました。 (HRESULT からの例外:0x800711C7)
```

### 🔧 Solution

- Disable Smart App Control

If this error occurs, you may need to disable Smart App Control in Windows 11.  
Note that once disabled, re-enabling it requires OS reinstallation. Use this function only if you have already disabled SAC or do not mind it remaining disabled.

## ⚠️ Usage Restrictions

This repository is not distributed under any formal open-source license.  
It is intended primarily for sharing technical knowledge within the [**AyakaMods** community](https://discord.gg/stellarblademodding), not for wide public distribution of the source code.

If you use the tools in this repository to create MODs that **significantly degrade the gameplay experience** of **Stellar Blade** (e.g., drastically lowering a boss's Max HP),  
such use is tolerated **only for personal or private use among trusted individuals**.  
**Public distribution** of such MODs, including on social media or mod-sharing platforms, is strictly prohibited.

On the other hand, MODs that **enhance the gameplay experience** are welcome to be shared publicly.

If you are unsure whether your MOD would significantly degrade the experience, **please refrain from using this repository**.
