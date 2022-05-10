#include "pch.h"
#include "JsonParseHelperInt.h"

namespace FooSupport
{
	RTTI_DEFINITIONS(JsonParseHelperInt)
	RTTI_DEFINITIONS(JsonParseHelperInt::DataWrapper)
	void JsonParseHelperInt::Initalize()
	{
		FieaGameEngine::IJsonParseHelper::Initalize();
		isInitalized = true;
	}


	bool JsonParseHelperInt::StartHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, const Json::Value& value, int32_t index)
	{
		
		JsonParseHelperInt::DataWrapper* customWrapper = sharedData.As<JsonParseHelperInt::DataWrapper>();
		index;

		if (customWrapper == nullptr)
		{
			return false;
		}


		sharedData.IncrementDepth();
		++StartHandlerCalls;

		if (key != IntKey)
		{
			return false;
		}

		if (isParsing)
		{
			throw std::runtime_error("Already parsing an integer right now :{");
		}

		isParsing = true;

	
		customWrapper->Data.PushBack(value.asInt());
		

		return true;

	}
	JsonParseHelperInt* JsonParseHelperInt::Create() const
	{
		return new JsonParseHelperInt();
	}

	size_t JsonParseHelperInt::DataWrapper::IncrementDepth()
	{
		IJsonParseHelper::DataWrapper::IncrementDepth();

		DeepestDepth += 1;

		return size_t();
	}


	JsonParseHelperInt::DataWrapper* JsonParseHelperInt::DataWrapper::Create() const
	{
		return new DataWrapper();
	}


	bool JsonParseHelperInt::EndHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, bool isArray)
	{
		
		JsonParseHelperInt::DataWrapper* customWrapper = sharedData.As<JsonParseHelperInt::DataWrapper>();

		

		if (customWrapper == nullptr || key != IntKey || (isParsing == false && !isArray))
		{
			throw std::runtime_error("Error ending your parse :{");
		}

		++EndHandlerCalls;
		sharedData.DecrementDepth();

		isParsing = false;

		return true;
	}
	std::string JsonParseHelperInt::ToString() const
	{
		return std::string("JsonParseHelperInt!!! :D");
	}
	std::string JsonParseHelperInt::DataWrapper::ToString() const
	{
		return std::string("JsonParseHelperInt's DataWrapper!!! :D");
	}



	bool JsonParseHelperInt::Equals(const RTTI* rhs) const
	{
		const JsonParseHelperInt* temp = rhs->As<JsonParseHelperInt>();

		bool equals = false;

		if (this == rhs)
		{
			equals = true;
		}
		
		if (temp != nullptr)
		{
			equals = true;
		}

		return equals;
	}

	bool JsonParseHelperInt::DataWrapper::Equals(const RTTI* rhs) const
	{
		const DataWrapper* temp = rhs->As<JsonParseHelperInt::DataWrapper>();

		bool equals = false;

		if (this == rhs)
		{
			equals = true;
		}

		if (temp != nullptr)
		{
			equals = true;
		}

		return equals;
	}

	

}

