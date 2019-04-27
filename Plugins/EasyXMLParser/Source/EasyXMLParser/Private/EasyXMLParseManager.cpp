// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyXMLParseManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "EasyXMLObject.h"



UEasyXMLObject* UEasyXMLParseManager::LoadFromString(const FString& XMLString)
{
	return UEasyXMLObject::CreateEasyXMLObject(XMLString);
}

UEasyXMLObject* UEasyXMLParseManager::LoadFromFile(const FString& FilePath, bool IsAblolute)
{
	auto readPath = FilePath;
	if (!IsAblolute)
	{
		readPath = FPaths::Combine(FPaths::ProjectLogDir(), FilePath);
	}

	if (!FPaths::FileExists(readPath)) return nullptr;

	FString xmlString;

	FFileHelper::LoadFileToString(xmlString, *readPath);

	return LoadFromString(xmlString);
}
