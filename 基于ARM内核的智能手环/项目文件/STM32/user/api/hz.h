#ifndef __ZI_H_
#define __ZI_H_
//PC2LCD2002取模方式设置：阴码+逐行式+顺向+C51格式
typedef struct
{
	unsigned char Index[2];
	char Msk[24];
}FONT_HZ12;

#define hz12_num   50

const FONT_HZ12 Hz12X12[hz12_num]={
"信",{0x22,0x00,0x21,0x00,0x5F,0xE0,0x40,0x00,0xCF,0xC0,0x40,0x00,0x4F,0xC0,0x40,0x00,0x4F,0xC0,0x48,0x40,0x4F,0xC0,0x48,0x40},/*"信",0*/
"盈",{0x00,0x00,0xFF,0x80,0x20,0x80,0x3D,0x00,0x55,0xC0,0x48,0x40,0x95,0x80,0x00,0x00,0x7F,0xC0,0x4A,0x40,0x4A,0x40,0xFF,0xE0},/*"盈",1*/
"达",{0x41,0x00,0x21,0x00,0x01,0x00,0x0F,0xE0,0xE1,0x00,0x21,0x00,0x22,0x80,0x22,0x40,0x24,0x20,0x28,0x20,0x50,0x00,0x8F,0xE0},/*"达",2*/
};


typedef struct
{
	unsigned char Index[2];
	char Msk[32];
}FONT_HZ16;

#define hz16_num   500

const FONT_HZ16 Hz16X16[hz16_num]={


"翟",{0x00,0x00,0x7E,0xFC,0x22,0x44,0x12,0x24,0x1A,0x34,0x62,0xC4,0x02,0x04,0x09,0x00,0x1F,0xFC,0x30,0x80,0x5F,0xF8,0x90,0x80,0x1F,0xF8,0x10,0x80,0x1F,0xFC,0x10,0x00},/*"翟",0*/

"翔",{0x44,0x00,0x25,0xDC,0x28,0x44,0xFE,0x44,0x11,0x54,0x10,0xCC,0x7C,0x44,0x10,0x44,0x10,0x4C,0xFE,0xD4,0x11,0x64,0x10,0x44,0x20,0x44,0x20,0x44,0x41,0x54,0x80,0x88},/*"翔",1*/



"第",{0x20,0x40,0x3F,0x7E,0x48,0x90,0x85,0x08,0x3F,0xF8,0x01,0x08,0x01,0x08,0x3F,0xF8,0x21,0x00,0x21,0x00,0x3F,0xFC,0x03,0x04,0x05,0x04,0x19,0x28,0xE1,0x10,0x01,0x00},/*"第",0*/
	

"组",{0x10,0x00,0x11,0xF8,0x21,0x08,0x21,0x08,0x49,0x08,0xF9,0xF8,0x11,0x08,0x21,0x08,0x41,0x08,0xF9,0xF8,0x41,0x08,0x01,0x08,0x19,0x08,0xE1,0x08,0x47,0xFE,0x00,0x00},/*"组",0*/

	
"嵌",{0x01,0x00,0x21,0x08,0x21,0x08,0x3F,0xF8,0x00,0x20,0x22,0x20,0x22,0x3E,0xFF,0x42,0x22,0x94,0x22,0x10,0x3E,0x10,0x22,0x10,0x22,0x28,0x3E,0x28,0x22,0x44,0x00,0x82},/*"嵌",0*/

"入",{0x04,0x00,0x02,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x02,0x80,0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x08,0x20,0x10,0x10,0x20,0x10,0x40,0x08,0x80,0x06},/*"入",1*/

"式",{0x00,0x48,0x00,0x44,0x00,0x44,0x00,0x40,0xFF,0xFE,0x00,0x40,0x00,0x40,0x3E,0x40,0x08,0x40,0x08,0x40,0x08,0x20,0x08,0x22,0x0F,0x12,0x78,0x0A,0x20,0x06,0x00,0x02},/*"式",2*/

"软",{0x10,0x40,0x10,0x40,0x10,0x40,0xFE,0x7C,0x20,0x84,0x28,0x88,0x49,0x20,0x7E,0x20,0x08,0x20,0x08,0x50,0x0E,0x50,0xF8,0x50,0x48,0x88,0x08,0x88,0x09,0x04,0x0A,0x02},/*"软",3*/

"件",{0x08,0x20,0x08,0x20,0x09,0x20,0x11,0x20,0x11,0xFC,0x32,0x20,0x32,0x20,0x54,0x20,0x90,0x20,0x17,0xFE,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20},/*"件",4*/

"二",{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00},/*"二",5*/

"班",{0x00,0x80,0x00,0x80,0xF8,0xBE,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0xFA,0xBE,0x22,0x88,0x24,0x88,0x20,0x88,0x39,0x08,0xE1,0x08,0x42,0x3E,0x04,0x00,0x08,0x00},/*"班",6*/
	
	
"裴",{0x04,0x40,0x04,0x40,0x7C,0x7C,0x04,0x40,0x3C,0x78,0x04,0x40,0x7C,0x7C,0x06,0x40,0x01,0x00,0xFF,0xFE,0x05,0x00,0x0C,0x88,0x34,0x50,0xC5,0x30,0x06,0x0E,0x04,0x00},/*"裴",0*/

"家",{0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x7F,0xFC,0x02,0x00,0x0D,0x08,0x71,0x90,0x02,0xA0,0x0C,0xC0,0x71,0xA0,0x06,0x98,0x18,0x86,0xE2,0x80,0x01,0x00},/*"家",1*/

"豪",{0x01,0x00,0x7F,0xFC,0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x00,0x00,0x7F,0xFE,0x40,0x02,0x9F,0xF4,0x06,0x00,0x19,0x20,0x06,0xC0,0x39,0xB0,0x06,0x8C,0x39,0x80},/*"豪",2*/

	

"请",{0x00,0x40,0x40,0x40,0x27,0xFC,0x20,0x40,0x03,0xF8,0x00,0x40,0xE7,0xFE,0x20,0x00,0x23,0xF8,0x22,0x08,0x23,0xF8,0x22,0x08,0x2B,0xF8,0x32,0x08,0x22,0x28,0x02,0x10},/*"请",0*/

"关",{0x10,0x10,0x08,0x10,0x08,0x20,0x00,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x02,0x80,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06},/*"关",1*/

"注",{0x00,0x80,0x20,0x40,0x10,0x00,0x17,0xFC,0x80,0x40,0x40,0x40,0x40,0x40,0x10,0x40,0x13,0xFC,0x20,0x40,0xE0,0x40,0x20,0x40,0x20,0x40,0x20,0x40,0x2F,0xFE,0x00,0x00},/*"注",2*/

"我",{0x04,0x40,0x0E,0x50,0x78,0x48,0x08,0x48,0x08,0x40,0xFF,0xFE,0x08,0x40,0x08,0x44,0x0A,0x44,0x0C,0x48,0x18,0x30,0x68,0x22,0x08,0x52,0x08,0x8A,0x2B,0x06,0x10,0x02},/*"我",3*/

"的",{0x10,0x40,0x10,0x40,0x20,0x40,0x7E,0x7C,0x42,0x84,0x42,0x84,0x43,0x04,0x42,0x44,0x7E,0x24,0x42,0x24,0x42,0x04,0x42,0x04,0x42,0x04,0x7E,0x04,0x42,0x28,0x00,0x10},/*"的",4*/

"G",{0x00,0x00,0x00,0x3C,0x44,0x44,0x80,0x80,0x80,0x8E,0x84,0x44,0x44,0x38,0x00,0x00},/*"G",5*/

"i",{0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00},/*"i",6*/

"t",{0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x12,0x0C,0x00,0x00},/*"t",7*/

"H",{0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00},/*"H",8*/

"u",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00},/*"u",9*/

"b",{0x00,0x00,0x00,0x00,0xC0,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x00,0x00},/*"b",10*/

"，",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x10,0x00,0x20,0x00,0x00,0x00},/*"，",11*/

"我",{0x04,0x40,0x0E,0x50,0x78,0x48,0x08,0x48,0x08,0x40,0xFF,0xFE,0x08,0x40,0x08,0x44,0x0A,0x44,0x0C,0x48,0x18,0x30,0x68,0x22,0x08,0x52,0x08,0x8A,0x2B,0x06,0x10,0x02},/*"我",12*/

"会",{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xCF,0xE6,0x00,0x00,0x00,0x00,0x7F,0xFC,0x02,0x00,0x04,0x00,0x08,0x20,0x10,0x10,0x3F,0xF8,0x10,0x08},/*"会",13*/

"每",{0x10,0x00,0x1F,0xFC,0x20,0x00,0x20,0x00,0x5F,0xF0,0x90,0x10,0x12,0x10,0x11,0x10,0xFF,0xFE,0x20,0x10,0x22,0x10,0x21,0x10,0x3F,0xFC,0x00,0x10,0x00,0xA0,0x00,0x40},/*"每",14*/

"日",{0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10},/*"日",15*/

"更",{0x00,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x11,0x00,0x0A,0x00,0x06,0x00,0x19,0xC0,0xE0,0x3E},/*"更",16*/

"新",{0x10,0x00,0x08,0x04,0x7F,0x78,0x00,0x40,0x22,0x40,0x14,0x40,0xFF,0x7E,0x08,0x48,0x08,0x48,0x7F,0x48,0x08,0x48,0x2A,0x48,0x49,0x48,0x88,0x88,0x28,0x88,0x11,0x08},/*"新",17*/

"学",{0x22,0x08,0x11,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xE0,0x00,0x40,0x01,0x80,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},/*"学",18*/

"习",{0x00,0x00,0x7F,0xF8,0x00,0x08,0x00,0x08,0x08,0x08,0x04,0x08,0x02,0x08,0x02,0x08,0x00,0x68,0x01,0x88,0x0E,0x08,0x70,0x08,0x20,0x08,0x00,0x08,0x00,0x50,0x00,0x20},/*"习",19*/

"笔",{0x10,0x40,0x10,0x40,0x3F,0x7E,0x48,0x90,0x85,0x08,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0xF8,0x3F,0x00,0x01,0x00,0x01,0xFC,0x7F,0x02,0x01,0x02,0x01,0x02,0x00,0xFE},/*"笔",20*/

"记",{0x00,0x00,0x20,0x00,0x11,0xF8,0x10,0x08,0x00,0x08,0x00,0x08,0xF0,0x08,0x11,0xF8,0x11,0x08,0x11,0x00,0x11,0x00,0x11,0x00,0x15,0x02,0x19,0x02,0x10,0xFE,0x00,0x00},/*"记",21*/
	
"宗",{0x02,0x00,0x01,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x00,0x00,0x00,0x00,0x7F,0xFC,0x01,0x00,0x11,0x10,0x11,0x08,0x21,0x04,0x45,0x04,0x02,0x00},/*"宗",0*/

"明",{0x00,0x00,0x00,0xFC,0x7C,0x84,0x44,0x84,0x44,0x84,0x44,0xFC,0x7C,0x84,0x44,0x84,0x44,0x84,0x44,0xFC,0x7C,0x84,0x44,0x84,0x01,0x04,0x01,0x04,0x02,0x14,0x04,0x08},/*"明",1*/

"傲",{0x12,0x10,0x12,0x10,0x1F,0xD0,0x22,0x20,0x2F,0xBE,0x62,0x44,0xBF,0xA4,0x24,0x24,0x24,0x24,0x27,0xA8,0x24,0xA8,0x24,0x90,0x24,0xA8,0x29,0xA8,0x28,0x44,0x30,0x82},/*"傲",2*/

"欢",{0x00,0x80,0x00,0x80,0xFC,0x80,0x04,0xFC,0x05,0x04,0x49,0x08,0x2A,0x40,0x14,0x40,0x10,0x40,0x28,0xA0,0x24,0xA0,0x45,0x10,0x81,0x10,0x02,0x08,0x04,0x04,0x08,0x02},/*"欢",0*/

"迎",{0x00,0x00,0x20,0x80,0x13,0x3C,0x12,0x24,0x02,0x24,0x02,0x24,0xF2,0x24,0x12,0x24,0x12,0x24,0x12,0xB4,0x13,0x28,0x12,0x20,0x10,0x20,0x28,0x20,0x47,0xFE,0x00,0x00},/*"迎",1*/

"大",{0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x10,0x10,0x20,0x08,0xC0,0x06},/*"大",2*/

"家",{0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x7F,0xFC,0x02,0x00,0x0D,0x08,0x71,0x90,0x02,0xA0,0x0C,0xC0,0x71,0xA0,0x06,0x98,0x18,0x86,0xE2,0x80,0x01,0x00},/*"家",3*/

"加",{0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x7C,0xFE,0x44,0x12,0x44,0x12,0x44,0x12,0x44,0x12,0x44,0x12,0x44,0x12,0x44,0x12,0x44,0x22,0x44,0x22,0x7C,0x4A,0x44,0x84,0x00},/*"加",4*/

"我",{0x04,0x40,0x0E,0x50,0x78,0x48,0x08,0x48,0x08,0x40,0xFF,0xFE,0x08,0x40,0x08,0x44,0x0A,0x44,0x0C,0x48,0x18,0x30,0x68,0x22,0x08,0x52,0x08,0x8A,0x2B,0x06,0x10,0x02},/*"我",5*/

"的",{0x10,0x40,0x10,0x40,0x20,0x40,0x7E,0x7C,0x42,0x84,0x42,0x84,0x43,0x04,0x42,0x44,0x7E,0x24,0x42,0x24,0x42,0x04,0x42,0x04,0x42,0x04,0x7E,0x04,0x42,0x28,0x00,0x10},/*"的",6*/

"微",{0x11,0x08,0x15,0x48,0x25,0x48,0x45,0x50,0x97,0xDE,0x10,0x24,0x20,0x14,0x6F,0xD4,0xA0,0x14,0x27,0x94,0x24,0x94,0x24,0xA8,0x24,0xC8,0x24,0x94,0x28,0x14,0x30,0x22},/*"微",7*/

"信",{0x08,0x40,0x08,0x20,0x0B,0xFE,0x10,0x00,0x10,0x00,0x31,0xFC,0x30,0x00,0x50,0x00,0x91,0xFC,0x10,0x00,0x10,0x00,0x11,0xFC,0x11,0x04,0x11,0x04,0x11,0xFC,0x11,0x04},/*"信",8*/

	
"这",{0x00,0x80,0x20,0x40,0x10,0x40,0x17,0xFC,0x00,0x10,0x02,0x10,0xF1,0x20,0x10,0xA0,0x10,0x40,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x08,0x28,0x00,0x47,0xFE,0x00,0x00},/*"这",0*/

"个",{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x10,0x10,0x21,0x08,0xC1,0x06,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00},/*"个",1*/

"是",{0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x00,0x00,0xFF,0xFE,0x01,0x00,0x11,0x00,0x11,0xF8,0x11,0x00,0x29,0x00,0x45,0x00,0x83,0xFE},/*"是",2*/

"我",{0x04,0x40,0x0E,0x50,0x78,0x48,0x08,0x48,0x08,0x40,0xFF,0xFE,0x08,0x40,0x08,0x44,0x0A,0x44,0x0C,0x48,0x18,0x30,0x68,0x22,0x08,0x52,0x08,0x8A,0x2B,0x06,0x10,0x02},/*"我",3*/

"—",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"—",6*/


">",{0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00},/*">",8*/
"王",{0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x00,0x00},/*"王",0*/

"家",{0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x7F,0xFC,0x02,0x00,0x0D,0x08,0x71,0x90,0x02,0xA0,0x0C,0xC0,0x71,0xA0,0x06,0x98,0x18,0x86,0xE2,0x80,0x01,0x00},/*"家",1*/

"乐",{0x00,0x20,0x00,0xF0,0x1F,0x00,0x10,0x00,0x11,0x00,0x21,0x00,0x21,0x00,0x3F,0xFC,0x01,0x00,0x09,0x20,0x09,0x10,0x11,0x08,0x21,0x04,0x41,0x04,0x05,0x00,0x02,0x00},/*"乐",2*/
	
"这",{0x00,0x80,0x20,0x40,0x10,0x40,0x17,0xFC,0x00,0x10,0x02,0x10,0xF1,0x20,0x10,0xA0,0x10,0x40,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x08,0x28,0x00,0x47,0xFE,0x00,0x00},/*"这",0*/

"个",{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x10,0x10,0x21,0x08,0xC1,0x06,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00},/*"个",1*/

"是",{0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x00,0x00,0xFF,0xFE,0x01,0x00,0x11,0x00,0x11,0xF8,0x11,0x00,0x29,0x00,0x45,0x00,0x83,0xFE},/*"是",2*/

"马",{0x00,0x00,0x7F,0xE0,0x00,0x20,0x00,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x04,0xFF,0xE4,0x00,0x04,0x00,0x04,0x00,0x28,0x00,0x10},/*"马",3*/

"顺",{0x04,0x00,0x45,0xFE,0x54,0x20,0x54,0x40,0x55,0xFC,0x55,0x04,0x55,0x24,0x55,0x24,0x55,0x24,0x55,0x24,0x55,0x24,0x55,0x44,0x54,0x50,0x54,0x88,0x85,0x04,0x06,0x02},/*"顺",4*/

"最",{0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x00,0x00,0xFF,0xFE,0x22,0x00,0x3E,0xF8,0x22,0x88,0x3E,0x90,0x22,0x50,0x2F,0x20,0xF2,0x50,0x42,0x88,0x03,0x06},/*"最",5*/

"喜",{0x01,0x00,0x7F,0xFC,0x01,0x00,0x3F,0xF8,0x00,0x00,0x3F,0xF8,0x20,0x08,0x3F,0xF8,0x08,0x20,0xFF,0xFE,0x00,0x00,0x3F,0xF8,0x20,0x08,0x20,0x08,0x3F,0xF8,0x20,0x08},/*"喜",6*/

"欢",{0x00,0x80,0x00,0x80,0xFC,0x80,0x04,0xFC,0x05,0x04,0x49,0x08,0x2A,0x40,0x14,0x40,0x10,0x40,0x28,0xA0,0x24,0xA0,0x45,0x10,0x81,0x10,0x02,0x08,0x04,0x04,0x08,0x02},/*"欢",7*/

"↓",{0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x09,0x20,0x05,0x40,0x07,0xC0,0x03,0x80,0x03,0x80,0x01,0x00,0x01,0x00},/*"↓",10*/

};


typedef struct
{
	unsigned char Index[2];
	char Msk[72];
}FONT_HZ24;

#define hz24_num   50

const FONT_HZ24 Hz24X24[hz24_num]={


"1",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x07,0x00,0x3F,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x3F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},/*"1",0*/

"2",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x31,0xC0,0x60,0xE0,0x70,0xE0,0x70,0xE0,0x00,0xE0,0x01,0xC0,0x01,0xC0,0x03,0x80,0x06,0x00,0x0C,0x00,0x18,0x60,0x30,0x60,0x60,0x60,0x7F,0xE0,0x7F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},/*"2",1*/

"3",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x33,0x80,0x71,0xC0,0x71,0xC0,0x71,0xC0,0x01,0xC0,0x03,0x80,0x0F,0x00,0x01,0xC0,0x00,0xC0,0x00,0xE0,0x70,0xE0,0x70,0xE0,0x70,0xE0,0x31,0xC0,0x1F,0x80,0x00,0x00,0x00,0x00,0x00,0x00},/*"3",2*/

"4",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x01,0xC0,0x03,0xC0,0x03,0xC0,0x07,0xC0,0x0D,0xC0,0x0D,0xC0,0x19,0xC0,0x31,0xC0,0x31,0xC0,0x61,0xC0,0x7F,0xF0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x01,0xC0,0x07,0xF0,0x00,0x00,0x00,0x00,0x00,0x00},/*"4",3*/

"5",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xE0,0x3F,0xE0,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x3F,0x80,0x39,0xC0,0x30,0xE0,0x00,0xE0,0x00,0xE0,0x70,0xE0,0x70,0xE0,0x61,0xC0,0x31,0xC0,0x1F,0x80,0x00,0x00,0x00,0x00,0x00,0x00},/*"5",4*/

"6",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x1C,0xE0,0x38,0xE0,0x38,0x00,0x30,0x00,0x70,0x00,0x77,0xC0,0x7C,0xE0,0x78,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x30,0x70,0x38,0x60,0x1C,0xE0,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,0x00},/*"6",5*/

"7",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF0,0x3F,0xF0,0x38,0x60,0x30,0xC0,0x30,0xC0,0x00,0xC0,0x01,0x80,0x01,0x80,0x03,0x00,0x03,0x00,0x03,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"7",6*/

"8",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xC0,0x38,0xE0,0x70,0x70,0x70,0x70,0x70,0x70,0x78,0x60,0x3E,0xE0,0x0F,0x80,0x3B,0xC0,0x30,0xE0,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x38,0xE0,0x0F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00},/*"8",7*/

"9",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x80,0x38,0xC0,0x38,0xE0,0x70,0x60,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0xF0,0x39,0xF0,0x1F,0x70,0x00,0x70,0x00,0xE0,0x00,0xE0,0x38,0xC0,0x39,0xC0,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"9",8*/

"0",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x80,0x1D,0xC0,0x38,0xE0,0x38,0xE0,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x70,0x38,0xE0,0x38,0xE0,0x1D,0xC0,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,0x00},/*"0",9*/

"：",{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x03,0x80,0x00,0x03},
{0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"：",10*/




};


#endif

