// Copyright 2019 ayumax. All Rights Reserved.
#include "EasyXMLAsyncLoadFromString.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Async/Async.h"
#include "Utils/CustomXMLParser.h"

UEasyXMLAsyncLoadFromString::UEasyXMLAsyncLoadFromString(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

UEasyXMLAsyncLoadFromString* UEasyXMLAsyncLoadFromString::AsyncLoadFromString(UObject* WorldContextObject, const FString& XMLString)
{
	auto Action = NewObject<UEasyXMLAsyncLoadFromString>();
	Action->RegisterWithGameInstance(WorldContextObject);
	Action->_XMLString = XMLString;

	return Action;
}

void UEasyXMLAsyncLoadFromString::Activate()
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			CustomXMLParser parser;
			FString _errorMessage;

			auto rootElement = parser.Parse(_XMLString, _errorMessage);
			
			if (rootElement != nullptr)
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
