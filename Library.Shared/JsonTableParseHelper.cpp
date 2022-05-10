#pragma once
#include "pch.h"
#include "JsonTableParseHelper.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonTableParseHelper)
	RTTI_DEFINITIONS(JsonTableParseHelper::DataWrapper)

	void JsonTableParseHelper::Initalize()
	{
		IJsonParseHelper::Initalize();

		_datumStrings.Insert(std::pair<std::string, DatumTypes>("integer", DatumTypes::INT));
		_datumStrings.Insert(std::pair<std::string, DatumTypes>(std::string("float"), DatumTypes::FLOAT));
		_datumStrings.Insert(std::pair<std::string, DatumTypes>(std::string("vec4"), DatumTypes::VEC4));
		_datumStrings.Insert(std::pair<std::string, DatumTypes>(std::string("mat4"), DatumTypes::MAT4));
		_datumStrings.Insert(std::pair<std::string, DatumTypes>(std::string("string"), DatumTypes::STRING));
		_datumStrings.Insert(std::pair<std::string, DatumTypes>(std::string("table"), DatumTypes::TABLE));

		isInitalized = true;
	}

	void JsonTableParseHelper::Cleanup()
	{
		IJsonParseHelper::Cleanup();
		_stack.ClearList();
		_datumStrings.ClearList();
	}

	void JsonTableParseHelper::DataWrapper::Initalize()
	{
		IJsonParseHelper::DataWrapper::Initalize();

		if (_currentContext == nullptr)
		{
			_currentContext = new GameObject();
		}
		
		
		
	}

	void JsonTableParseHelper::DataWrapper::Cleanup()
	{
		IJsonParseHelper::DataWrapper::Cleanup();

		if (_currentContext != nullptr)
		{
			delete _currentContext;
		}
	}


	bool JsonTableParseHelper::StartHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, const Json::Value& value, int32_t index)
	{
		JsonTableParseHelper::DataWrapper* customWrapper = sharedData.As<JsonTableParseHelper::DataWrapper>();

		if (customWrapper == nullptr)
		{
			return false;
		}

		if (key.empty())
		{
			return false;
		}

		if (_stack.Size() == 0)
		{
			_stack.PushBack({ "root" , "null",  (customWrapper->_currentContext), nullptr});
		}

		if (value.isObject() && key != valueKey)
		{
			DatumSetUpLoop(key, value);
		}
		else
		{
			if (value.size() == 0 && key == valueKey)
			{
				DatumExternalCheck(const_cast<Json::Value&>(value), index);
			}
			isParsing = true;
		}
		
		customWrapper->IncrementDepth();
			
		return isParsing;
	}



	DatumTypes JsonTableParseHelper::StringToDatumTypes(const std::string& str) const
	{
		auto [it, found, index] = _datumStrings.Find(str);

		if (!found)
		{
			throw std::runtime_error("Error Getting your Datum Type :{");
		}

		return it->second;
	}
	
	void JsonTableParseHelper::SetUpDatums(const std::string& key, const Json::Value& value, StackFrame& stackFrame)
	{
		DatumTypes datumType = StringToDatumTypes(value.asString());

		if (_stack.Back()._context == nullptr)
		{
			throw std::runtime_error("Error: Stack Context is null :{");
		}

		Datum* tempDatum = &(_stack.Back()._context->Append(key));
		tempDatum->SetType(datumType);
		stackFrame._datum = tempDatum;

		if (datumType == DatumTypes::TABLE)
		{
			Scope* tempScope = Factory<Scope>::Create(stackFrame._class);
			assert(tempScope != nullptr);
			_stack.Back()._context->Adopt(key, *tempScope);
			stackFrame._context = tempScope;

		}
		else
		{
			stackFrame._context = _stack.Back()._context;
		}

		_stack.PushBack(stackFrame);
		
	}

	void JsonTableParseHelper::DatumExternalCheck(Json::Value& value, int32_t index)
	{
		Datum& tempDatum = *_stack.Back()._datum;

		if (tempDatum.IsExternal())
		{
			tempDatum.SetFromString(value.asString(), index);
		}
		else
		{
			tempDatum.PushBackFromString(value.asString());
		}

	}

	bool JsonTableParseHelper::EndHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, bool isArray)
	{
		JsonTableParseHelper::DataWrapper* customWrapper = sharedData.As<JsonTableParseHelper::DataWrapper>();
		
		if (customWrapper == nullptr || key.empty() || (isParsing == false && !isArray && key == typeKey))
		{
			throw std::runtime_error("Error ending your parse :{");
		}

		if (&key == &_stack.Back()._name)
		{
			_stack.PopBack();
		}
		
		customWrapper->DecrementDepth();
		isParsing = false;
		return isParsing;
	}


	JsonTableParseHelper::DataWrapper* JsonTableParseHelper::DataWrapper::Create() const
	{
		return new DataWrapper();
	}

	std::string JsonTableParseHelper::DataWrapper::ToString() const
	{
		return std::string("JsonTableParseHelper's DataWrapper!! :D");
	}

	std::string JsonTableParseHelper::ToString() const
	{
		return std::string("JsonTableParseHelper!! :D");
	}

	bool JsonTableParseHelper::Equals(const RTTI* rhs) const
	{
		const JsonTableParseHelper* temp = rhs->As<JsonTableParseHelper>();

		bool equals = true;

		if (this != rhs)
		{
			equals = false;
		}

		if (temp != nullptr)
		{
			if (_stack.Size() != temp->_stack.Size())
			{
				equals = false;
				return equals;
			}
		}

		return equals;
	}

	bool JsonTableParseHelper::DataWrapper::Equals(const RTTI* rhs) const
	{
		const JsonTableParseHelper::DataWrapper* temp = rhs->As<JsonTableParseHelper::DataWrapper>();

		bool equals = false;

		if (this == rhs)
		{
			equals = true;
		}

		if (temp != nullptr)
		{
			if ((temp->_currentContext == _currentContext) && (temp->GetDepth() == GetDepth()))
			{
				equals = true;
			}
		}

		return equals;
	}
	
	JsonTableParseHelper* JsonTableParseHelper::Create() const
	{
		return new JsonTableParseHelper();
	}

	void JsonTableParseHelper::DatumSetUpLoop(const std::string& key, const Json::Value& value)
	{
		auto members = value.getMemberNames();

		StackFrame temp{key};
		size_t index = 0;
		for (; index < value.size(); ++index)
		{
			if (members[index] == classKey)
			{
				temp._class = value[members[index]].asString();	
			}

			if (members[index] == typeKey)
			{
				isParsing = true;
				SetUpDatums(key, value[members[index]], temp);
				break;
			}

		}
	}

	

}


