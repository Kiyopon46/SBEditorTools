# 🛠 SBEditorTools の使い方ガイド

このガイドでは、 SBEditorTools を使用して `.json` ファイルから DataTable アセットを作成する方法を説明します。  
ここでは、例として CharacterTable の DataTable を作成します。　　

事前にメニューバーに「SB Tools」のメニューがあることを確認してください。  
まだ SBEditorTools を導入していない場合は **[SBEditorTools インストールガイド](install-guide-ja.md)** を参照して導入してください。

![](../images/26-Appear_SBTools.png)

---

## ✅ ステップ1：「SB Tools」メニューを開く

1-1. UE4 Editor メニューバーから `SB Tools` → `DataTable` → `CharacterTable` を選択します。

![Select CharacterTable](../images/27-Select_CharacterTable.png)

このとき、既に DataTable アセットが UE4 Editor 上に作成されている場合、上書きしても良いか確認するダイアログが表示されます。  
Yes を選択すると **ステップ2** に進むことができますが、**この時点で既存の DataTable アセットは削除されます。ご注意ください。**  

![Confirm Delete Existing DataTable](../images/43-Confirm_Overwritten_Existing_DataTable.png)

## ✅ ステップ2：.json ファイルを選択して DataTable アセットを作成

2-1. 作成する DataTable の .json ファイルを読み込みます。  

![Select .json file](../images/28-Select_json.png)

![](../images/29-Select_CharacterTableJsonFile.png)

2-2. 選択した DataTable が所定のフォルダに作成されます。フォルダがなかった場合は作成されます。

![](../images/30-Generated_CharacterTableDataTable.png)

### ステップ2a : .json ファイルからではなく手動でアセットを追加する

`SBDataTable` に定義があれば、UE4 Editor の通常の DataTable 作成手順でもその DataTable を作成することができます。  

2a-1. `Miscellaneous` → `DataTable` を選択します。  

![](../images/44-Select_Miscellaneous_DataTable.png)


2a-2. `Pick Row Structure` から該当の DataTable 構造体 (Row Structure) を選択します。  

![](../images/45-Select_Row_Structure.png)


どの Row Structure を選択するかは、元にした .json ファイルの冒頭に記載があります。  

![](../images/46-CharacterTableJsonFileHeader.png)

2a-3. `Add` ボタンをクリックして行を追加し、入力していきます。  

![](../images/47-Add_Row.png)

## ステップ3 : パッキング

以降は通常のパッキング工程と同じです。

### ステップ3a : プロジェクトの設定

IOStore と Chunk の設定を行います。  

3a-1. メニューバーから `Edit` → `Project Setting...` を選択し、 `IOStore` の設定と `Chunk` の設定を行います。  

![](../images/31-ProjectSettings1.png)

3a-2. メニューバーから `Edit` → `Edior Preferences...` を選択し、 `Chunk` の設定を行います。

![](../images/32-ProjectSettings2.png)

3a-3. `Miscellaneous` → `DataAsset` を選択します。  

![](../images/33-Create_DataAsset.png)

3a-4. `PrimaryAssetLabel` を選択します。

![](../images/34-Select_PrimaryAssetLabel.png)

3a-5. PrimaryAssetLabel が作成されます。名前は何でも良いです。  

![](../images/35-After-Create_DataAsset.png)

3a-6. PrimaryAssetLabel に DataTable を追加します。  

![](../images/36-ChunkSetting1_2.png)

3a-7. 追加されたことを確認します。  

![](../images/37-ChunkSetting2.png)

3a-7. メニューバーから `File` → `Package Project` → `Windows (64-bit)` を選択してパッケージングを実行します。  

![](../images/38-Package_Project.png)

3a-8. 結果を出力するフォルダーを選択します。    

![](../images/39-SelectFolder.png)

3a-9. 成功した場合はこのようなメッセージが画面右下に表示されます。  

![](../images/41-Packaging_Complete.png)

3a-10. パッケージングが成功するとファイルが作成されます。 `MOD` として有効にするためにはファイル名を変更する必要があります。  
また、 `MOD` のファイル名の末尾には `_P` をつけるのが慣例となっています。  

![](../images/42-After_Packaging.png)
