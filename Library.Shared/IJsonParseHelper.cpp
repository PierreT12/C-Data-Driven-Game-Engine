#include "pch.h"
#include "IJsonParseHelper.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(IJsonParseHelper)
	RTTI_DEFINITIONS(IJsonParseHelper::DataWrapper)

		
	void IJsonParseHelper::Initalize()
	{
		_isParsing = false;
	}

	void IJsonParseHelper::Cleanup() {}

	void IJsonParseHelper::DataWrapper::Initalize() {}

	void IJsonParseHelper::DataWrapper::Cleanup() {}

	IJsonParseHelper::DataWrapper::~DataWrapper()
	{
		_owner = nullptr;
	}

	JsonParseMaster* IJsonParseHelper::DataWrapper::GetJsonParseMaster()
	{
		return _owner;
	}

	size_t IJsonParseHelper::DataWrapper::GetDepth() const
	{
		return DataWrapper::_currentDepth;
	}

	size_t IJsonParseHelper::DataWrapper::IncrementDepth()
	{
		return ++DataWrapper::_currentDepth;
	}

	size_t IJsonParseHelper::DataWrapper::DecrementDepth()
	{
		if (DataWrapper::_currentDepth > 0)
		{
			--DataWrapper::_currentDepth;
		}
		return DataWrapper::_currentDepth;
	}


	void IJsonParseHelper::DataWrapper::SetJsonParseMaster(JsonParseMaster& owner)
	{
		_owner = &owner;
	}
}