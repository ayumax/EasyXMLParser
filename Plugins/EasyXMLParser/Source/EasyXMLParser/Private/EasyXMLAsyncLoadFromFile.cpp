// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyXMLAsyncLoadFromFile.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Async/Async.h"
#include "Utils/CustomXMLParser.h"
#include "EasyXMLParseManager.h"

UEasyXMLAsyncLoadFromFile::UEasyXMLAsyncLoadFromFile(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

UEasyXMLAsyncLoadFromFile* UEasyXMLAsyncLoadFromFile::AsyncLoadFromFile(UObject* WorldContextObject, const FString& FilePath, bool IsAblolute)
{
	auto Action = NewObject<UEasyXMLAsyncLoadFromFile>();
	Action->RegisterWithGameInstance(WorldContextObject);
	Action->_XMLFile = FilePath;
	Action->_IsAblolute = IsAblolute;

	return Action;
}

void UEasyXMLAsyncLoadFromFile::Activate()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			auto manager = NewObject<UEasyXMLParseManager>();
			FString _errorMessage;
			EEasyXMLParserErrorCode _isSuccessed;
			auto rootElement = manager->LoadFromFile(_XMLFile, _IsAblolute, _isSuccessed, _errorMessage);

			if (_isSuccessed == EEasyXMLParserErrorCode::Successed)
			{
				AsyncTask(ENamedThreads::GameThread, [this, rootElement]()
					{
						Successed.Broadcast(rootElement, TEXT(""));
						SetReadyToDestroy();
					});
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [this, _errorMessage]()
					{
						Failed.Broadcast(nullptr, _errorMessage);
						SetReadyToDestroy();
					});
			}

		});
}
