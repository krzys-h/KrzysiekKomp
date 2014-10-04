#pragma once

#ifndef __cplusplus
#error This header cannot be used in C
#endif

#include "screen/text_screen.h"
#include "services/keyboard.h"
#include "stdlib/printf.h"

namespace std {
	class StdOut {
		public:
		
		inline StdOut& operator<<(const char* in)
		{
			printf("%s", in);
			return *this;
		}
		
		inline StdOut& operator<<(char in)
		{
			printf("%c", in);
			return *this;
		}
		
		inline StdOut& operator<<(int in)
		{
			printf("%d", in);
			return *this;
		}
		
		inline void clear()
		{
			screen_clear();
		}
	};
	
	class StdIn {
		public:
		
		inline StdIn& operator>>(char* out)
		{
			getstring(out);
			return *this;
		}
	};
	
	static StdOut cout = StdOut();
	static StdIn cin = StdIn();
	static const char endl = '\n';
}
