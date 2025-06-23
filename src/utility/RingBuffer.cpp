/*--------------------------------------------------------------------
This file is part of the Arduino WiFiEsp library.

The Arduino WiFiEsp library is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

The Arduino WiFiEsp library is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Arduino WiFiEsp library.  If not, see
<http://www.gnu.org/licenses/>.
--------------------------------------------------------------------*/

#include <Arduino.h>

#include "RingBuffer.h"


RingBuffer::RingBuffer(unsigned int size)
{
	_size = size;
	// add one char to terminate the string
	_ringBuf = new char[size+1];
	_ringBufEnd = &_ringBuf[size];
	init();
}

RingBuffer::~RingBuffer() {}

void RingBuffer::reset()
{
	_ringBufP = _ringBuf;
}

void RingBuffer::init()
{
	_ringBufP = _ringBuf;
	memset(_ringBuf, 0, _size+1);
}

void RingBuffer::push(char c)
{
	*_ringBufP = c;
	_ringBufP++;
	if (_ringBufP>=_ringBufEnd)
		_ringBufP = _ringBuf;
}



bool RingBuffer::endsWith(const char* str)
{
	int findStrLen = strlen(str);

	// b is the start position into the ring buffer
	char* b = _ringBufP-findStrLen;
	if(b < _ringBuf)
		b = b + _size;

	char *p1 = (char*)&str[0];
	char *p2 = p1 + findStrLen;

	for(char *p=p1; p<p2; p++)
	{
		if(*p != *b)
			return false;

		b++;
		if (b == _ringBufEnd)
			b=_ringBuf;
	}

	return true;
}



void RingBuffer::getStr(char * destination, unsigned int skipChars)
{
	int len = _ringBufP-_ringBuf-skipChars;

	// copy buffer to destination string
	strncpy(destination, _ringBuf, len);

	// terminate output string
	//destination[len]=0;
}

void RingBuffer::getStrN(char * destination, unsigned int skipChars, unsigned int num)
{
	int len = _ringBufP-_ringBuf-skipChars;

	if (len>num)
		len=num;

	// copy buffer to destination string
	strncpy(destination, _ringBuf, len);

	// terminate output string
	//destination[len]=0;
}
