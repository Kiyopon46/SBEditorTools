# 📥 SBEditorTools Installation Guide

This guide provides step-by-step instructions with screenshots on how to integrate SBDataTable into your UE4 project.

---

## Step 1: Create a New UE4 Project (if starting from scratch)

Create a new Unreal Engine 4.26 project with any name. Either `Blueprint` or `C++` is fine.  
If you are integrating into an existing project, start from **Step 2**.

1-1. Select `Games` → `Next`.  
![Select or Create New Project](./images/01-Create_New_Project.png)

1-2. Select `Blank` → `Next`.  
![Select Template](./images/02-Select_Template.png)

1-3. Choose either `Blueprint` or `C++`.  
If you select `Blueprint`, you’ll need to convert to a C++ project in Step 2. Click `Create Project`.  
![Project Settings](./images/03-Project_Settings.png)

---

## Step 2: Convert to a C++ Project

Convert your project to C++.  
If you selected `C++` in Step 1 or are using an existing C++ project, skip to **Step 3**.  
If you’re unsure or used `Blueprint`, proceed with this step.

2-1. Click `File` → `New C++ Class...`  
![New C++ Class...](./images/04-New_Cpp_Class.png)

2-2. In the "Choose Parent Class" dialog, select `None` → `Next`.  
![Choose Parent Class](./images/05-Choose_Parant_Class.png)

2-3. Enter any name in `Name`, then click `Create Class`.  
![Name Your New Class](./images/06-Name_Your_New_Class.png)

2-4. Wait for compilation to finish.  
![Compiling](./images/07-Compiling_new_cpp_code.png)  
![Compiling](./images/08-Compiling_cpp_code.png)

2-5. Visual Studio will launch. Your project is now a C++ project.  
You can proceed to **Step 3**, but it’s recommended to remove the unnecessary class.  
![Launched VS](./images/09-Launched_VS.png)

2-6. Remove the folder containing the class created in 2-3 from the solution.  
![Remove Unnecessary Codes](./images/10-Remove_Unnecessary_Code.png)

2-7. Click `OK`.  
![Confirm OK](./images/11-Confirm.png)

2-8. The class is removed from the solution. The files remain, but that’s fine.  
![After Removed Unnecessaries](./images/13-After_Removed_Unnecessaries.png)

2-9. Close Visual Studio.  
![Close VS](./images/14-Close_VS.png)

---

## Step 3: Add SBDataTable and SBEditorTools

Integrate both [SBDataTable](https://github.com/Kiyopon46/SBDataTable/) and [SBEditorTools](https://github.com/Kiyopon46/SBEditorTools/) into your project.

3-1. Your project folder should look like this. If you already added plugins, you may see a `Plugins` folder.  
![](./images/15-After_Closed_VS.png)

3-2. Clone `SBDataTable` into the `Source` folder (or download the latest release ZIP).  

```
git clone https://github.com/Kiyopon46/SBDataTable.git
```

![clone SBDataTable](./images/16-Clone_SBDataTable.png)

3-3. Clone `SBEditorTools` into the `Plugins` folder (or download the latest release ZIP).  

```
git clone https://github.com/Kiyopon46/SBEditorTools.git
```

![](./images/17-Clone-SBEditorTools.png)

3-4. Your folder structure should now look like this:  

```
/YourProjectName/
├── Plugins/
│ └── SBEditorTools/
└── Source/
  └── SBDataTable/
```


3-5. If UE4 Editor is open, close and reopen it.

3-6. When reopening the project via `.uproject`, it will prompt you to build SBEditorPlugin. Click `Yes`.  
![](./images/21-Run_Uproject.png)  
![](./images/22-Build_Confirmation.png)  
![](./images/23-Build_Progress.png)

3-9. If UE4 Editor starts successfully, the setup is complete.

---

## Step 4: Enable SBEditorTools Plugin

4-1. Open `Edit → Plugins` in UE4 Editor, search for `SB`, and enable `SBEditorTools`.  
![](./images/24-Select_Plugins.png)

4-2. Enable the plugin, then restart UE4 Editor when prompted.  
![](./images/25-Enabled_SBEditorTools.png)

4-3. Once restarted, if you see `SB Tools` in the menu bar, setup is complete!  
![](./images/26-Appear_SBTools.png)
