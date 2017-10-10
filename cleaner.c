/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Assignment 2 -- Red Black Trees
 */

#include "cleaner.h"
#include "scanner.h"


char *cleanUp(FILE *fp)
{
	if(stringPending(fp))
	{
		return readString(fp);
	}
	else
	{
		return readToken(fp);
	}
}

void cleanString(char *str)
{
	char *src = str, *dest = str;

	while (*src)
	{
		if(isspace((unsigned char)*src))
		{
			while(!isalpha((unsigned char)*src))
			{
				src++;
				*dest = ' ';
			}
		}
		else if (!isalpha((unsigned char)*src))
		{
			src++;
		}
		else if (isupper((unsigned char)*src))
		{
			*dest++ = tolower((unsigned char)*src);
			src++;
		}
		else if(src == dest)
		{
			src++;
			dest++;
		} 
		else
		{
			*dest++ = *src++;
		}
	}

	*dest = 0;
}


