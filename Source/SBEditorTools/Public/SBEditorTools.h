// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Importer/FSBDataTableImporter.h"
#include "Importer/FSBPhotoModeImageTableImporter.h"

class FSBEditorToolsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
    TArray<TPair<FString, TSharedPtr<FSBDataTableImporter>>> CachedImporterArray;

    void AddMenuBarMenu(class FMenuBarBuilder& MenuBarBuilder);
    void GenerateSBToolsMenu(class FMenuBuilder& MenuBuilder);
    void GenerateDataTableMenu(class FMenuBuilder& MenuBuilder);

    void HandleJsonFiles();
    void HandleFolder();

    TArray<FString> SelectJsonFiles();

    TArray<FString> SelectJsonFolder();

    void ProcessAllFiles(TArray<FString> JsonPaths);

    TSharedPtr<FJsonObject> LoadJsonDataTableObject(const FString& FilePath);

    ///**
    // * Main processing called for each handlers.
    // * @param Importer Importer for each DataTable
    // */
    //void Execute(TUniquePtr<FSBDataTableImporter> Importer);

    ///** Check if the file exists */
    //UDataTable* GetExistingTable(const FString& PackagePath);

    ///** Open a dialog to get the JSON file path. */
    //FString GetJsonFilePath();

    ///**
    // * Read the JSON file and get the "Rows" object from it.
    // * The following file formats are supported:
    // * <code>
    // * [
    // *   {
    // *     "Rows": {
    // *       "RowName1": {
    // *         // DataTable structure.
    // *       },
    // *       ...
    // *     }
    // *   }
    // * ]
    // * </code>
    // */
    //TSharedPtr<FJsonObject> LoadJsonRows(const FString& FilePath);

    //UDataTable* CreateDataTable(TUniquePtr<FSBDataTableImporter> Importer);

    //void SaveDataTableAsset(
    //    UDataTable* DataTable, const FString& PackagePath);

    /* Menu Click Handlers for each DataTable here. */

    /** Handler for CharacterTable. */
//    void OnCharacterTableClicked();

    /** Handler for PhotoModeImageTable. */
//    void OnPhotoModeImageTableClicked();

};
