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

For detailed **usage instructions**, please refer to the [README.md of SBDataTable](https://github.com/Kiyopon46/SBDataTable/blob/main/README.md).

## ⚠️ Important Note

Depending on your system configuration, you may encounter issues during compilation or execution due to Windows application control policies.  
If that happens, you may need to **disable Smart App Control** on Windows 11.  
Please only use this tool if Smart App Control is already disabled or can be safely disabled on your system.

## ⚠️ Usage Restrictions

This repository is not distributed under any formal open-source license.  
It is intended primarily for sharing technical knowledge within the [**AyakaMods** community](https://discord.gg/stellarblademodding), not for wide public distribution of the source code.

If you use the tools in this repository to create MODs that **significantly degrade the gameplay experience** of **Stellar Blade** (e.g., drastically lowering a boss's Max HP),  
such use is tolerated **only for personal or private use among trusted individuals**.  
**Public distribution** of such MODs, including on social media or mod-sharing platforms, is strictly prohibited.

On the other hand, MODs that **enhance the gameplay experience** are welcome to be shared publicly.

If you are unsure whether your MOD would significantly degrade the experience, **please refrain from using this repository**.
