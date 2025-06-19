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

具体的な **使用手順** 以降は [SBDataTable の README-ja.md](https://github.com/Kiyopon46/SBDataTable/blob/main/docs/ja/README-ja.md) をご覧ください。

## ⚠️ 要注意
コンパイルおよび実行時にパッキングの問題が発生する可能性があります。その場合は、Windows11のスマートアプリコントロールを無効にする必要があります。既に無効にしている場合、または無効にできる場合にのみ、この本機能をご利用ください。

## ⚠️ 制限事項

本リポジトリには明示的なライセンスは付与されていません。  
本リポジトリはソースコードの広範な配布を目的としたものではなく、[**AyakaMods** コミュニティ](https://discord.gg/stellarblademodding) 内での情報共有を主目的としています。

本リポジトリに含まれる機能を用いて **Stellar Blade** のゲーム体験を著しく損なう MOD を作成した場合（例：ボスの MaxHP を極端に下げるなど）、  
その使用は「個人利用」や「信頼できる仲間内でのクローズドな共有」に限り許容されます。  
SNS や MOD 配布サイトなどでの**一般公開は固く禁止**します。

一方で、**ゲーム体験をより豊かにするような MOD**については、一般公開も歓迎されます。

なお、「ゲーム体験を著しく損なう」とは何か判断できない方の使用はご遠慮ください。
