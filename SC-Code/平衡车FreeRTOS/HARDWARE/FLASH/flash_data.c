#include "pbdata.h"
//***********�û�ʹ�ô�����¼******************
void user_n_write(u32 data)
{
   //����
	FLASH_Unlock();
	//�����־λ
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
	FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	//Ҫ����ҳ����ʼ��ַ
	FLASH_ErasePage(0x0807F800);
	//д����
	FLASH_ProgramWord(0x0807F800,data);
	//����
	FLASH_Lock();	
}
//******************�û�ʹ�ô�����ȡ*******************
u32 user_n_read(void)
{
	u32 data=0;
	data=(*(__IO uint32_t*)(0x0807F800));
	return data;
}













