#pragma once
#include <fstream>
#include "json/json.h"
#include "GameObject.h"
#include "IJsonParseHelper.h"

namespace FieaGameEngine
{
	
	/// <summary>
	/// A Json Parse Master
	/// </summary>
	class JsonParseMaster final
	{
	public:

		/// <summary>
		/// Constructor that takes in a Data Wrapper
		/// </summary>
		/// <param name="data"> The Data Wrapper where the Parsed Data will be placed into</param>
		JsonParseMaster(IJsonParseHelper::DataWrapper& data);
		
		/// <summary>
		/// Default Destructor
		/// </summary>
		~JsonParseMaster();

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other"> The Parse Master that will be moved </param>
		JsonParseMaster(JsonParseMaster&& other);

		/// <summary>
		/// Move Assignment
		/// </summary>
		/// <param name="other"> The Parse Master that will be mvoed </param>
		/// <returns> The moved Parse Master </returns>
		JsonParseMaster& operator=(JsonParseMaster&& other);

		/// <summary>
		/// Copying via Cloning Method
		/// </summary>
		/// <returns> The new Parse Master </returns>
		JsonParseMaster* Clone() const;

		/// <summary>
		/// Adds a Helper to this Parse Master's Helper List
		/// </summary>
		/// <param name="helper"> A ref to the helper that will be added to the Helper List</param>
		void AddHelper(IJsonParseHelper& helper);

		// <summary>
		/// Removeds a Helper from this Parse Master's Helper List
		/// </summary>
		/// <param name="helper"> A ref to the helper that will be removed from the Helper List</param>
		void RemoveHelper(IJsonParseHelper& helper);

		void ParseFromFile(const std::string& fileName);

		/// <summary>
		/// Parses the given string into the Data Wrapper in this Parse Master
		/// </summary>
		/// <param name="data"> The String of Json Data that will be parsed</param>
		void Parse(const std::string& data);

		/// <summary>
		/// Parses the given Istream into the Data Wrapper in this Parse Master
		/// </summary>
		/// <param name="data"> The Istream of Json Data that will be parsed</param>
		void Parse(std::istream& data);

		/// <summary>
		/// Gets the Data Wrapper assoicated with this Parse Master
		/// </summary>
		/// <returns> A pointer to the Data Wrapper in this Parse Master</returns>
		IJsonParseHelper::DataWrapper* GetDataWrapper() const;

		/// <summary>
		/// Takes the given Data Wrapper and assoicates it with this class
		/// </summary>
		/// <param name="data"> The Data wrapper that will now be assoicated with this class</param>
		void SetDataWrapper(IJsonParseHelper::DataWrapper& data);


	private:

		/// <summary>
		/// Parses Each Object Member of a Json Object
		/// </summary>
		/// <param name="value"> The Json Object that will be parsed</param>
		void ParseMembers(const Json::Value& value);

		/// <summary>
		/// Parses a String/Value pair
		/// </summary>
		/// <param name="key"> The key that is needed to find the correct Parse Helper</param>
		/// <param name="value"> The value that will be parsed</param>
		/// <param name="isArray"> True/False depending on if the value is an array or not</param>
		void Parse(const std::string& key, const Json::Value& value, bool isArray, int32_t index = 0);

		Vector<IJsonParseHelper*> _helpers;

		//const std::string fileKey = "file";

		IJsonParseHelper::DataWrapper* _internalWrap;

		bool _isCloned;

	};

}