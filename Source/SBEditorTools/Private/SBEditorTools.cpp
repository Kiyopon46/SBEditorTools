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

#include "Importer/FSBDataTableImporter.h"

// Add the DataTable Importer here.
#include "Importer/FSBCharacterTableImporter.h" // SBCharacterTableProperty

#define LOCTEXT_NAMESPACE "FSBEditorToolsModule"

void FSBEditorToolsModule::StartupModule()
{
	// Register Menu Extension
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuBarExtension("Window", EExtensionHook::After, nullptr,
		FMenuBarExtensionDelegate::CreateRaw(this, &FSBEditorToolsModule::AddMenuBarMenu));

	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
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
    // Menu for CharacterTable
    MenuBuilder.AddMenuEntry(
        LOCTEXT("CharacterTableEntry", "CharacterTable"),
        LOCTEXT("CharacterTableEntry_Tooltip", "Run CharacterTable tool"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FSBEditorToolsModule::OnCharacterTableClicked))
    );
}

void FSBEditorToolsModule::OnCharacterTableClicked()
{
    UE_LOG(LogTemp, Log, TEXT("OnCharacterTableClicked Start."));
    TUniquePtr<FSBDataTableImporter> Importer = MakeUnique<FSBCharacterTableImporter>();
    Execute(MoveTemp(Importer));
    UE_LOG(LogTemp, Log, TEXT("OnCharacterTableClicked End."));
}

void FSBEditorToolsModule::Execute(TUniquePtr<FSBDataTableImporter> Importer)
{
    if (!Importer.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Importer is invalid"));
        return;
    }

    FString PackagePath = Importer->GetPackagePath();

    // Check if the file exists
    UDataTable* ExistingTable = GetExistingTable(PackagePath);

    // If the file exists, confirm overwriting
    if (ExistingTable)
    {
        FText DialogText = FText::FromString(TEXT("The DataTable already exists. Do you want to overwrite it?"));
        EAppReturnType::Type Result = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

        if (Result == EAppReturnType::No)
        {
            UE_LOG(LogTemp, Log, TEXT("User chose not to overwrite the existing DataTable."));
            return;
        }

        // Delete first if it's okay to overwrite.
        if (ExistingTable)
        {
            FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
            AssetRegistryModule.Get().AssetDeleted(ExistingTable);
            ExistingTable->MarkPendingKill();
            ExistingTable->GetOutermost()->MarkPackageDirty();
            ExistingTable->ConditionalBeginDestroy();
        }
    }

    FString JsonPath = GetJsonFilePath();
    if (JsonPath.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("GetJsonFilePath() failed."));
        return;
    }

    TSharedPtr<FJsonObject> RowsObject = LoadJsonRows(JsonPath);
    if (!RowsObject.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("LoadJsonRows() failed."));
        return;
    }

    UDataTable* TargetTable = CreateDataTable(MoveTemp(Importer));
    if (!TargetTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("CreateCharacterDataTable() failed."));
        return;
    }

    // Read data from JSON and set it in a DataTable.
    Importer->PopulateDataTable(TargetTable, RowsObject);

    SaveDataTableAsset(TargetTable, PackagePath);
}

UDataTable* FSBEditorToolsModule::GetExistingTable(const FString& PackagePath)
{
    UObject* ExistingAsset = LoadObject<UObject>(nullptr, *PackagePath);
    UDataTable* ExistingTable = Cast<UDataTable>(ExistingAsset);

    return ExistingTable;
}

FString FSBEditorToolsModule::GetJsonFilePath()
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (!DesktopPlatform)
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Desktop platform not available.")));
        return FString(TEXT(""));
    }

    const void* ParentWindowHandle = nullptr;
    if (FSlateApplication::IsInitialized())
    {
        TSharedPtr<SWindow> ParentWindow = nullptr;
        ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(ParentWindow);
    }

    TArray<FString> OutFiles;
    bool bOpened = DesktopPlatform->OpenFileDialog(
        ParentWindowHandle,
        TEXT("Select JSON File"),
        FPaths::ProjectContentDir(),
        TEXT(""),
        TEXT("JSON files (*.json)|*.json"),
        EFileDialogFlags::None,
        OutFiles
    );

    if (!bOpened || OutFiles.Num() == 0) {
        UE_LOG(LogTemp, Warning, TEXT("!bOpened || OutFiles.Num() == 0 failed."));
        return FString(TEXT(""));
    }

    FString FilePath = OutFiles[0];

    return FilePath;
}

TSharedPtr<FJsonObject> FSBEditorToolsModule::LoadJsonRows(const FString& FilePath)
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

    // Get "Rows" Object
    const TSharedPtr<FJsonObject>* RowsObjectPtr = nullptr;
    if (!DataTableObject->TryGetObjectField(TEXT("Rows"), RowsObjectPtr) || !RowsObjectPtr) {
        UE_LOG(LogTemp, Error, TEXT("Rows field missing or invalid."));
        return nullptr;
    }

    return *RowsObjectPtr;
}

UDataTable* FSBEditorToolsModule::CreateDataTable(TUniquePtr<FSBDataTableImporter> Importer)
{
    // Create Package and DataTable
    FString PackagePath = Importer->GetPackagePath();
    UPackage* Package = CreatePackage(*PackagePath);
    UDataTable* DataTable = NewObject<UDataTable>(Package, *FPaths::GetBaseFilename(PackagePath), RF_Public | RF_Transactional | RF_Standalone);
    DataTable->RowStruct = FSBCharacterTableProperty::StaticStruct();

    return DataTable;
}

void FSBEditorToolsModule::SaveDataTableAsset(UDataTable* DataTable, const FString& PackagePath)
{
    if (!DataTable || PackagePath.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("SaveDataTableAsset: Invalid DataTable or PackagePath."));
        return;
    }

    // Register the asset
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    AssetRegistryModule.Get().AssetCreated(DataTable);

    // Mark as dirty
    DataTable->MarkPackageDirty();

    // Convert to full file path
    FString PackageFilePath = FPackageName::LongPackageNameToFilename(PackagePath, FPackageName::GetAssetPackageExtension());

    // Get the outer package from the DataTable
    UPackage* Package = DataTable->GetOutermost();

    if (!Package)
    {
        UE_LOG(LogTemp, Warning, TEXT("SaveDataTableAsset: Failed to get outermost package."));
        return;
    }

    // Save the package
    bool bSuccess = UPackage::SavePackage(
        Package,
        DataTable,
        EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
        *PackageFilePath,
        GError,
        nullptr,
        true,
        true,
        SAVE_None
    );

    if (bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("DataTable saved successfully to %s"), *PackageFilePath);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to save DataTable to %s"), *PackageFilePath);
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSBEditorToolsModule, SBEditorTools)