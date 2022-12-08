#include "AES.h"






AES::AES(unsigned char Copy_PlainText[], unsigned char Copy_Key[])
{

	//Input Preparation for plain text
	uint8_t* PlainText_R1 = &(Copy_PlainText[0]) + 0;
	uint8_t* PlainText_R2 = &(Copy_PlainText[0]) + 1;
	uint8_t* PlainText_R3 = &(Copy_PlainText[0]) + 2;
	uint8_t* PlainText_R4 = &(Copy_PlainText[0]) + 3;
	//Input Preparation for Key word 0
	uint8_t* Key_R1 = &(Copy_Key[0]) + 0;
	uint8_t* Key_R2 = &(Copy_Key[0]) + 1;
	uint8_t* Key_R3 = &(Copy_Key[0]) + 2;
	uint8_t* Key_R4 = &(Copy_Key[0]) + 3;

	for (int i = 0;i < 4;i++)
	{
		//plain text preparation
		this->PlainText[i]    = *PlainText_R1;
		this->PlainText[i+4]  = *PlainText_R2;
		this->PlainText[i+8]  = *PlainText_R3;
		this->PlainText[i+12] = *PlainText_R4;
		
		PlainText_R1 += 4;
		PlainText_R2 += 4;
		PlainText_R3 += 4;
		PlainText_R4 += 4;
		
		//Key preparation
		this->Key[i]      = *Key_R1;
		this->Key[i + 4]  = *Key_R2;
		this->Key[i + 8]  = *Key_R3;
		this->Key[i + 12] = *Key_R4;

		Key_R1 += 4;
		Key_R2 += 4;
		Key_R3 += 4;
		Key_R4 += 4;
	}

}

void AES::Set_Data(unsigned char Copy_PlainText[], unsigned char Copy_Key[])
{
	//Input Preparation for plain text
	uint8_t* PlainText_R1 = &(Copy_PlainText[0]) + 0;
	uint8_t* PlainText_R2 = &(Copy_PlainText[0]) + 1;
	uint8_t* PlainText_R3 = &(Copy_PlainText[0]) + 2;
	uint8_t* PlainText_R4 = &(Copy_PlainText[0]) + 3;
	//Input Preparation for Key word 0
	uint8_t* Key_R1 = &(Copy_Key[0]) + 0;
	uint8_t* Key_R2 = &(Copy_Key[0]) + 1;
	uint8_t* Key_R3 = &(Copy_Key[0]) + 2;
	uint8_t* Key_R4 = &(Copy_Key[0]) + 3;

	for (int i = 0;i < 4;i++)
	{
		//plain text preparation
		this->PlainText[i]    = *PlainText_R1;
		this->PlainText[i+4]  = *PlainText_R2;
		this->PlainText[i+8]  = *PlainText_R3;
		this->PlainText[i+12] = *PlainText_R4;
		
		PlainText_R1 += 4;
		PlainText_R2 += 4;
		PlainText_R3 += 4;
		PlainText_R4 += 4;
		
		//Key preparation
		this->Key[i]      = *Key_R1;
		this->Key[i + 4]  = *Key_R2;
		this->Key[i + 8]  = *Key_R3;
		this->Key[i + 12] = *Key_R4;

		Key_R1 += 4;
		Key_R2 += 4;
		Key_R3 += 4;
		Key_R4 += 4;
	}









}


void AES::Substitute_Bytes(unsigned char * PlainText)
{
	unsigned  char x = -1;
	unsigned char y = -1;


	for (int i = 0;i < 16;i++)
	{
		x = (unsigned  char) ((PlainText[i] & 0xF0)>>4);
		y= (unsigned  char)(PlainText[i] & 0x0F);

		PlainText[i] = sbox[x][y];
	}

}

void AES::Inv_Substitute_Bytes(unsigned char * PlainText)
{
	unsigned  char x = -1;
	unsigned char y = -1;


	for (int i = 0;i < 16;i++)
	{
		x = (unsigned  char)((PlainText[i] & 0xF0) >> 4);
		y = (unsigned  char)(PlainText[i] & 0x0F);

		PlainText[i] = inv_sbox[x][y];
	}
}

void AES::Shift_Rows(unsigned char * PlainText)
{
	unsigned char temp[4];

	//row 0 Shift for Encryption Circulate Left 0 Byte

	//no change

	
	for (int k = 1;k < 4;k++)
	{
		unsigned char *Row = (&PlainText[0]) + 4*k;
		for (int i = 0;i < 4;i++)
		{
			temp[i] = *Row;
			Row++;
		}

		for (int i = 0;i < 4;i++)
		{
			//row 1 Shift for Encryption Circulate Left 1 Byte
			if(k==1)
			*((&PlainText[0]) + 4*k + i) = temp[(i + 1) % 4];

			//row 2 Shift for Encryption Circulate Left 2 Byte
			if(k==2)
			*((&PlainText[0]) + 4*k + i) = temp[(i + 2) % 4];
			
			//row 3 Shift for Encryption Circulate Left 3 Byte
			if(k==3)
			*((&PlainText[0]) + 4*k + i) = temp[(i + 3) % 4];
		}
	}
	


}

void AES::Inv_Shift_Rows(unsigned char * PlainText)
{
	unsigned char temp[4];

	//row 0 Shift for Encryption Circulate Left 0 Byte

	//no change


	for (int k = 1;k < 4;k++)
	{
		unsigned char *Row = (&PlainText[0]) + 4 * k;
		for (int i = 0;i < 4;i++)
		{
			temp[i] = *Row;
			Row++;
		}

		for (int i = 3;i >=0 ;i--)
		{
			//row 1 Shift for Encryption Circulate Left 1 Byte
			if (k == 1)
			{
				if ((i - 1) < 0)
				{
				*((&PlainText[0]) + 4 * k + i) = temp[(i - 1 + 4)];
				}
				else
				{
				*((&PlainText[0]) + 4 * k + i) = temp[(i - 1)];
				}
				

			}
				

			//row 2 Shift for Encryption Circulate Left 2 Byte
			if (k == 2)
			{
				if ((i - 2) < 0)
				{
					*((&PlainText[0]) + 4 * k + i) = temp[(i - 2 + 4)];
				}
				else
				{
					*((&PlainText[0]) + 4 * k + i) = temp[(i - 2)];
				}
			}


			//row 3 Shift for Encryption Circulate Left 3 Byte
			if (k == 3)
			{
				if ((i - 3) < 0)
				{
					*((&PlainText[0]) + 4 * k + i) = temp[(i - 3 + 4)];
				}
				else
				{
					*((&PlainText[0]) + 4 * k + i) = temp[(i - 3)];
				}
			}
	
		}
	}





}

void AES::Mix_Columns(unsigned char * PlainText)
{

	for (int i = 0;i < 4;i++)
	{
		
		unsigned char temp = 
				(
				(*((&PlainText[0]) + 0 + i)) ^ (*((&PlainText[0]) + 4 + i)) ^ 
				(*((&PlainText[0]) + 8 + i)) ^ (*((&PlainText[0]) + 12 + i))	
				);

		unsigned char temp_s0j = (*((&PlainText[0]) + 0 + i));


		(*((&PlainText[0]) + 0 + i)) =
			(
			(*((&PlainText[0]) + 0 + i)) ^ temp ^
				Mix_Columns_MUL_2[((*((&PlainText[0]) + 0 + i))) ^ ((*((&PlainText[0]) + 4 + i)))]
			);

		(*((&PlainText[0]) + 4 + i)) =
			(
			(*((&PlainText[0]) + 4 + i)) ^ temp ^
				Mix_Columns_MUL_2[((*((&PlainText[0]) + 4 + i))) ^ ((*((&PlainText[0]) + 8 + i)))]
				);

		(*((&PlainText[0]) + 8 + i)) =
			(
			(*((&PlainText[0]) + 8 + i)) ^ temp ^
				Mix_Columns_MUL_2[((*((&PlainText[0]) + 8 + i))) ^ ((*((&PlainText[0]) + 12 + i)))]
				);

		(*((&PlainText[0]) + 12 + i)) =
			(
			(*((&PlainText[0]) + 12 + i)) ^ temp ^
				Mix_Columns_MUL_2[((*((&PlainText[0]) + 12 + i))) ^ temp_s0j]
				);




	}
	



}

void AES::Inv_Mix_Columns(unsigned char * PlainText)
{
	unsigned char Temp_PlainText[16];
	for (int i = 0;i < 16;i++)
	{
		Temp_PlainText[i] = PlainText[i];

	}

	for (int k = 0;k < 4;k++)
	{

		for (int i = 0;i < 4;i++)
		{
			switch(k)
			{
			case 0:
				PlainText[i+4*k] = Mix_Columns_MUL_E[Temp_PlainText[i]] ^ Mix_Columns_MUL_B[Temp_PlainText[i + 4]] ^
					Mix_Columns_MUL_D[Temp_PlainText[i + 8]] ^ Mix_Columns_MUL_9[Temp_PlainText[i + 12]];
				break;

			case 1:
				PlainText[i+4*k] = Mix_Columns_MUL_9[Temp_PlainText[i]] ^ Mix_Columns_MUL_E[Temp_PlainText[i + 4]] ^
					Mix_Columns_MUL_B[Temp_PlainText[i + 8]] ^ Mix_Columns_MUL_D[Temp_PlainText[i + 12]];
				break;
			case 2:
				PlainText[i + 4 * k] = Mix_Columns_MUL_D[Temp_PlainText[i]] ^ Mix_Columns_MUL_9[Temp_PlainText[i + 4]] ^
					Mix_Columns_MUL_E[Temp_PlainText[i + 8]] ^ Mix_Columns_MUL_B[Temp_PlainText[i + 12]];
				break;
			case 3:
				PlainText[i + 4 * k] = Mix_Columns_MUL_B[Temp_PlainText[i]] ^ Mix_Columns_MUL_D[Temp_PlainText[i + 4]] ^
					Mix_Columns_MUL_9[Temp_PlainText[i + 8]] ^ Mix_Columns_MUL_E[Temp_PlainText[i + 12]];
				break;

			}






		}



	}




}

void AES::Add_Round_Key(unsigned char * PlainText, unsigned char Copy_Key[])
{

	for (int i = 0;i < 16;i++)
	{
		PlainText[i] = PlainText[i] ^ Copy_Key[i];

	}


}

void AES::Key_Expansion(void)
{
		//from slides
		//word temp;
	uint32_t temp=-1;
		
	//from slides	
	//	w[i] = (key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3]);
	for (int k = 0;k < 4;k++)
	{
		uint8_t * ptr = (uint8_t *)&(this->word[k]);

		for (int i = 0; i < 4; i++)
		{
			*(ptr + (3 - i)) = this->Key[(4 * i)+k];
		}
	}

		
		//from slides
		//for (i = 4; i < 44; i++)
		//	{
		//		//temp = g(w[i - 1])
		//		temp = w[i - 1];
		//		if (i mod 4 = 0)
		//			temp = SubWord(RotWord(temp)) xor Rcon[i / 4];
		//		w[i] = w[i - 4] xor temp
		//	}

		for (int i = 4; i < 44; i++)
			{
				
			temp = this->word[i - 1];
				if ((i % 4) == 0)
				{
					Rot_Word(&temp);
					Sub_Word(&temp);
					temp = temp ^ Rcon(i / 4);
				}

				this->word[i] = this->word[i - 4] ^ temp;
			}

	
}

void AES::Rot_Word(uint32_t * Copy_word)
{

	    unsigned char temp[4];

		unsigned char *Row = (unsigned char *)Copy_word ;
		for (int i = 3;i >=0;i--)
		{
			temp[i] = *Row;
			Row++;
			
		}



		uint8_t * ptr = (uint8_t *)Copy_word;

		for (int i = 0; i < 4; i++)
		{
			*(ptr + (3-i)) = temp[(i + 1) % 4];
		}

}

void AES::Sub_Word(uint32_t * Copy_word)
{


	unsigned char temp[4] = {0,0,0,0};

	unsigned char *Row = (unsigned char *)Copy_word;
	for (int i = 3;i >= 0;i--)
	{
		temp[i] = *Row;
		unsigned  char x = -1;
		unsigned char y = -1;

		x = (unsigned  char)((temp[i] & 0xF0) >> 4);
		y = (unsigned  char)(temp[i] & 0x0F);

		temp[i] = sbox[x][y];
		
		Row++;
	}

	uint8_t * ptr =(uint8_t *)Copy_word ;
	for (int i = 0; i < 4; i++)
	{
		*(ptr+ (3 - i)) = temp[i];
	}

	

}

uint32_t AES::Rcon(unsigned char num)
{
	uint32_t ret = 0x00000000;
	uint8_t * ptr = (uint8_t *)(&ret);
	ptr += 3;
	switch (num)
	{
	case 1:
		*ptr = 0x01;
		break;
	case 2:
		*ptr = 0x02;
		break;
	case 3:
		*ptr = 0x04;
		break;
	case 4:
		*ptr = 0x08;
		break;
	case 5:
		*ptr = 0x10;
		break;
	case 6:
		*ptr = 0x20;
		break;
	case 7:
		*ptr = 0x40;
		break;
	case 8:
		*ptr = 0x80;
		break;
	case 9:
		*ptr = 0x1B;
		break;
	case 10:
		*ptr = 0x36;
		break;

	}
	return ret;
}

void AES::Encrypt(unsigned char Cipher_Text[])
{
	unsigned char Temp_Key[16];

	Key_Expansion();
	Add_Round_Key(this->PlainText, this->Key);
	//9 rounds from round 1 to 9
	for (int i = 0;i < 9;i++)
	{
		Substitute_Bytes(this->PlainText);
		Shift_Rows(this->PlainText);
		Mix_Columns(this->PlainText);
		
		Prepare_Round_Key(Temp_Key, 4 * (i+1) );
		Add_Round_Key(this->PlainText, Temp_Key);

	}

	//round number 10
	Substitute_Bytes(this->PlainText);
	Shift_Rows(this->PlainText);
	
	Prepare_Round_Key(Temp_Key, 40);
	Add_Round_Key(this->PlainText, Temp_Key);


	//output construction
	uint8_t itr = 0;
	for (int k = 0;k < 4;k++)
	{
		for (int i = 0;i < 4;i++)
		{
			Cipher_Text[itr] = this->PlainText[(4 * i)+k];
			itr++;
		}
	}

}

void AES::Decrypt(unsigned char Decrypt_Text[])
{
	unsigned char Temp_Key[16];

	Key_Expansion();

	Prepare_Round_Key(Temp_Key, 40);
	Add_Round_Key(this->PlainText, Temp_Key);

	//9 rounds from round 1 to 9
	for (int i = 8;i >=0 ;i--)
	{
	
		Inv_Shift_Rows(this->PlainText);
		Inv_Substitute_Bytes(this->PlainText);

		Prepare_Round_Key(Temp_Key, 4 * (i + 1));
		Add_Round_Key(this->PlainText, Temp_Key);

		Inv_Mix_Columns(this->PlainText);

	}

	//round number 10
	Inv_Shift_Rows(this->PlainText);
	Inv_Substitute_Bytes(this->PlainText);
	
	Add_Round_Key(this->PlainText, this->Key);

	//output construction
	uint8_t itr = 0;
	for (int k = 0;k < 4;k++)
	{
		for (int i = 0;i < 4;i++)
		{
			Decrypt_Text[itr] = this->PlainText[(4 * i) + k];
			itr++;
		}
	}



}

void AES::Prepare_Round_Key(unsigned char * Key, int Begin)
{
	for (int k = 0;k < 4;k++)
	{
		uint8_t* ptr = (uint8_t*)((&word[Begin]) + k);
		for (int i = 3;i >= 0;i--)
		{

			Key[(4 * i)+k] = *ptr;
			ptr++;

		}

	}




}



AES::~AES()
{
}
