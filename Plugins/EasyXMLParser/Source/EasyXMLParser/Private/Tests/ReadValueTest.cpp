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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);
		
		TestEqual(TEXT("success read int"), rootNode->ReadInt(TEXT("root.abc"), 0), 123);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("-123")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);

		TestEqual(TEXT("success read int"), rootNode->ReadInt(TEXT("root.abc"), 0), -123);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123456789")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read int"), rootNode->ReadInt(TEXT("root.abc"), 0), 123456789);
	}


	// parse ng(string)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read int(string)"), rootNode->ReadInt(TEXT("root.abc"), 0), 0);
	}

	// parse ng(float)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("3.14")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read int(float)"), rootNode->ReadInt(TEXT("root.abc"), 0), 0);
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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read int(xml)"), rootNode->ReadInt(TEXT("root.abc"), 0), 0);
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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat(TEXT("root.abc"), 0), 1.23f);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("-1.23")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat(TEXT("root.abc"), 0), -1.23f);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123.456789")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat(TEXT("root.abc"), 0), 123.456789f);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read float"), rootNode->ReadFloat(TEXT("root.abc"), 0), 123.0f);
	}


	// parse ng(string)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read float(string)"), rootNode->ReadFloat(TEXT("root.abc"), 0), 0.0f);
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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read float(xml)"), rootNode->ReadFloat(TEXT("root.abc"), 0), 0.0f);
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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool(TEXT("root.abc"), false), true);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("tRue")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool(TEXT("root.abc"), false), true);
	}
	
	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("False")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool(TEXT("root.abc"), true), false);
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("fAlse")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read bool"), rootNode->ReadBool(TEXT("root.abc"), true), false);
	}


	// parse ng(string)
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("text")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read bool(string)"), rootNode->ReadBool(TEXT("root.abc"), false), false);
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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("ng read bool(xml)"), rootNode->ReadBool(TEXT("root.abc"), false), false);
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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString(TEXT("root.abc"), TEXT("")), TEXT("text"));
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("123")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString(TEXT("root.abc"), TEXT("")), TEXT("123"));
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("1.23")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString(TEXT("root.abc"), TEXT("")), TEXT("1.23"));
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("true")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString(TEXT("root.abc"), TEXT("")), TEXT("true"));
	}

	// parse success
	{
		FString xmlString = TEXT("<root>")
								TEXT("<abc>")
									TEXT("false")
								TEXT("</abc>")
							TEXT("</root>");

		EEasyXMLParserErrorCode result;
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);


		TestEqual(TEXT("success read string"), rootNode->ReadString(TEXT("root.abc"), TEXT("")), TEXT("false"));
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
		FString errorMessage;
		auto rootNode = UEasyXMLParseManager::LoadFromString(xmlString, result, errorMessage);

		TestEqual(TEXT("success read string"), rootNode->ReadString(TEXT("root.abc"), TEXT("")), TEXT(""));
	}

	return true;
}