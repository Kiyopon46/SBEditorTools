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
    TArray<TSharedPtr<FSBDataTableImporter>> ImporterArray = FSBDataTableImporterFactory().GetInstanceArray();

    for (const TSharedPtr<FSBDataTableImporter>& Importer : ImporterArray)
    {
        FSBMenuEntry MenuEntry = Importer->GetMenuEntry();
        MenuBuilder.AddMenuEntry(
            MenuEntry.Label,
            MenuEntry.Tooltip,
            FSlateIcon(),
            FUIAction(FExecuteAction::CreateLambda(MenuEntry.Callback))
        );
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSBEditorToolsModule, SBEditorTools)