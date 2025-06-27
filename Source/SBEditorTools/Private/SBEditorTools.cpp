#include "SBEditorTools.h"
#include "SBEditorToolsEdMode.h"

#include "LevelEditor.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#include "AssetToolsModule.h"
#include "ObjectTools.h"
#include "Engine/DataTable.h"
#include "Editor/UnrealEd/Public/ObjectTools.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Dom/JsonObject.h"

#include "AssetRegistryModule.h"
#include "Misc/PackageName.h"
#include "UObject/SavePackage.h"

#include "Importer/FSBDataTableImporterFactory.h"

#define LOCTEXT_NAMESPACE "FSBEditorToolsModule"

void FSBEditorToolsModule::StartupModule()
{
	// Register Menu Extension
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FSBEditorToolsModule::AddMenuBarMenu));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

    FSBDataTableImporterFactory Factory;
    Factory.RegisterAll();
    CachedImporterArray = Factory.GetImporterMapSortedByName();
}

void FSBEditorToolsModule::ShutdownModule()
{
    //// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    //// we call this function before unloading the module.
    //FEditorModeRegistry::Get().UnregisterMode(FSBEditorToolsEdMode::EM_SBEditorToolsEdModeId);
}

void FSBEditorToolsModule::AddMenuBarMenu(FMenuBarBuilder& MenuBarBuilder)
{
	MenuBarBuilder.AddPullDownMenu(
        LOCTEXT("SBToolsMenu", "SB Tools"),
        LOCTEXT("SBToolsMenu_ToolTip", "Custom tools for Stellar Blade modding"),
        FNewMenuDelegate::CreateRaw(this, &FSBEditorToolsModule::GenerateSBToolsMenu),
        "SBTools"
    );
}

void FSBEditorToolsModule::GenerateSBToolsMenu(FMenuBuilder& MenuBuilder)
{
    MenuBuilder.AddSubMenu(
        LOCTEXT("DataTableSubmenu", "DataTable"),
        LOCTEXT("DataTableSubmenu_Tooltip", "DataTable related tools"),
        FNewMenuDelegate::CreateRaw(this, &FSBEditorToolsModule::GenerateDataTableMenu)
    );
}

void FSBEditorToolsModule::GenerateDataTableMenu(FMenuBuilder& MenuBuilder)
{
	// Select .json files.
	MenuBuilder.AddMenuEntry(
		LOCTEXT("ImportJsonFile", "Import .json Files"),
		LOCTEXT("ImportJsonFile_Tooltip", "Select file(s) containing JSON DataTables to import."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FSBEditorToolsModule::HandleJsonFiles))
	);

	// Select folder.
	MenuBuilder.AddMenuEntry(
		LOCTEXT("ImportJsonFileByFolder", "Import .json Files from Folder"),
		LOCTEXT("ImportJsonFileByFolder_Tooltip", "Select a folder containing JSON DataTables to import."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(this, &FSBEditorToolsModule::HandleFolder))
	);

}

TArray<FString> FSBEditorToolsModule::SelectJsonFiles()
{
	TArray<FString> JsonFiles;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		return JsonFiles;
	}

	// ファイル or フォルダを選択
	const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	const bool bFileSelected = DesktopPlatform->OpenFileDialog(
		ParentWindowHandle,
		TEXT("Select JSON file or folder"),
		TEXT(""),
		TEXT(""),
		TEXT("JSON files (*.json)|*.json"),
		EFileDialogFlags::Multiple,
		JsonFiles
	);

	if (!bFileSelected || JsonFiles.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("!bFileSelected || JsonFiles.Num() == 0 failed."));
		return JsonFiles;
	}

	return JsonFiles;
}

TArray<FString> FSBEditorToolsModule::SelectJsonFolder()
{
	TArray<FString> JsonFiles;

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		return JsonFiles;
	}

	// フォルダ選択
	FString SelectedFolder;
	const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	const bool bFolderSelected = DesktopPlatform->OpenDirectoryDialog(
		ParentWindowHandle,
		TEXT("Select Folder Containing JSON Files"),
		TEXT(""),
		SelectedFolder
	);

	if (!bFolderSelected || SelectedFolder.IsEmpty())
	{
		return JsonFiles;
	}

	// フォルダ内の .json ファイルを列挙
	IFileManager::Get().FindFilesRecursive(
		JsonFiles,
		*SelectedFolder,
		TEXT("*.json"),
		true,  // Files
		false  // Directories
	);

	return JsonFiles;
}

void FSBEditorToolsModule::ProcessAllFiles(TArray<FString> JsonPaths)
{
	// ImporterFactory を使って処理
	FSBDataTableImporterFactory Factory;
	Factory.RegisterAll();

	for (const FString& JsonPath : JsonPaths)
	{
		TSharedPtr<FJsonObject> RootJson = LoadJsonDataTableObject(*JsonPath);
		if (!RootJson.IsValid())
		{
			continue;
		}

		TSharedPtr<FSBDataTableImporter> Importer = Factory.GetImporterFor(RootJson);
		if (Importer.IsValid())
		{
			Importer->Execute(RootJson);
			UE_LOG(LogTemp, Display, TEXT("Imported: %s via %s"), *JsonPath, *Importer->GetDataTableName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No importer found for: %s"), *JsonPath);
		}
	}
}

void FSBEditorToolsModule::HandleJsonFiles()
{
	//IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	//if (!DesktopPlatform)
	//{
	//	return;
	//}

	//// ファイル or フォルダを選択
	//TArray<FString> OutFiles;
	//const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	//const bool bFileSelected = DesktopPlatform->OpenFileDialog(
	//	ParentWindowHandle,
	//	TEXT("Select JSON file or folder"),
	//	TEXT(""),
	//	TEXT(""),
	//	TEXT("JSON files (*.json)|*.json"),
	//	EFileDialogFlags::None,
	//	OutFiles
	//);

	TArray<FString> JsonPaths = SelectJsonFiles();

	ProcessAllFiles(JsonPaths);

	//// ImporterFactory を使って処理
	//FSBDataTableImporterFactory Factory;
	//Factory.RegisterAll();

	//for (const FString& JsonPath : JsonPaths)
	//{
	//	TSharedPtr<FJsonObject> RootJson = LoadJsonDataTableObject(*JsonPath);
	//	if (!RootJson.IsValid())
	//	{
	//		continue;
	//	}

	//	TSharedPtr<FSBDataTableImporter> Importer = Factory.GetImporterFor(RootJson);
	//	if (Importer.IsValid())
	//	{
	//		Importer->Execute(RootJson);
	//		UE_LOG(LogTemp, Display, TEXT("Imported: %s via %s"), *JsonPath, *Importer->GetDataTableName());
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("No importer found for: %s"), *JsonPath);
	//	}
	//}
}

void FSBEditorToolsModule::HandleFolder()
{
	TArray<FString> JsonPaths = SelectJsonFolder();

	ProcessAllFiles(JsonPaths);
}

TSharedPtr<FJsonObject> FSBEditorToolsModule::LoadJsonDataTableObject(const FString& FilePath)
{
	// Loading a JSON file
	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *FilePath)) {
		UE_LOG(LogTemp, Warning, TEXT("LoadFileToString() failed."));
		return nullptr;
	}

	// If the first character is a BOM, delete it.
	if (FileContent.StartsWith(TEXT("\xFEFF"))) {
		FileContent.RightChopInline(1);  // Delete the first character
	}

	// Create an Array from JSON
	TArray<TSharedPtr<FJsonValue>> RootArray;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileContent);

	if (!FJsonSerializer::Deserialize(Reader, RootArray) || RootArray.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON as array or array is empty."));
		return nullptr;
	}

	// Extract the first element (assuming there is only one object in the array)
	TSharedPtr<FJsonObject> DataTableObject = RootArray[0]->AsObject();
	if (!DataTableObject.IsValid()) {
		UE_LOG(LogTemp, Error, TEXT("First object in array is invalid."));
		return nullptr;
	}

	return DataTableObject;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSBEditorToolsModule, SBEditorTools)