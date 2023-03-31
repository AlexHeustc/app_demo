#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

#include "../Headers/display_manage.h"
#include "../Headers/fontdata.h"


/**********************************************************************
 * 函数名称： lcd_put_ascii
 * 功能描述： 在LCD指定位置上显示一个8*16的字符
 * 输入参数： x坐标，y坐标，ascii码
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/05/12	     V1.0	  zh(angenao)	      创建
 ***********************************************************************/
void lcd_put_ascii(int x, int y, unsigned char c)
{
    unsigned char *dots = (unsigned char *)&fontdata_8x16[c*16];
    int i, b;
    unsigned char byte;

    for (i = 0; i < 16; i++)
    {
        byte = dots[i];
        for (b = 7; b >= 0; b--)
        {
            if (byte & (1<<b))
            {
                /* show */
                PutPixel(x+7-b, y+i, 0xffffff); /* 白 */
            }
            else
            {
                /* hide */
                PutPixel(x+7-b, y+i, 0); /* 黑 */
            }
        }
    }
}

int main(int argc, char **argv)
{
    //select the regin you want to show font on the screen
    Region region;
    region.iLeftUpX = 100;
    region.iLeftUpY = 100;
    region.iWidth   = 8;
    region.iHeigh  = 16;

    //malloc a block of memory
    PDispBuff ptBuffer;

    DisplayInit();
    SelectDefaultDisplay("fb");
    InitDefaultDisplay();
    lcd_put_ascii(100, 100, 'A');



    ptBuffer = GetDisplayBuffer();
    FlushDisplayRegion(&region, ptBuffer);

    return 0;
}


