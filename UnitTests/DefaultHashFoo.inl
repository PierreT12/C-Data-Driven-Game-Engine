namespace FieaGameEngine
{
	template<>
	struct DefaultHash<Foo>
	{
		inline size_t operator()(Foo type)
		{
			return AdditiveHash(reinterpret_cast<const uint8_t*>(&type.Data()), sizeof(type.Data()));
		}
	};

	template<>
	struct DefaultHash<const Foo>
	{
		inline size_t operator()(const Foo type)
		{
			return AdditiveHash(reinterpret_cast<const uint8_t*>(&type.Data()), sizeof(type.Data()));
		}
	};

}





