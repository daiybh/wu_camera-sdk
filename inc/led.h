#pragma  once
#include "stdio.h"
#include "stdlib.h"

class LEDFunc {
	typedef enum cmdEnum
	{
		cmd_screen = 0x0AA1,
	}
	cmdEnum;

	static int checkSum(void const *data, size_t length)
	{
		int sum = 0;
		const unsigned char *Da = (const unsigned char *)data;
		for (size_t i = 0; i < length; i++)
		{
			sum += Da[i];
		}
		return sum;
	}

	static int  CmdSendLed(const void *dat, int length, unsigned char *pData)
	{
		struct
		{
			unsigned short stx;
			unsigned short len;
			unsigned short add;
			unsigned short cmd;
			//   data
			unsigned short sum;
			unsigned short eot;
		} pack;

		unsigned char *data = (unsigned char *)dat;

		for (size_t i = 0; i < length; i++)
		{
			data[i] ^= 0xAA;
		}

		pack.stx = 0x0101;
		pack.len = sizeof(pack) + length - 4;
		pack.add = 0xFFFF;
		pack.cmd = 0x0AA1;
		pack.sum = checkSum(&pack.len, 2 * 3);
		pack.eot = 0x0303;
		pack.sum += checkSum(data, length);

		memcpy(pData, (unsigned char *)&pack.stx, 8);
		memcpy(pData + 8, (unsigned char  *)dat, length);
		memcpy(pData + 8 + length, (unsigned char  *)&pack.sum, 4);


		return 8 + 4 + length;
	}
public:
	static int  ledCls(unsigned char *pData)
	{
		const char cls[] = "{\"cmd\":\"clear\",\"param1\":0}";
		return  CmdSendLed(cls, strlen(cls), pData);
	}


	static int  ledText(int row, int ms, const char *text, const char *color, unsigned char *pData)
	{
		char str[1024] = { 0 };
		int len = 0;
		memset(str, 0, 1024);
		len = sprintf(str, "{\"cmd\":\"text\",\"param1\":[{\"ms\":%d,\"priority\":0,\"row\":%d,\"style\":2,\"txt\":\"%s\"",
			ms, row, text);
		if (color)
		{
			len += sprintf(str + len, ",\"color\":\"%s\"", color);
		}
		len += sprintf(str + len, "}]}");
		return  CmdSendLed(str, len, pData);
	}
};