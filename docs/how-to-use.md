# 🛠 SBEditorTools Usage Guide

This guide explains how to use SBEditorTools to create DataTable assets from `.json` files.  
As an example, we’ll create a DataTable for `CharacterTable`.

Make sure the `SB Tools` menu is visible in the menu bar.  
If you haven't installed SBEditorTools yet, please follow the **[SBEditorTools Installation Guide](install-guide.md)** first.

![](./images/26-Appear_SBTools.png)

---

## ✅ Step 1: Open the "SB Tools" Menu

1-1. In the UE4 Editor menu bar, select `SB Tools` → `DataTable` → `CharacterTable`.

![Select CharacterTable](./images/27-Select_CharacterTable.png)

If a DataTable asset already exists in UE4 Editor, a confirmation dialog will appear.  
If you select `Yes`, it will proceed to **Step 2** but will delete the existing DataTable asset. **Be careful!**

![Confirm Delete Existing DataTable](./images/43-Confirm_Overwritten_Existing_DataTable.png)

---

## ✅ Step 2: Select a .json File to Create the DataTable Asset

2-1. Select the `.json` file that contains the DataTable data.  

![Select .json file](./images/28-Select_json.png)  
![](./images/29-Select_CharacterTableJsonFile.png)

2-2. A DataTable asset will be created in the appropriate folder. If the folder doesn’t exist, it will be created automatically.  
![](./images/30-Generated_CharacterTableDataTable.png)

---

### Step 2a: Manually Create the DataTable Asset (optional)

If a definition exists in `SBDataTable`, you can also manually create the DataTable using UE4's built-in method.

2a-1. Right-click in the Content Browser and select `Miscellaneous` → `DataTable`.  
![](./images/44-Select_Miscellaneous_DataTable.png)

2a-2. In the "Pick Row Structure" dialog, choose the appropriate structure for your DataTable.  
![](./images/45-Select_Row_Structure.png)

You can find the corresponding Row Structure name at the beginning of the `.json` file.  
![](./images/46-CharacterTableJsonFileHeader.png)

2a-3. Click `Add` to add rows and fill in the values manually.  
![](./images/47-Add_Row.png)

---

## Step 3: Packaging

From this point on, the packaging process follows standard UE4 procedures.

---

### Step 3a: Project Settings

Configure `IOStore` and `Chunk` settings.

3a-1. Go to `Edit` → `Project Settings`, then configure `IOStore` and `Chunk`.  
![](./images/31-ProjectSettings1.png)

3a-2. Go to `Edit` → `Editor Preferences`, and configure `Chunk` settings.  
![](./images/32-ProjectSettings2.png)

3a-3. In the Content Browser, create a new `DataAsset` under `Miscellaneous`.  
![](./images/33-Create_DataAsset.png)

3a-4. Choose `PrimaryAssetLabel`.  
![](./images/34-Select_PrimaryAssetLabel.png)

3a-5. The PrimaryAssetLabel will be created. You can name it anything.  
![](./images/35-After-Create_DataAsset.png)

3a-6. Add the DataTable to the PrimaryAssetLabel.  
![](./images/36-ChunkSetting1_2.png)

3a-7. Confirm that it has been added successfully.  
![](./images/37-ChunkSetting2.png)

3a-8. From the menu, select `File` → `Package Project` → `Windows (64-bit)` to package.  
![](./images/38-Package_Project.png)

3a-9. Choose the output folder.  
![](./images/39-SelectFolder.png)

3a-10. If successful, you’ll see a notification like this:  
![](./images/41-Packaging_Complete.png)

3a-11. After packaging, the output file will appear.  
To use it as a `MOD`, you must rename the file.  
Conventionally, MOD filenames end with `_P`.  
![](./images/42-After_Packaging.png)
