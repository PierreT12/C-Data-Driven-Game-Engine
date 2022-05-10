#include "pch.h"
#include "JsonParseMaster.h"

namespace FieaGameEngine
{
	JsonParseMaster::JsonParseMaster(IJsonParseHelper::DataWrapper& data):
		_internalWrap{ &data },
		_isCloned{ false }
	{
		_internalWrap->Initalize();
		_internalWrap->SetJsonParseMaster(*this);
	}

	JsonParseMaster::~JsonParseMaster()
	{
		if (_internalWrap != nullptr)
		{
			_internalWrap->Cleanup();
		}

		if (_isCloned)
		{
			delete _internalWrap;
		}

		for (auto& helper : _helpers)
		{
			if (helper != nullptr)
			{
				helper->Cleanup();
				if (_isCloned)
				{
					delete helper;
				}
			}
			
			
		}
	}

	JsonParseMaster::JsonParseMaster(JsonParseMaster&& other):
		_internalWrap{std::move(other._internalWrap)},
		_isCloned{other._isCloned},
		_helpers{std::move(other._helpers)}
	{
		other._helpers.ClearList();
		_internalWrap->_owner = this;
		other._internalWrap = nullptr;
		other._isCloned = false;
	}



	JsonParseMaster& JsonParseMaster::operator=(JsonParseMaster&& other)
	{
		if (this != &other)
		{
			_helpers.ClearList();

			_helpers = std::move(other._helpers);
			_internalWrap = std::move(other._internalWrap);
			_internalWrap->_owner = this;
			_isCloned = other._isCloned;

			other._helpers.ClearList();
			other._internalWrap = nullptr;
			other._isCloned = false;
		}
		return *this;
	}


	JsonParseMaster* JsonParseMaster::Clone() const
	{
		JsonParseMaster* cloned = new JsonParseMaster(*(this->GetDataWrapper()->Create()));
		for (auto& helper : _helpers)
		{
			cloned->AddHelper(*helper->Create());
		}
		cloned->_isCloned = true;

		return cloned;
	}

	void JsonParseMaster::AddHelper(IJsonParseHelper& helper)
	{
		if (_isCloned)
		{
			throw std::runtime_error("Cannont add to a Cloned Object :{");
		}

		_helpers.PushBack(&helper);
		helper.Initalize();
	}

	void JsonParseMaster::RemoveHelper(IJsonParseHelper& helper)
	{
		if (_isCloned)
		{
			throw std::runtime_error("Cannont remove from a Cloned Object :{");
		}

		helper.Cleanup();
		bool removed =_helpers.Remove(&helper);

		if (!removed)
		{
			throw std::runtime_error("Couldn't find this object :{");
		}
	}

	void JsonParseMaster::ParseFromFile(const std::string& fileName)
	{
		std::ifstream file(fileName.c_str());
		Parse(file);
	}

	void JsonParseMaster::Parse(const std::string& data)
	{
		std::istringstream iStream(data);
		Parse(iStream);
	}

	void JsonParseMaster::Parse(std::istream& data)
	{

		Json::Value root;
		data >> root;

		ParseMembers(root);
	}

	IJsonParseHelper::DataWrapper* JsonParseMaster::GetDataWrapper() const
	{
		return _internalWrap;
	}

	void JsonParseMaster::SetDataWrapper(IJsonParseHelper::DataWrapper& data)
	{
		if (_isCloned)
		{
			throw std::runtime_error("Cannont set a Cloned Data Wrapper :{");
		}
		_internalWrap = &data;
		_internalWrap->_owner = this;
	}

	void JsonParseMaster::ParseMembers(const Json::Value& value)
	{
		if (value.size() > 0)
		{
			const auto members = value.getMemberNames();
			for (const auto& names : members)
			{
				if (names == "file")
				{
					ParseFromFile(value[names].asString());
				}
				else
				{
					Parse(names, value[names], value[names].isArray());
				}
			}
		}
		
	}

	void JsonParseMaster::Parse(const std::string& key, const Json::Value& value, bool isArray, int32_t index)
	{
		bool isParsing = false;

		for (const auto helper : _helpers)
		{

			if (value.isObject())
			{
				isParsing = helper->StartHandler(*_internalWrap, key, value, index);

				if (isParsing)
				{
					ParseMembers(value);
				}
			}
			else if (isArray)
			{
				for (Json::ArrayIndex jsonIndex = 0; jsonIndex < value.size(); ++jsonIndex)
				{
					Parse(key, value[jsonIndex], value[jsonIndex].isArray(), jsonIndex);
				}
			}
			else
			{
				isParsing = helper->StartHandler(*_internalWrap, key, value, index);
			}

			if (isParsing)
			{
				helper->EndHandler(*_internalWrap, key, value.isArray());
				
			}
			
		}
		
	}

	
}