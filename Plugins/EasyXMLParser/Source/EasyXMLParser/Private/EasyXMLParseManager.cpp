// Copyright 2019 ayumax. All Rights Reserved.

#include "EasyXMLParseManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "EasyXMLElement.h"
#include "Utils/CustomXMLParser.h"


UEasyXMLElement* UEasyXMLParseManager::LoadFromString(const FString& XMLString, EEasyXMLParserErrorCode& Result, FString& ErrorMessage)
{
	CustomXMLParser parser;
	FString _errorMessage;

	auto rootElement = parser.Parse(XMLString, _errorMessage);
	Result = rootElement != nullptr ? EEasyXMLParserErrorCode::Successed : EEasyXMLParserErrorCode::Failed;
	ErrorMessage = _errorMessage;

	return rootElement;
}

UEasyXMLElement* UEasyXMLParseManager::LoadFromFile(const FString& FilePath, bool IsAblolute, EEasyXMLParserErrorCode& Result, FString& ErrorMessage)
{
	auto readPath = FilePath;
	if (!IsAblolute)
	{
		readPath = FPaths::Combine(FPaths::ProjectContentDir(), FilePath);
	}

	if (!FPaths::FileExists(readPath)) return nullptr;

	FString xmlString;

	FFileHelper::LoadFileToString(xmlString, *readPath);

	return LoadFromString(xmlString, Result, ErrorMessage);
}
