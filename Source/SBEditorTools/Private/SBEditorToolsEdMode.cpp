// Copyright Epic Games, Inc. All Rights Reserved.

#include "SBEditorToolsEdMode.h"
#include "SBEditorToolsEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"

const FEditorModeID FSBEditorToolsEdMode::EM_SBEditorToolsEdModeId = TEXT("EM_SBEditorToolsEdMode");

FSBEditorToolsEdMode::FSBEditorToolsEdMode()
{

}

FSBEditorToolsEdMode::~FSBEditorToolsEdMode()
{

}

void FSBEditorToolsEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FSBEditorToolsEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
}

void FSBEditorToolsEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}

	// Call base Exit method to ensure proper cleanup
	FEdMode::Exit();
}

bool FSBEditorToolsEdMode::UsesToolkits() const
{
	return true;
}




