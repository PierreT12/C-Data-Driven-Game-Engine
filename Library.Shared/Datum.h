#pragma once
#include "RTTI.h"
#include "glm\glm.hpp"
#include "DatumTypes.h"

#define MaxChar 160



namespace FieaGameEngine
{
	class Scope;
	/// <summary>
	/// The Strong Enum Class that has all of the different possible datatypes for Datum
	/// </summary>
	

	/// <summary>
	/// A Datum Class
	/// </summary>
	class Datum final
	{
		
	public:
		
		friend class Scope;
		

		/// <summary>
		/// Default Constructor
		/// </summary>
		Datum() = default;
		
		/// <summary>
		/// Constructor Overload for int32_t
		/// </summary>
		/// <param name="other"> Takes in a const ref int32_t and sets the first index in a Datum to that value and the Datum Type to Int</param>
		Datum(int32_t other);

		/// <summary>
		/// Constructor Overload for float
		/// </summary>
		/// <param name="other"> Takes in a const ref float and sets the first index in a Datum to that value and the Datum Type to float</param>
		Datum(float other);

		/// <summary>
		/// Constructor Overload for vec4
		/// </summary>
		/// <param name="other"> Takes in a const ref vec4 and sets the first index in a Datum to that value and the Datum Type to vec4</param>
		Datum(const glm::vec4& other);

		/// <summary>
		/// Constructor Overload for mat4
		/// </summary>
		/// <param name="other"> Takes in a const ref ma4 and sets the first index in a Datum to that value and the Datum Type to ma4</param>
		Datum(const glm::mat4& other);

		/// <summary>
		/// Constructor Overload for string
		/// </summary>
		/// <param name="other"> Takes in a const ref string and sets the first index in a Datum to that value and the Datum Type to string</param>
		Datum(const	std::string& other);

		/// <summary>
		/// Constructor Overload for RTTI*
		/// </summary>
		/// <param name="other"> Takes in a  RTTI* and sets the first index in a Datum to that value and the Datum Type to RTTI*</param>
		Datum(RTTI* other);


		/// <summary>
		/// Constructor Overload for Scope
		/// </summary>
		/// <param name="other"> Takes in a const ref Scope and sets the first index in a Datum to that value and the Datum Type to RTTI*</param>
		Datum(Scope& other);
		


		/// <summary>
		/// Another Constrcutor for Datum that takes a type and capacity
		/// </summary>
		/// <param name="type"> The Type of Datum this will be, cannot be Unknown</param>
		/// <param name="capacity"> The Capacity for this Datum that will be reserved</param>
		Datum(DatumTypes type, size_t capacity = 3);

		/// <summary>
		/// Default Destructor
		/// </summary>
		~Datum();

		/// <summary>
		/// Copy Contructor
		/// </summary>
		/// <param name="other"> The Datum that will be copied from</param>
		Datum(const Datum& other);

		/// <summary>
		/// Default Move Constrctor
		/// </summary>
		/// <param name="rhs"> The Datum that will be moved</param>
		Datum(Datum&& rhs) noexcept;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other"> The data that will be copied</param>
		/// <returns> This Datum with the copied values</returns>
		Datum& operator=(const Datum& other);

		/// <summary>
		/// Move Assingmnet Operator
		/// </summary>
		/// <param name="rhs"> The Datum that will be moved</param>
		/// <returns> This Datum with the other Datum's values moved into it</returns>
		Datum& operator=(Datum&& rhs) noexcept;

		/// <summary>
		/// Assingment Operator Overload for int32_t
		/// </summary>
		/// <param name="other">Takes in a const ref int32_t and sets the first index in a Datum to that value and the Datum Type to Int</param>
		/// <returns>The Datum with the given value at index 0</returns>
		Datum& operator=(int32_t other);

		/// <summary>
		/// Assingment Operator Overload for float
		/// </summary>
		/// <param name="other">Takes in a const ref float and sets the first index in a Datum to that value and the Datum Type to float</param>
		/// <returns>The Datum with the given value at index 0</returns>
		Datum& operator=(float other);

		/// <summary>
		/// Assingment Operator Overload for vec4
		/// </summary>
		/// <param name="other">Takes in a const ref vec4 and sets the first index in a Datum to that value and the Datum Type to vec4 </param>
		/// <returns>The Datum with the given value at index 0</returns>
		Datum& operator=(const glm::vec4& other);

		/// <summary>
		/// Assingment Operator Overload for mat4
		/// </summary>
		/// <param name="other">Takes in a const ref mat4 and sets the first index in a Datum to that value and the Datum Type to mat4</param>
		/// <returns>The Datum with the given value at index 0</returns>
		Datum& operator=(const glm::mat4& other);

		/// <summary>
		/// Assingment Operator Overload for string
		/// </summary>
		/// <param name="other">Takes in a const ref string and sets the first index in a Datum to that value and the Datum Type to string</param>
		/// <returns>The Datum with the given value at index 0</returns>
		Datum& operator=(const	std::string& other);

		/// <summary>
		/// Assingment Operator Overload for RTTI*
		/// </summary>
		/// <param name="other">Takes in a const ref RTTI* and sets the first index in a Datum to that value and the Datum Type to RTTI*</param>
		/// <returns>The Datum with the given value at index 0</returns>
		Datum& operator=(RTTI* other);

		/// <summary>
		/// Assingment Operator Overload for Scope
		/// </summary>
		/// <param name="other">Takes in a const ref Scope and sets the first index in a Datum to that value and the Datum Type to RTTI*</param>
		/// <returns>The Datum with the given value at index 0</returns>
		Datum& operator=(Scope& other);

		/// <summary>
		/// Operator [] for Scope (wrapper for Get)
		/// </summary>
		/// <param name="index"> The index of the datum of the desired Scope</param>
		/// <returns>If within bounds, the desired Scope</returns>
		Scope& operator[](size_t index);


		/// <summary>
		/// Returns the type that this Datum is
		/// </summary>
		/// <returns> A Copy of the </returns>
		DatumTypes Type() const;



		bool IsExternal() const;

		/// <summary>
		/// If the Datum is Unknown, this can set it to a type
		/// </summary>
		/// <param name="type"> The type of Datum it will be set to</param>
		void SetType(const DatumTypes& type);

		/// <summary>
		/// Returns the amount of elements in the Datum
		/// </summary>
		/// <returns> The amount of items in the Datum as a size_t </returns>
		size_t Size() const;

		/// <summary>
		/// Resizes the size of the Datum to be bigger or smaller
		/// </summary>
		/// <param name="newSize"> The new size of the Datum</param>
		void Resize(size_t newSize);


		/// <summary>
		/// Reserves more size for the Datum, cannot shrink it
		/// </summary>
		/// <param name="capacity"> The new capacity of the Datum, must be larger than the current</param>
		void Reserve(size_t capacity);

		/// <summary>
		/// Clears the Datum
		/// </summary>
		void ClearList();


		void SetStorage(DatumTypes type, void* externalData, size_t size);

		/// <summary>
		/// Set Storage, Int32_t Version
		/// </summary>
		/// <param name="externalData"> The external storage that the Datum will point to</param>
		/// <param name="size"> How big the external storage is</param>
		void SetStorage(int32_t* externalData, size_t size);

		/// <summary>
		/// Set Storage, Float Version
		/// </summary>
		/// <param name="externalData"> The external storage that the Datum will point to</param>
		/// <param name="size"> How big the external storage is</param>
		void SetStorage(float* externalData, size_t size);

		/// <summary>
		/// Set Storage, Vec4 Version
		/// </summary>
		/// <param name="externalData"> The external storage that the Datum will point to</param>
		/// <param name="size"> How big the external storage is</param>
		void SetStorage(glm::vec4* externalData, size_t size);

		/// <summary>
		/// Set Storage, Mat4 Version
		/// </summary>
		/// <param name="externalData"> The external storage that the Datum will point to</param>
		/// <param name="size"> How big the external storage is</param>
		void SetStorage(glm::mat4* externalData, size_t size);

		/// <summary>
		/// Set Storage, String Version
		/// </summary>
		/// <param name="externalData"> The external storage that the Datum will point to</param>
		/// <param name="size"> How big the external storage is</param>
		void SetStorage(std::string* externalData, size_t size);

		/// <summary>
		/// Set Storage, RTTI* Version
		/// </summary>
		/// <param name="externalData"> The external storage that the Datum will point to</param>
		/// <param name="size"> How big the external storage is</param>
		void SetStorage(RTTI** externalData, size_t size);


		/// <summary>
		/// The Not Equal Operator
		/// </summary>
		/// <param name="other"> The other Datum that will be compared</param>
		/// <returns> A bool that is true/false depending on if they are not equal or not</returns>
		bool operator!=(const Datum& other) const;

		/// <summary>
		/// The Equal Equal Operator
		/// </summary>
		/// <param name="other"> The other Datum that will be compared</param>
		/// <returns> A bool that is true/false depending on if they are equal or not</returns>
		bool operator==(const Datum& other) const;


		/// <summary>
		/// Sets the given data to the given index, Int32_t Version
		/// </summary>
		/// <param name="data"> The data that will be set</param>
		/// <param name="index"> The place in the Datum where the value will be set</param>
		void Set(int32_t data, const size_t index = 0);

		/// <summary>
		/// Sets the given data to the given index, Float Version
		/// </summary>
		/// <param name="data"> The data that will be set</param>
		/// <param name="index"> The place in the Datum where the value will be set</param>
		void Set(float data, const size_t index = 0);

		/// <summary>
		/// Sets the given data to the given index, Vec4 Version
		/// </summary>
		/// <param name="data"> The data that will be set</param>
		/// <param name="index"> The place in the Datum where the value will be set</param>
		void Set(const glm::vec4& data, const size_t index = 0);

		/// <summary>
		/// Sets the given data to the given index, Mat4 Version
		/// </summary>
		/// <param name="data"> The data that will be set</param>
		/// <param name="index"> The place in the Datum where the value will be set</param>
		void Set(const glm::mat4& data, const size_t index = 0);

		/// <summary>
		/// Sets the given data to the given index, String Version
		/// </summary>
		/// <param name="data"> The data that will be set</param>
		/// <param name="index"> The place in the Datum where the value will be set</param>
		void Set(const std::string& data, const size_t index = 0);

		/// <summary>
		/// Sets the given data to the given index, RTTI* Version
		/// </summary>
		/// <param name="data"> The data that will be set</param>
		/// <param name="index"> The place in the Datum where the value will be set</param>
		void Set(RTTI* data, const size_t index = 0);

	private:
		/// <summary>
		/// Sets the given data to the given index, Scope* Version
		/// </summary>
		/// <param name="data"> The data that will be set</param>
		/// <param name="index"> The place in the Datum where the value will be set</param>
		void Set(Scope& data, const size_t index = 0);


	public:
		template <typename _Type>
		/// <summary>
		/// Main Template of Get. Gets data from the provided index if valid
		/// </summary>
		/// <param name="index"> The place of the data inside the Datum</param>
		/// <returns> The data at that memory location</returns>
		_Type& Get(const size_t index = 0);

		template<>
		/// <summary>
		/// Get Specialization, Int32_t
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The int32_t at that memory location</returns>
		int32_t& Get(const size_t index);

		template<>
		/// <summary>
		/// Get Specialization, Float
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		float& Get(const size_t index);

		template<>
		/// <summary>
		/// Get Specialization, Vec4
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		glm::vec4& Get(const size_t index);

		template<>
		/// <summary>
		/// Get Specialization, Mat4
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		glm::mat4& Get(const size_t index);

		template<>
		/// <summary>
		/// Get Specialization, String
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		std::string& Get(const size_t index);

		template<>
		/// <summary>
		/// Get Specialization, RTTI*
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		RTTI*& Get(const size_t index);

		template<>
		/// <summary>
		/// Get Specialization, RTTI*
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		Scope& Get(const size_t index);




		template <typename _Type>
		/// <summary>
		/// Main Template of Get. Gets data from the provided index if valid
		/// </summary>
		/// <param name="index"> The place of the data inside the Datum</param>
		/// <returns> The data at that memory location</returns>
		_Type& Get(const size_t index = 0) const;

		template<>
		/// <summary>
		/// Get Specialization, Int32_t
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The int32_t at that memory location</returns>
		int32_t& Get(const size_t index) const;

		template<>
		/// <summary>
		/// Get Specialization, Float
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		float& Get(const size_t index) const;

		template<>
		/// <summary>
		/// Get Specialization, Vec4
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		glm::vec4& Get(const size_t index) const;

		template<>
		/// <summary>
		/// Get Specialization, Mat4
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		glm::mat4& Get(const size_t index) const;

		template<>
		/// <summary>
		/// Get Specialization, String
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		std::string& Get(const size_t index) const;

		template<>
		/// <summary>
		/// Get Specialization, RTTI*
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		RTTI*& Get(const size_t index) const;

		template<>
		/// <summary>
		/// Get Specialization, RTTI*
		/// </summary>
		/// <param name="index">The place of the data inside the Datum</param>
		/// <returns>The float at that memory location</returns>
		Scope& Get(const size_t index) const;

		/// <summary>
		/// The general ToString Method
		/// </summary>
		/// <param name="index"> The place of the data inside the Datum </param>
		/// <returns>The data at that indext as a string</returns>
		std::string ToString(const size_t index = 0) const;

		/// <summary>
		/// Given a String, it is coverted to a Datum's Data Type, if it is in the correct format. General Version
		/// </summary>
		/// <param name="str"> The given string that will be converted</param>
		/// <param name="index"> The index that the converted string will be placed in</param>
		void SetFromString(const std::string& str, const size_t index = 0);

		

	private:
		/// <summary>
		/// Given a String, it is coverted to a Datum's Data Type, if it is in the correct format. Int32_t Version
		/// </summary>
		/// <param name="str"> The given string that will be converted</param>
		/// <param name="index"> The index that the converted string will be placed in</param>
		void SetFromStringInt(const std::string& str, const size_t index = 0);

		/// <summary>
		/// Given a String, it is coverted to a Datum's Data Type, if it is in the correct format. Float Version
		/// </summary>
		/// <param name="str"> The given string that will be converted</param>
		/// <param name="index"> The index that the converted string will be placed in</param>
		void SetFromStringFloat(const std::string& str, const size_t index = 0);

		/// <summary>
		/// Given a String, it is coverted to a Datum's Data Type, if it is in the correct format.  Vec4 Version
		/// </summary>
		/// <param name="str"> The given string that will be converted</param>
		/// <param name="index"> The index that the converted string will be placed in</param>
		void SetFromStringVec4(const std::string& str, const size_t index = 0);

		/// <summary>
		/// Given a String, it is coverted to a Datum's Data Type, if it is in the correct format. Mat4 Version
		/// </summary>
		/// <param name="str"> The given string that will be converted</param>
		/// <param name="index"> The index that the converted string will be placed in</param>
		void SetFromStringMat4(const std::string& str, const size_t index = 0);

		/// <summary>
		/// Given a String, it is coverted to a Datum's Data Type, if it is in the correct format. String Version
		/// </summary>
		/// <param name="str"> The given string that will be converted</param>
		/// <param name="index"> The index that the converted string will be placed in</param>
		void SetFromStringString(const std::string& str, const size_t index = 0);



		



		/// <summary>
		/// Given a valid index, the data at that location is converted to a string, Int32_t Version
		/// </summary>
		/// <param name="index"> Index of data that will be converted</param>
		/// <returns> Converted String</returns>
		std::string ToStringInt(const size_t index = 0) const;

		/// <summary>
		/// Given a valid index, the data at that location is converted to a string, Float Version
		/// </summary>
		/// <param name="index"> Index of data that will be converted</param>
		/// <returns> Converted String</returns>
		std::string ToStringFloat(const size_t index = 0) const;

		/// <summary>
		/// Given a valid index, the data at that location is converted to a string, Vec4 Version
		/// </summary>
		/// <param name="index"> Index of data that will be converted</param>
		/// <returns> Converted String</returns>
		std::string ToStringVec4(const size_t index = 0) const;
		 
		/// <summary>
		/// Given a valid index, the data at that location is converted to a string, Mat4 Version
		/// </summary>
		/// <param name="index"> Index of data that will be converted</param>
		/// <returns> Converted String</returns>
		std::string ToStringMat4(const size_t index = 0) const;

		/// <summary>
		/// Given a valid index, the data at that location is converted to a string, String Version
		/// </summary>
		/// <param name="index"> Index of data that will be converted</param>
		/// <returns> Converted String</returns>
		std::string ToStringString(const size_t index = 0) const;

		/// <summary>
		/// Given a valid index, the data at that location is converted to a string, RTTI* Version
		/// </summary>
		/// <param name="index"> Index of data that will be converted</param>
		/// <returns> Converted String</returns>
		std::string ToStringRTTI(const size_t index = 0) const;

	public:

		void PushBackFromString(const std::string& str);

		void PushBackFromStringInt(const std::string& str);
		void PushBackFromStringFloat(const std::string& str);
		void PushBackFromStringVec4(const std::string& str);
		void PushBackFromStringMat4(const std::string& str);
		void PushBackFromStringString(const std::string& str);

		//void PushBackFromStringRTTI(const std::string& str);
		//void PushBackFromStringScope(const std::string& str);

		/// <summary>
		/// Adds given data to the end of the Datum, Int32_t Version
		/// </summary>
		/// <param name="data"> The data that will added to Datum</param>
		void PushBack(const int32_t& data);

		/// <summary>
		/// Adds given data to the end of the Datum, Float Version
		/// </summary>
		/// <param name="data"> The data that will added to Datum</param>
		void PushBack(const float& data);

		/// <summary>
		/// Adds given data to the end of the Datum, Vec4 Version
		/// </summary>
		/// <param name="data"> The data that will added to Datum</param>
		void PushBack(const glm::vec4& data);

		/// <summary>
		/// Adds given data to the end of the Datum, Mat4 Version
		/// </summary>
		/// <param name="data"> The data that will added to Datum</param>
		void PushBack(const glm::mat4& data);

		/// <summary>
		/// Adds given data to the end of the Datum, String Version
		/// </summary>
		/// <param name="data"> The data that will added to Datum</param>
		void PushBack(const std::string& data);

		/// <summary>
		/// Adds given data to the end of the Datum, RTTI* Version
		/// </summary>
		/// <param name="data"> The data that will added to Datum</param>
		void PushBack(RTTI* const & data);
		
	//Disabled for Testing Purposes
	//private:
		/// <summary>
		/// Adds given data to the end of the Datum, Scope Version
		/// </summary>
		/// <param name="data"> The data that will added to Datum</param>
		void PushBack(Scope& data);

	public:
		/// <summary>
		/// Removes the last item from the Datum's pointer, cannot be used if the Datum has external storage
		/// </summary>
		void PopBack();

		//Front Non Const Done
		template <typename _Type>
		/// <summary>
		/// Gets the value at the Front of the list, General Template
		/// </summary>
		/// <returns> A ref to the data</returns>
		_Type& Front();

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Int32_t Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		int32_t& Front();

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Float Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		float& Front();

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Vec4 Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		glm::vec4& Front();

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Mat4 Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		glm::mat4& Front();

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, String Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		std::string& Front();

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, RTTI* Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		RTTI*& Front();

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, RTTI* Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		Scope& Front();




		template <typename _Type>
		/// <summary>
		/// Gets the value at the Front of the list, General Template Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const _Type& Front() const;

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Int32_t Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const int32_t& Front()const;

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Float Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const float& Front() const;

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Vec4 Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const glm::vec4& Front() const;

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, Mat4 Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const glm::mat4& Front() const;

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, String Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const std::string& Front() const;

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, RTTI* Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		RTTI* const & Front() const;

		template<>
		/// <summary>
		/// Gets the value at the Front of the list, RTTI* Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const Scope& Front() const;


		template<typename _Type>
		/// <summary>
		/// Gets the value at the Back of the list, General Template
		/// </summary>
		/// <returns> A ref to the data</returns>
		_Type& Back();

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Int32_t Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		int32_t& Back();

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Float Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		float& Back();

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Vec4 Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		glm::vec4& Back();

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Mat4 Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		glm::mat4& Back();

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, String Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		std::string& Back();

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, RTTI* Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		RTTI*& Back();

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, RTTI* Version
		/// </summary>
		/// <returns> A ref to the data</returns>
		Scope& Back();


		
		template <typename _Type>
		/// <summary>
		/// Gets the value at the Back of the list, General Template Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const _Type& Back() const;

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Int32_t Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const int32_t& Back()const;

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Float Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const float& Back() const;


		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Vec4 Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const glm::vec4& Back() const;

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, Mat4 Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const glm::mat4& Back() const;

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, String Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const std::string& Back() const;

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, RTTI* Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		RTTI* const & Back() const;

		template<>
		/// <summary>
		/// Gets the value at the Back of the list, RTTI* Version Const
		/// </summary>
		/// <returns> A ref to the data</returns>
		const Scope& Back() const;

		

		/// <summary>
		/// Removes the given data from the list, if it is found, Int32_t Version
		/// </summary>
		/// <param name="data"> The data that will try to be removed</param>
		/// <returns> A bool that is true/false, depending on if the data was removed or not</returns>
		bool Remove(const int32_t data);

		/// <summary>
		/// Removes the given data from the list, if it is found, Float Version
		/// </summary>
		/// <param name="data"> The data that will try to be removed</param>
		/// <returns> A bool that is true/false, depending on if the data was removed or not</returns>
		bool Remove(const float data);

		/// <summary>
		/// Removes the given data from the list, if it is found, Vec4 Version
		/// </summary>
		/// <param name="data"> The data that will try to be removed</param>
		/// <returns> A bool that is true/false, depending on if the data was removed or not</returns>
		bool Remove(const glm::vec4& data);

		/// <summary>
		/// Removes the given data from the list, if it is found, Mat4 Version
		/// </summary>
		/// <param name="data"> The data that will try to be removed</param>
		/// <returns> A bool that is true/false, depending on if the data was removed or not</returns>
		bool Remove(const glm::mat4& data);

		/// <summary>
		/// Removes the given data from the list, if it is found, String Version
		/// </summary>
		/// <param name="data"> The data that will try to be removed</param>
		/// <returns> A bool that is true/false, depending on if the data was removed or not</returns>
		bool Remove(const std::string& data);

		/// <summary>
		/// Removes the given data from the list, if it is found, RTTI* Version
		/// </summary>
		/// <param name="data"> The data that will try to be removed</param>
		/// <returns> A bool that is true/false, depending on if the data was removed or not</returns>
		bool Remove(const RTTI* data);


		/// <summary>
		/// Removes the given data from the list, if it is found, RTTI* Version
		/// </summary>
		/// <param name="data"> The data that will try to be removed</param>
		/// <returns> A bool that is true/false, depending on if the data was removed or not</returns>
		bool Remove(Scope& data);

		/// <summary>
		/// Removed the data at the given Index
		/// </summary>
		/// <param name="index"> The spot where the data will be removed</param>
		void RemoveAt(const size_t index = 0);



		/// <summary>
		/// Find, Int32_t Version
		/// </summary>
		/// <param name="value"> The data that is trying to be found</param>
		/// <returns> A pair with the index and a bool that is true/false, depending if it was found our not </returns>
		std::pair<size_t,bool> Find(const int32_t value) const;

		/// <summary>
		/// Find, Float Version
		/// </summary>
		/// <param name="value"> The data that is trying to be found</param>
		/// <returns> A pair with the index and a bool that is true/false, depending if it was found our not </returns>
		std::pair<size_t, bool> Find(const float value) const;

		/// <summary>
		/// Find, Vec4 Version
		/// </summary>
		/// <param name="value"> The data that is trying to be found</param>
		/// <returns> A pair with the index and a bool that is true/false, depending if it was found our not </returns>
		std::pair<size_t, bool> Find(const glm::vec4& value) const;

		/// <summary>
		/// Find, Mat4 Version
		/// </summary>
		/// <param name="value"> The data that is trying to be found</param>
		/// <returns> A pair with the index and a bool that is true/false, depending if it was found our not </returns>
		std::pair<size_t, bool> Find(const glm::mat4& value) const;

		/// <summary>
		/// Find, String Version
		/// </summary>
		/// <param name="value"> The data that is trying to be found</param>
		/// <returns> A pair with the index and a bool that is true/false, depending if it was found our not </returns>
		std::pair<size_t, bool> Find(const std::string& value) const;

		/// <summary>
		/// Find, RTTI* Version
		/// </summary>
		/// <param name="value"> The data that is trying to be found</param>
		/// <returns> A pair with the index and a bool that is true/false, depending if it was found our not </returns>
		std::pair<size_t, bool> Find(const RTTI* value) const;


		/// <summary>
		/// Find, RTTI* Version
		/// </summary>
		/// <param name="value"> The data that is trying to be found</param>
		/// <returns> A pair with the index and a bool that is true/false, depending if it was found our not </returns>
		std::pair<size_t, bool> Find(Scope& value) const;
		
		

		

	private:

		


		/// <summary>
		/// A Discriminated union for the Array
		/// </summary>
		union DatumValues final
		{
			int32_t* i;
			float* f;
			glm::vec4* vec;
			glm::mat4* mat;
			std::string* s;
			RTTI** r;
			Scope** t;
			void* v{ nullptr };
		};

		DatumValues _data;
		DatumTypes _type{DatumTypes::UNKNOWN};
		size_t _size{ 0 };
		size_t _capacity{ 0 };
		bool _isExternal{ false };

		
		using PushBackFromStringFunc = void(Datum::*)(const std::string&);
		static const PushBackFromStringFunc DatumPushBackFromString[static_cast<size_t>(DatumTypes::END)];

		/// <summary>
		/// A Lookup Table to return the size of a datatype
		/// </summary>
		static const size_t DatumSizeTypes[static_cast<size_t>(DatumTypes::END) + 1];

		/// <summary>
		/// Lookup Table for Datum removal
		/// </summary>
		static const size_t DatumRemove[static_cast<size_t>(DatumTypes::END) + 1];
		

		using FromStringFunc = void(Datum::*)(const std::string&, const size_t);
		
		/// <summary>
		/// Lookup Table for SetFromString
		/// </summary>
		static const FromStringFunc DatumFromString[static_cast<size_t>(DatumTypes::END)];

		using ToStringFunc = std::string(Datum::*)(size_t index) const;


		/// <summary>
		/// Lookup Table for ToString
		/// </summary>
		static const ToStringFunc DatumToString[static_cast<size_t>(DatumTypes::END) + 1];

		using CompareFunc = bool(Datum::*)(const DatumValues& otherdata) const;


		/// <summary>
		/// Lookup Table for Comparison
		/// </summary>
		static const CompareFunc DatumCompare[static_cast<size_t>(DatumTypes::END) + 1];


		friend class Attributed;

		void RemoveHelper(DatumTypes type) const;

		void PushBackHelper(DatumTypes type);

		void ScalarAssignmentHelper(DatumTypes type);

		void GetHelper(DatumTypes type, size_t index) const;

		void FrontBackHelper(DatumTypes type) const;



		bool ComparePrim(const DatumValues& otherdata) const;
		bool CompareStrings(const DatumValues& otherdata) const;
		bool ComparePointers(const DatumValues& otherdata) const;


	};
	
}

#include "Datum.inl"


