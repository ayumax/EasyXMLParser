// Copyright 2019 ayumax. All Rights Reserved.
#include "Misc/AutomationTest.h"
#include "EasyXMLParseManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FReadValueTest_Int, "EasyXMLParser.ReadValueTest.Int", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FReadValueTest_Int::RunTest(const FString& Parameters)
{
	// parse success
	{
		FString xmlString = TEXT("<root>\r")
								TEXT("<!-- comment desu -->\r")
								TEXT("<abc attr1=\"10\" attr2=\"false\">\r")								
									TEXT("123\r")
								TEXT("</abc>\r")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);
		
		TestEqual(TEXT("success read int"), rootNode->ReadInt("root.abc", isSuccess), 123);
		TestEqual(TEXT("success read int"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("-123")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);

		TestEqual(TEXT("success read int"), rootNode->ReadInt("root.abc", isSuccess), -123);
		TestEqual(TEXT("success read int"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123456789")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read int"), rootNode->ReadInt("root.abc", isSuccess), 123456789);
		TestEqual(TEXT("success read int"), isSuccess, true);
	}


	// parse ng(string)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read int(string)"), rootNode->ReadInt("root.abc", isSuccess), 0);
		TestEqual(TEXT("ng read int(string)"), isSuccess, false);
	}

	// parse ng(float)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("3.14")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read int(float)"), rootNode->ReadInt("root.abc", isSuccess), 0);
		TestEqual(TEXT("ng read int(float)"), isSuccess, false);
	}

	// parse ng(xml)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("<def>")
										TEXT("123")
									TEXT("</def>")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read int(xml)"), rootNode->ReadInt("root.abc", isSuccess), 0);
		TestEqual(TEXT("ng read int(xml)"), isSuccess, false);
	}
	

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FReadValueTest_Float, "EasyXMLParser.ReadValueTest.Float", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FReadValueTest_Float::RunTest(const FString& Parameters)
{
	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("1.23")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat("root.abc", isSuccess), 1.23f);
		TestEqual(TEXT("success read float"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("-1.23")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat("root.abc", isSuccess), -1.23);
		TestEqual(TEXT("success read float"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123.456789")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat("root.abc", isSuccess), 123.456789);
		TestEqual(TEXT("success read float"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat("root.abc", isSuccess), 123.0f);
		TestEqual(TEXT("success read float"), isSuccess, true);
	}


	// parse ng(string)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read float(string)"), rootNode->ReadFloat("root.abc", isSuccess), 0.0f);
		TestEqual(TEXT("ng read float(string)"), isSuccess, false);
	}

	// parse ng(xml)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("<def>")
										TEXT("1.23")
									TEXT("</def>")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read float(xml)"), rootNode->ReadFloat("root.abc", isSuccess), 0.0f);
		TestEqual(TEXT("ng read float(xml)"), isSuccess, false);
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FReadValueTest_Bool, "EasyXMLParser.ReadValueTest.Bool", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FReadValueTest_Bool::RunTest(const FString& Parameters)
{
	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("True")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool("root.abc", isSuccess), true);
		TestEqual(TEXT("success read bool"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("tRue")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool("root.abc", isSuccess), true);
		TestEqual(TEXT("success read bool"), isSuccess, true);
	}
	
	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("False")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool("root.abc", isSuccess), false);
		TestEqual(TEXT("success read bool"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("fAlse")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool("root.abc", isSuccess), false);
		TestEqual(TEXT("success read bool"), isSuccess, true);
	}


	// parse ng(string)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read bool(string)"), rootNode->ReadBool("root.abc", isSuccess), false);
		TestEqual(TEXT("ng read bool(string)"), isSuccess, false);
	}

	// parse ng(xml)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("<def>")
										TEXT("true")
									TEXT("</def>")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read bool(xml)"), rootNode->ReadBool("root.abc", isSuccess), false);
		TestEqual(TEXT("ng read bool(xml)"), isSuccess, false);
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FReadValueTest_String, "EasyXMLParser.ReadValueTest.String", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FReadValueTest_String::RunTest(const FString& Parameters)
{
	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString("root.abc", isSuccess), TEXT("text"));
		TestEqual(TEXT("success read string"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString("root.abc", isSuccess), TEXT("123"));
		TestEqual(TEXT("success read string"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("1.23")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString("root.abc", isSuccess), TEXT("1.23"));
		TestEqual(TEXT("success read string"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("true")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString("root.abc", isSuccess), TEXT("true"));
		TestEqual(TEXT("success read string"), isSuccess, true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("false")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString("root.abc", isSuccess), TEXT("false"));
		TestEqual(TEXT("success read string"), isSuccess, true);
	}

	// parse ng(xml)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("<def>")
										TEXT("text")
									TEXT("</def>")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		bool isSuccess;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);

		TestEqual(TEXT("success read string"), rootNode->ReadString("root.abc", isSuccess), TEXT(""));
		TestEqual(TEXT("success read string"), isSuccess, true);
	}

	return true;
}