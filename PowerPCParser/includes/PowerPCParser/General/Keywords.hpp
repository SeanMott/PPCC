#pragma once

//defines various keywords

#include <cstdint>
#include <string>

namespace PPC::Util
{
	//defines various datatypes
	enum class Datatype
	{
		Skip_Uint16 = 0, //defines a skip which is just a uint16

		Float, //defines a float
		Double, //defines a double

		Byte, //defines a byte

		Byte_4, //defines a 4byte

		Ptr, //defines a regular pointer
		FuncPtr, //defines a function pointer

		Count
	};

	//defines a array of datatypes in assembly
#define DATATYPE_KEYWORD_COUNT 5
	static const char* DATATYPE_KEYWORD_STR[DATATYPE_KEYWORD_COUNT] = { "skip", "float", "double", "byte", "4byte" };

	//checks if a string is a datatype
	inline bool IsDatatype(const char* keyword, uint32_t& arrayIndex, Datatype& datatype)
	{
		for (uint32_t i = 0; i < DATATYPE_KEYWORD_COUNT; ++i)
		{
			if (!strcmp(keyword, DATATYPE_KEYWORD_STR[i]))
			{
				datatype = (Datatype)i;
				arrayIndex = i;
				return true;
			}
		}

		return false;
	}

	//defines various directives
	enum class DotDirective
	{
		//defines the bounds of a function
		FuncStart = 0,
		FuncEnd,

		//defines the bounds of a object
		ObjectStart,
		ObjectEnd,

		//JumpLabel, //marks a jump label
		//marks a jump address

		//Section, //marks a section
		//Section_Text, //marks a text section
		//Section_Constructor, //marks constructors
		//Section_Deconstructor, //marks deconstructors
		//SetAlignment, //sets alignment

		Count
	};

	static const char* DOT_DERETIVE_KEYWORD_STRS[(int)DotDirective::Count] = { "fn", "endfn", "obj", "endobj" };

	//checks if a string is a dot directive
	inline bool IsDotDerective(const char* keyword, uint32_t& arrayIndex, DotDirective& directive)
	{
		for (uint32_t i = 0; i < (int)DotDirective::Count; ++i)
		{
			if (!strcmp(keyword, DOT_DERETIVE_KEYWORD_STRS[i]))
			{
				arrayIndex = i;
				directive = (DotDirective)i;
				return true;
			}
		}

		return false;
	}
}