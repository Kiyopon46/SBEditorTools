日本語 | [English](../../README.md)

# SBEditorTools

## はじめに

**SBEditorTools** は、Stellar Blade（PC版）における DataTable アセットを上書きするためのツールです。  
ゲーム本編から FModel というツールを使って .json 形式で DataTable を抽出し、それを任意に編集した後、Unreal Engine 4.26 Editor（以下、UE4 Editor）上で再インポートすることができます。

本プロジェクトは、次の2つの GitHub リポジトリで構成されています：

1. [SBEditorTools](https://github.com/Kiyopon46/SBEditorTools/) - UE4 Editor に導入するプラグイン

2. [SBDataTable](https://github.com/Kiyopon46/SBDataTable/) - 各種 DataTable の定義と、実際のインポート処理

DataTable の追加など、プロジェクトのアップデートは主に [SBDataTable](https://github.com/Kiyopon46/SBDataTable/) 側で行われます。  
本リポジトリである [SBEditorTools](https://github.com/Kiyopon46/SBEditorTools/)は **SBDataTable** を UE4 Editor からメニュー経由で使用するためのプラグインになります。

---

## 導入手順 (概要)

以下の手順で導入できます。  
**スクリーンショット付きの詳細手順はこちら → [詳細導入ガイド](./install-guide-ja.md)**

1. Unreal Engine 4.26 で任意の名前でプロジェクトを作成します。Blueprint でも C++ でも大丈夫です (Blueprint の場合は後の手順が少し追加されます) 。
2. メニューバーの「File → New C++ Class...」をクリックし、任意の名前で C++ クラスを作成します。
3. Visual Studio が開きますがそのまま閉じて良いです。必要ならばソリューションビューから 2. で作成したクラスを削除します。
4. プロジェクト直下に `Source` フォルダが作成されているので、本リポジトリの ZIP を展開するか、任意のコミットをクローンします。
5. 次に `Plugins` フォルダを作成し、[SBEditorTools](https://github.com/Kiyopon46/SBEditorTools/) の ZIP を展開するか、任意のコミットをクローンします。
6. ここまででフォルダ構成は以下のようになります：
```
/YourProjectName/
├── Plugins/
│ └── SBEditorTools/
└── Source/
  └── SBDataTable/
```
7. UE4 Editor が起動中であれば一度終了し、再起動してください。
8. UE4 Editor を起動すると SBEditorPlugin のビルドを求められるのでビルドしてください。
9. UE4 Editor のメニューから「Edit → Plugins」を開き、「SB」と検索し、`SBEditorTools` を有効化します。
10. プラグインの有効化後に再起動を求められるので、再起動します。
11. UE4 Editor 起動後、メニューバーに「SB Tools」が追加されていれば準備完了です。

---

## 使い方 (概要)

基本的な使い方を以下に示します。  
**画像付きの詳細手順はこちら → [使い方ガイド](./how-to-use-ja.md)**

1. メニューバーから「SB Tools → DataTable →  (作成したい DataTable 名) 」を選択します。
 - UE4 Editor 上に対象の DataTable が存在しない場合：  
   `.json` ファイルを選択するダイアログが表示されます。
 - すでに存在する場合：  
   上書き確認のダイアログが表示され、「Yes」を選択すると DataTable が削除された上でファイル選択に進みます (※削除に注意) 。

2. `.json` ファイルを選択すると、内容に基づいて DataTable アセットが作成されます。  
通常は `Content/Local/Data/` 以下に出力されます。  
**DataTable の種類に対応した `.json` ファイルを選んでください。**

参考用に、Stellar Blade PC版 v1.1.2 時点の `.json` ファイルを `Resources/json/` フォルダに同梱しています。

3. あとは通常通り、作成された DataTable を chunk に含めてパックすれば完了です。

---

## ⚠️ 要注意

コンパイルおよびパッキング実行時にセキュリティの問題が発生する可能性があります。

### パッケージング時の Smart App Control 等によるブロックについて

Windows 11 環境で C++ プロジェクトをパッケージングする際、以下のような現象が発生することがあります：

- `AppData/Local/Temp/UAT` 以下に一時的に生成された DLL ファイルの読み込みに失敗する
- 結果としてパッケージングが中断される

この現象は、**Smart App Control（SAC）または SmartScreen** によって、署名されていない一時ファイルの読み込みがブロックされるために発生します。  
この場合、 `Output Log` に次のようなログとスタックとレースが出力されます。

```
ERROR: System.IO.FileLoadException: ファイルまたはアセンブリ 'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll'、またはその依存関係の 1 つが読み込めませんでした。アプリケーション制御ポリシーによってこのファイルがブロックされました。 (HRESULT からの例外:0x800711C7)
       ファイル名 'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll' です。'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll'
       ......

PackagingResults: Error: System.IO.FileLoadException: ファイルまたはアセンブリ 'file:///C:\Users\PC_User\AppData\Local\Temp\UAT\C+Program+Files+Epic+Games+UE_4.26\Rules\UATRules1622703478.dll'、またはその依存関係の 1 つが読み込めませんでした。アプリケーション制御ポリシーによってこのファイルがブロックされました。 (HRESULT からの例外:0x800711C7)
```

### 🔧 対処法

- Smart App Control を無効化する

このエラーが発生した場合、 Windows11 のスマートアプリコントロールを無効にする必要がある場合があります。  
一度無効にすると再度有効にするには OS の再インストールが必要になるため、既に無効にしている場合、または無効のままにしていても構わない場合にのみ、本機能をご利用ください。

## ⚠️ 制限事項

本リポジトリには明示的なライセンスは付与されていません。  
本リポジトリはソースコードの広範な配布を目的としたものではなく、[**AyakaMods** コミュニティ](https://discord.gg/stellarblademodding) 内での情報共有を主目的としています。

本リポジトリに含まれる機能を用いて **Stellar Blade** のゲーム体験を著しく損なう MOD を作成した場合（例：ボスの MaxHP を極端に下げるなど）、  
その使用は「個人利用」や「信頼できる仲間内でのクローズドな共有」に限り許容されます。  
SNS や MOD 配布サイトなどでの**一般公開は固く禁止**します。

一方で、**ゲーム体験をより豊かにするような MOD**については、一般公開も歓迎されます。

なお、「ゲーム体験を著しく損なう」とは何か判断できない方の使用はご遠慮ください。
