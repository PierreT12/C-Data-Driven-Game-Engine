#pragma once
#include "RTTI.h"
#include "json/json.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Forward Declaration of JsonParseMaster
	/// </summary>
	class JsonParseMaster;

	/// <summary>
	/// A Json Parse Helper Class
	/// </summary>
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, RTTI)
		
	public:

		/// <summary>
		/// A Data Wrapper Class
		/// </summary>
		class DataWrapper : public RTTI
		{
			RTTI_DECLARATIONS(DataWrapper, RTTI);

		public:
			friend class JsonParseMaster;
			
			/// <summary>
			/// Virtual Data Wrapper Destructor
			/// </summary>
			virtual ~DataWrapper();

			/// <summary>
			/// A virtual Constructor that creates a new Data Wrapper
			/// </summary>
			/// <returns>The data wrapper that was just created</returns>
			virtual DataWrapper* Create() const = 0;
			
			/// <summary>
			/// Initalizes any special data inside of the Data Wrapper
			/// </summary>
			virtual void Initalize();

			virtual void Cleanup();

			/// <summary>
			/// Returns the Parse Master that owns this Helper
			/// </summary>
			/// <returns> A pointer to the owning Parse Master</returns>
			JsonParseMaster* GetJsonParseMaster();

			/// <summary>
			/// Returns the Depth that the Wrapper is currently at
			/// </summary>
			/// <returns> The current Depth</returns>
			size_t GetDepth() const;


			/// <summary>
			/// Increments the Depth counter in the Wrapper
			/// </summary>
			/// <returns> Returns the updated Depth </returns>
			virtual size_t IncrementDepth();

			/// <summary>
			/// Decrements the Depth counter in the Wrapper
			/// </summary>
			/// <returns> Returns the updated Depth </returns>
			virtual size_t DecrementDepth();


		private:

			/// <summary>
			/// Sets the owner (Json Parse Master) for this Parse Helper
			/// </summary>
			/// <param name="owner"> A Json Parse Master that will own this helper</param>
			void SetJsonParseMaster(JsonParseMaster& owner);

			size_t _currentDepth{ 0 };

			JsonParseMaster* _owner{ nullptr };
		};

		/// <summary>
		/// Virtual Constructor, Creates a new Helper
		/// </summary>
		virtual IJsonParseHelper* Create() const = 0;

		/// <summary>
		/// Virtual Default Destructor
		/// </summary>
		virtual ~IJsonParseHelper() = default;

		/// <summary>
		/// Initalizes the Helper
		/// </summary>
		virtual void Initalize();

		virtual void Cleanup();

		/// <summary>
		/// Virtual Start Handler, Starts the Parsing in the Helper
		/// </summary>
		/// <param name="sharedData"> The Wrapper that will have the data put into it</param>
		/// <param name="key"> The key assoicated with the value that is being put into the Wrapper</param>
		/// <param name="value"> The data that will be put into the wrapper</param>
		/// <returns> True/False depending on if the data was parsed or not</returns>
		virtual bool StartHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, const Json::Value& value, int32_t index = 0) = 0;
		
		/// <summary>
		/// Virtual End Handler, Ends the Parsing in the Helper
		/// </summary>
		/// <param name="sharedData"> The Wrapper that will have the data put into it</param>
		/// <param name="key"> The key assoicated with the value that is being put into the Wrapper</param>
		/// <param name="isArray"> If the data that was put into the wrapper was an array or not</param>
		/// <returns> True/False depending of if the parse was ended correctly</returns>
		virtual bool EndHandler(IJsonParseHelper::DataWrapper& sharedData, const std::string& key, bool isArray) = 0;

	private:

		bool _isParsing{ false };

		JsonParseMaster* _owner{ nullptr };
	};

}


