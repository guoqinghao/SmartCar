#include "pbdata.h"
//***********用户使用次数记录******************
void user_n_write(u32 data)
{
   //解锁
	FLASH_Unlock();
	//清除标志位
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
	FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	//要擦出页的起始地址
	FLASH_ErasePage(0x0807F800);
	//写数据
	FLASH_ProgramWord(0x0807F800,data);
	//锁定
	FLASH_Lock();	
}
//******************用户使用次数读取*******************
u32 user_n_read(void)
{
	u32 data=0;
	data=(*(__IO uint32_t*)(0x0807F800));
	return data;
}













