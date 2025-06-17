// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSBEditorToolsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
    void AddMenuBarMenu(class FMenuBarBuilder& MenuBarBuilder);
    void GenerateSBToolsMenu(class FMenuBuilder& MenuBuilder);
    void GenerateDataTableMenu(class FMenuBuilder& MenuBuilder);
    void OnCharacterTableClicked();

    UDataTable* GetExistingTable(const FString& PackagePath);
    FString GetJsonFilePath();
    TSharedPtr<FJsonObject> LoadJsonRows(const FString& FilePath);
    UDataTable* CreateDataTable(const FString& PackagePath);
    void PopulateDataTable(UDataTable* Table, const TSharedPtr<FJsonObject>& RowsObject);

    void TryApplyStringField(
        const TSharedPtr<FJsonObject>& JsonObject,
        const FString& Key,
        const FString& RowName,
        TFunction<void(const FString&)> Setter);
    void TryApplyIntField(
        const TSharedPtr<FJsonObject>& JsonObject,
        const FString& Key,
        const FString& RowName,
        TFunction<void(int32)> Setter);
    void TryApplyFloatField(
        const TSharedPtr<FJsonObject>& JsonObject,
        const FString& Key,
        const FString& RowName,
        TFunction<void(float)> Setter);
    void TryApplyStringArrayField(
        const TSharedPtr<FJsonObject>& JsonObject,
        const FString& Key,
        const FString& RowName,
        TFunction<void(const TArray<FString>&)> Setter);
    void TryApplyBoolField(
        const TSharedPtr<FJsonObject>& JsonObject,
        const FString& Key,
        const FString& RowName,
        TFunction<void(bool)> Setter);

    void SaveDataTableAsset(
        UDataTable* DataTable, const FString& PackagePath);

    //void ImportCharacterTable(const FString& JsonPath);
};
