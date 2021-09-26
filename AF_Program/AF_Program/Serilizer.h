#pragma once
class Serilizer
{
public:
	template<class T>
	static void serialize(T source, unsigned char* dest)	//this can be executed on stack
	{
		static_assert(std::is_pointer<T*>::value, "Expected a pointer");
		*(T&)dest = *source; //copy content from char array to template slot
	}

	template<class T>
	static void deserialize(T dest, unsigned char* source)	//this can be executed on stack
	{
		static_assert(std::is_pointer<T*>::value, "Expected a pointer");
		*dest = *(T&)source;	//copy the content of the template parm to a char array
		//memcpy(&dest, source, sizeof(T));	//this does the exact same from what I can tell
	}

	template<class T>
	static unsigned char* Safe_Serialize(T* source)	//This is a safe version of the 2 methods above
	{														//It is safe because it's all done on the heap and contained
		static_assert(std::is_pointer<T*>::value, "Expected a pointer");
		unsigned char* buffer = new unsigned char[sizeof(T)];
		serialize(source, buffer);
		return buffer;
	}

	template<class T>
	static T* Safe_Deserialize(unsigned char*buffer)	//Same as above comment
	{
		static_assert(std::is_pointer<T*>::value, "Expected a pointer");
		T* Output = new T();
		deserialize(Output, buffer);
		delete[] buffer;
		return Output;
	}
};

