/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: 2AHIF
 *-----------------------------------------------------------------------------
 * Exercise Number: 20
 * File:			lottery.c
 * Author(s):		Daniel Andricic
 * Due Date:		09.04.2019
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include "lottery.h"

int tips[TIP_SIZE];
FILE* fd;
char seperator;

bool init_lottery(const char *csv_file, char csv_separator)
{
  seperator = csv_separator;

  fd = fopen(csv_file, "r");

  for (int i = 0; i < TIP_SIZE; i++)
  {
    tips[i] = 0;
  }
  return fd != 0;
}

bool 	get_tip (int tip_number, int tip[TIP_SIZE])
{
  char line[MAX_LINE_LEN];

  fseek(fd, 0, SEEK_SET);

  if(tip_number < 0)
  {
    return false;
  }

  for (int i = 0; i <= tip_number; i++)
  {
    if(fgets(line, MAX_LINE_LEN, fd) == 0)
    {
      return false;
    }
  }

  int index=0;
  int count=0;
  for (int i = search_start(line); i < MAX_LINE_LEN; i++)
  {
    char numbers[2];

    if(line[i] == seperator || line[i] == '\n' || line[i] == '\0')
    {
      tip[index++] = converting_to_int(numbers,count);
      count = 0;
      if(index == TIP_SIZE)
      {
        break;
      }
    }
    else
    {
      numbers[count++] = line[i];
    }
  }
  return true;
}

int converting_to_int(char* chars, int count){
  int num = 0;
  for (int i = 0; i < count; i++)
  {
    num = num * 10 + chars[i] - '0';
  }
  return num;
}

int search_start(char* line){
  for (int i = 0; i < MAX_LINE_LEN; i++)
  {
    if(line[i] == seperator)
    {
      return i + 1;
    }
  }
  return -1;
}

bool 	set_drawing (int drawing_numbers[TIP_SIZE])
{
  for (int i = 0; i < TIP_SIZE; i++)
  {
    if(drawing_numbers[i] < 1 || drawing_numbers[i] > 45)
    {
      return false;
    }
    tips[i] = drawing_numbers[i];
  }
  return true;
}

int get_tip_result(int tip_number)
{
  if(tips[0] == 0)
  {
    return -1;
  }

  int tip[TIP_SIZE];

  if(!get_tip(tip_number,tip))
  {
    return -2;
  }

  int count = 0;

  for (int i = 0; i < TIP_SIZE; i++)
  {
    if(is_in_drawings(tip[i]))
    {
      count++;
    }
  }

  return count;
}

bool is_in_drawings(int tip)
{
  for (int i = 0; i < TIP_SIZE; i++)
  {
    if(tip == tips[i])
    {
      return true;
    }
  }
  return false;
}

int 	get_right_tips_count (int right_digits_count)
{
  if (right_digits_count < 0 || right_digits_count > TIP_SIZE || tips[0] == 0)
  {
    return -1;
  }

  int count = 0;
  fseek(fd, 0 , SEEK_SET);
  char line[MAX_LINE_LEN];

  for (int i = 0; i < 1000000; i++)
  {
    if(fgets(line, MAX_LINE_LEN, fd) == 0)
    {
      return count;
    }
    if(get_tip_result(i) == right_digits_count)
    {
      count++;
    }
  }
  return count;
}
