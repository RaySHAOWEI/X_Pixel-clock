#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define minute_part_x 12
#define minute_part_y 1

#define second_part_x 22
#define second_part_y 1

#define point_x 18
#define point_y 3

#define picture_x 1
#define picture_y 1

#define screen_x 32
#define screen_y 8

int screen[screen_y][screen_x] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int num0[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1}};
int *p_num0 = &num0[0][0];

int num1[6][3] =
    {{5, 3, 0},
     {0, 1, 0},
     {1, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {1, 1, 1}};
int *p_num1 = &num1[0][0];

int num2[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1}};
int *p_num2 = &num2[0][0];

int num3[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}};
int *p_num3 = &num3[0][0];

int num4[6][3] =
    {{5, 3, 0},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}};
int *p_num4 = &num4[0][0];

int num5[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}};
int *p_num5 = &num5[0][0];

int num6[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}};
int *p_num6 = &num6[0][0];

int num7[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1}};
int *p_num7 = &num7[0][0];

int num8[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}};
int *p_num8 = &num8[0][0];

int num9[6][3] =
    {{5, 3, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}};
int *p_num9 = &num9[0][0];

int char_a[6][3] =
    {{5, 3, 0},
     {0, 1, 0},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}};
int *p_char_a = &char_a[0][0];

String the_char = "0123456789a";

/*先拆分所有字符；
  然后一个一个缓存到缓存屏幕里；
  最后遍历缓存屏；
  打印。*/

void break_up(string thing) //拆分
{
  int start_x = 0;
  int start_y = 0;
  int thing_long = thing.length();
  char char_arr[thing_long];
  for (int n = 0; n < thing_long; n++)
  {
    char_arr[n] = thing.substring(n, n + 1));
  }
  return char_arr
}

void char_cache(int *cursor, String want_char)
{
  int *arr[11] = {&p_num0, &p_num1, &p_num2, &p_num3, &p_num4, &p_num5, &p_num6, &p_num7, &p_num8, &p_num9, &p_char_a};
  int char_index = String(the_char).indexOf(String(want_char));
  int *num = arr[char_index];
  int the_x = num[0][1];
  int the_y = mun[0][0];

  for (int y = 0; y < the_y; y++)
  {
    for (int x = 0; x < the_x; x++)
    {
      *(cursor + x + y * 32) = *(num + x + y * the_x);
    }
  }
}

void prints(int x, int y, String thing)
{
  int start_x = x;
  int start_y = y;
  int thing_long = thing.length();
  for (int n = 0; n < thing_long; n++)
  {
    int char_index = String("0123456789:-a").indexOf(thing.substring(n, n + 1));
    char_cache(&screen[y][x], thing.substring(n, n + 1));
    x += (dictionary[0][char_index] + 1);
    y = start_y;
  }
}

void print_mode(int *p_screen, int mode_num)
{
  if (mode_num == 1)
  {
    for (int y = 0; y < 8; y = y + 1)
    {
      for (int x = 0; x < 32; x = x + 1)
      {
        if (*(p_screen + y * 32 + x) == 1)
        {
          matrix.drawPixel(x, y, matrix.Color(255, 0, 255));
        }
      }
    }
  }
}
