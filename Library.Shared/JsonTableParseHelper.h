#pragma once
#include "JsonParseMaster.h"
#include "IJsonParseHelper.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Json Table Parser Helper Class
	/// </summary>
	class JsonTableParseHelper final : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonTableParseHelper, IJsonParseHelper)
	public:

		/// <summary>
		/// Data Wrapper Class for Json Table Parse Helper
		/// </summary>
		class DataWrapper final : public IJsonParseHelper::DataWrapper
		{
			RTTI_DECLARATIONS(DataWrapper, IJsonParseHelper::DataWrapper)
		public:

			/// <summary>
			/// Default Virtual Destructor
			/// </summary>
			virtual ~DataWrapper() = default;

			/// <summary>
			/// Create Override, Creates a new Data Wrapper
			/// </summary>
			/// <returns> A pointer to the new Data Wrapper Created</returns>
			virtual DataWrapper* Create() const override;

			/// <summary>
			/// Initalize Override, Initalizes the Data Wrapper
			/// </summary>
			virtual void Initalize() override;

			/// <summary>
			/// Cleanup Override, Cleans up the Data Wrapper
			/// </summary>
			virtual void Cleanup() override;

			/// <summary>
			/// To String Override
			/// </summary>
			/// <returns>Returns a String</returns>
			std::string ToString() const override;

			/// <summary>
			/// Equals Override
			/// </summary>
			/// <param name="rhs"> The other RTTI Object that this will be compared to</param>
			/// <returns> True/False Depending on if they are equal or not</returns>
			bool Equals(const RTTI* rhs) const override;

			Scope* _currentContext;

		};

		/// <summary>
		/// To String Override
		/// </summary>
		/// <returns>Returns a String</returns>
		std::string ToString() const override;

		/// <summary>
		/// Equals Override
		/// </summary>
		/// <param name="rhs"> The other RTTI Object that this will be compared to</param>
		/// <returns> True/False Depending on if they are equal or not</returns>
		bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Default Virtual Destructor
		/// </summary>
		virtual ~JsonTableParseHelper() = default;

		/// <summary>
		/// Create Override, Creates a new Json Table Parse Helper
		/// </summary>
		/// <returns> A pointer to the new Json Table Parse Helper Created</returns>
		virtual JsonTableParseHelper* Create() const override;

		/// <summary>
		/// Initalize Override, Initalizes the Json Table Parse Helper
		/// </summary>
		virtual void Initalize() override;

		/// <summary>
		/// Cleanup Override, Cleans up the Json Table Parse Helper
		/// </summary>
		virtual void Cleanup() override;

		/// <summary>
		/// Start Handler, Starts the Parsing in the Helper
		/// </summary>
		/// <param name="sharedData"> The Wrapper that will have the data put into it</param>
		/// <param name="key"> The key assoicated with the value that is being put into the Wrapper</param>
		/// <param name="value"> The data that will be put into the wrapper</param>
		/// <returns> True/False depending on if the data was parsed or not</returns>
		virtual bool StartHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, const Json::Value& value, int32_t index = 0) override;
		
		/// <summary>
		/// End Handler, Ends the Parsing in the Helper
		/// </summary>
		/// <param name="sharedData"> The Wrapper that will have the data put into it</param>
		/// <param name="key"> The key assoicated with the value that is being put into the Wrapper</param>
		/// <param name="isArray"> If the data that was put into the wrapper was an array or not</param>
		/// <returns> True/False depending of if the parse was ended correctly</returns>
		virtual bool EndHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, bool isArray) override;


		bool isInitalized{ false };

	private:


		struct StackFrame
		{
			const std::string& _name;
			std::string _class{ "Scope" };
			Scope* _context{ nullptr };
			Datum* _datum{ nullptr };
		};

		DatumTypes StringToDatumTypes(const std::string& str) const;

		void SetUpDatums(const std::string& key, const Json::Value& value, StackFrame& stackFrame);

		void DatumSetUpLoop(const std::string& key, const Json::Value& value);

		void DatumExternalCheck(Json::Value& value, int32_t index);

		inline static const std::string typeKey = "type";
		inline static const std::string valueKey = "value";
		inline static const std::string classKey = "class";
		bool isParsing{ false };
		std::string _classTemp;
		SList<StackFrame> _stack;
		HashMap<std::string, DatumTypes> _datumStrings;


		
	};

}


