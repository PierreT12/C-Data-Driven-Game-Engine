#pragma once
#include "JsonParseMaster.h"
#include "IJsonParseHelper.h"


using namespace FieaGameEngine;

namespace FooSupport
{
	class JsonParseHelperInt final : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonParseHelperInt, IJsonParseHelper)
	public:
		class DataWrapper final : public IJsonParseHelper::DataWrapper
		{
			RTTI_DECLARATIONS(DataWrapper, IJsonParseHelper::DataWrapper)
		public:
			virtual ~DataWrapper() = default;
			virtual DataWrapper* Create() const override;

			virtual size_t IncrementDepth() override;

			std::string ToString() const override;
			bool Equals(const RTTI* rhs) const override;

			Vector<int32_t> Data;

			size_t DeepestDepth{ 0 };

		};

		std::string ToString() const override;

		bool Equals(const RTTI* rhs) const override;
		virtual ~JsonParseHelperInt() = default;
		virtual JsonParseHelperInt* Create() const override;
		virtual void Initalize() override;

		
		virtual bool StartHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, const Json::Value& value, int32_t index = 0) override;
		virtual bool EndHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, bool isArray) override;

		
		bool isInitalized{ false };

		size_t StartHandlerCalls{ 0 };
		size_t EndHandlerCalls{ 0 };
		

	

		



	private:
		inline static const std::string IntKey = "integer";
		bool isParsing{ false };
	};

}

