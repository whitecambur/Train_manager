#include "mine_btn.h"
#include <graphics.h>

void BTN_NH(){
}

BTN::BTN(//两个端点创建对象的构造函数
  int x1,
  int y1,
  int x2,
  int y2,

  PIMAGE img,

  void (*function_left)(),
  void (*function_right)(),
  void (*function_hover)(),
  void (*function_hoverback)(),
  void (*function_down)(),
  void (*function_up)(),

  bool is_disabled
)
{
  //从参数获取值
  m_x1 = x1;
  m_y1 = y1;
  m_x2 = x2;
  m_y2 = y2;
  m_img = img;
  m_function_left = function_left;
  m_function_right = function_right;
  m_function_hover = function_hover;
  m_function_hoverback = function_hoverback;
  m_function_down = function_down;
  m_function_up = function_up;
  m_is_disabled = is_disabled;

  //获取宽度和长度
  m_length = y2 - y1;
  m_width = x2 - x1;

  //默认不高亮
  m_is_highlight = 0;
}

BTN::BTN(//通过左上坐标和长宽创建按钮对象的构造函数
  bool createmode,
  
  int x,
  int y,
  int width,
  int length,

  PIMAGE img,
  
  void (*function_left)(),
  void (*function_right)(),
  void (*function_hover)(),
  void (*function_hoverback)(),
  void (*function_down)(),
  void (*function_up)(),

  bool is_disabled
)
{
  //从参数获取对应值
  m_x1 = x;
  m_y1 = y;
  m_width = width;
  m_length = length;
  m_img = img;
  m_function_left = function_left;
  m_function_right = function_right;
  m_function_hover = function_hover;
  m_function_hoverback = function_hoverback;
  m_function_down = function_down;
  m_function_up = function_up;
  m_is_disabled = is_disabled;

  //计算得到右下端点坐标
  m_x2 = m_x1 + m_width;
  m_y2 = m_y1 + m_length;
  
  //默认不高亮
  m_is_highlight = 0;
}

BTN::~BTN(){//析构函数
}

////////////////////////////鼠标操作函数
bool BTN::left(int x,int y)
{
  if ((x >= m_x1 && x < m_x2) && (y >= m_y1 && y < m_y2))//如果鼠标在按钮上
  {
    mouse_msg msg = {0};
    while (1)
    {
      while(mousemsg())
      {
        msg = getmouse();
        if (msg.is_up())
        {
          m_function_left();
          return 1;
        }
      }
    }
  }
  return 0;
}
bool BTN::right(int x,int y)
{
  if ((x >= m_x1 && x < m_x2) && (y >= m_y1 && y < m_y2))//如果鼠标在按钮上
  {
    mouse_msg msg = {0};
    while (1)
    {
      while(mousemsg())
      {
        msg = getmouse();
        if (msg.is_up())
        {
          m_function_right();
          return 1;
        }
      }
    }
  }
  return 0;
}
bool BTN::hover(int x,int y)
{
  if ((x >= m_x1 && x < m_x2) && (y >= m_y1 && y < m_y2))
  {
    m_function_hover();
    return 1;
  }
  return 0;
}
bool BTN::hoverback(int x,int y)
{
  if ((x >= m_x1 && x < m_x2) && (y >= m_y1 && y < m_y2));
  else
  {
    m_function_hoverback();
    return 1;
  }
  return 0;
}
bool BTN::down(int x,int y)
{
  if ((x >= m_x1 && x < m_x2) && (y >= m_y1 && y < m_y2))
  {
    m_function_down();
    return 1;
  }
  return 0;
}
bool BTN::up(int x,int y)
{
  if ((x >= m_x1 && x < m_x2) && (y >= m_y1 && y < m_y2))
  {
    m_function_up();
    return 1;
  }
  return 0;
}

////////////////////////////////改变按钮属性的函数
bool BTN::set_x1(int num)
{
  m_x1 = num;
  m_width = m_x2 - m_x1;
  return 1;
}
bool BTN::set_y1(int num)
{
  m_y1 = num;
  m_length = m_y2 - m_y1;
  return 1;
}
bool BTN::set_x2(int num)
{
  m_x2 = num;
  m_width = m_x2 - m_x1;
  return 1;
}
bool BTN::set_y2(int num)
{
  m_y2 = num;
  m_length = m_y2 - m_y1;
  return 1;
}
bool BTN::set_img(PIMAGE img)
{
  m_img = img;
  return 1;
}
bool BTN::set_disabled(bool b)
{
  m_is_disabled = b;
  return 1;
}
bool BTN::change_disabled()
{
  m_is_disabled = !m_is_disabled;
  return 1;
}
bool BTN::set_highlight(int a)
{
  if (a > 0)
    m_is_highlight = 1;
  else if (a < 0)
    m_is_highlight = -1;
  else
    m_is_highlight = 0;
  return 0;
}
bool BTN::set_function_left(void (*newf)())
{
  m_function_left = newf;
  return 1;
}
bool BTN::set_function_right(void (*newf)())
{
  m_function_right = newf;
  return 1;
}
bool BTN::set_function_hover(void (*newf)())
{
  m_function_hover = newf;
  return 1;
}
bool BTN::set_function_hoverback(void (*newf)())
{
  m_function_hoverback = newf;
  return 1;
}
bool BTN::set_function_down(void (*newf)())
{
  m_function_down = newf;
  return 1;
}
bool BTN::set_function_up(void (*newf)())
{
  m_function_up = newf;
  return 1;
}

void BTN::show()
{
  if (m_img != NULL)//有图片则显示图片
    putimage(m_x1, m_y1, m_img);
  else//无图片则显示矩形
    bar(m_x1, m_y1, m_x2, m_y2);
  if (m_is_highlight == 1){//高亮图片
    PIMAGE temp = newimage(m_width, m_length);
    setfillcolor(WHITE, temp);
    bar(0, 0, m_width, m_length, temp);
    putimage_alphablend(NULL, temp, m_x1, m_y1, 100);
    delimage(temp);
  }
  else if (m_is_highlight == -1){//选中图片
    PIMAGE temp = newimage(m_width, m_length);
    setfillcolor(BLACK, temp);
    bar(0, 0, m_width, m_length, temp);
    putimage_alphablend(NULL, temp, m_x1, m_y1, 100);
    delimage(temp);
  }
}

