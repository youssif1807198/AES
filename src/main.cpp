#include"AES.h"
#include <iostream>
#include<string.h>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void HextoDec(unsigned char * hex_value)
{
        if(*hex_value=='A' || *hex_value=='a')
        {
            *hex_value=10;

        }
        
        else if(*hex_value=='B' || *hex_value=='b')
        {
            *hex_value=11;

        }
        else if(*hex_value=='C' || *hex_value=='c')
        {
            *hex_value=12;

        }
        else if(*hex_value=='D' || *hex_value=='d')
        {
            *hex_value=13;

        }        
        else if(*hex_value=='E' || *hex_value=='e')
        {
            *hex_value=14;

        }
        else if(*hex_value=='F' || *hex_value=='f')
        {
            *hex_value=15;

        }
        else 
        {
            *hex_value=*hex_value-48;

        }        


}

int main(int argc, char *argv[])
{
    if(argc<5)
    {
        std::cout<<"ERROR IN PASSING ARGUMENTS";
        return 0;


    }

//parsing command line arguments

    //get mode encrypt or decrypt
	std::string  mode           =  (std::string)argv[1] ;
    //get plain text path
    std::string  plain_text_path=  (std::string)argv[2] ;
    //get key path
    std::string  key_path       =  (std::string)argv[3] ;
    //get output path
    std::string  output_path    =  (std::string)argv[4] ;


    int Key_fd=-1;

    unsigned char Prepare_key[32]={0};
    unsigned char key[16]={0};

    
    Key_fd=open(key_path.c_str(),O_RDONLY);


    if(read(Key_fd, (unsigned char *)(&Prepare_key[0]),32) != 32 )
    {
        std::cout<<"ERROR IN KEY FILE";
        return 0;
    }

    for(int i=0;i<32;i++)
    {
        HextoDec(&Prepare_key[i]);
    }

    //fill key to use it either in encrypt or decrypt    
    for(int i=0;i<32;i=i+2)
    {
        key[i/2]=((unsigned char)(Prepare_key[i]<<4)&0xF0)|( (unsigned char)(Prepare_key[i+1]&0x0F) );
    } 

     
    close(Key_fd);
   

 /////////////////////////////////////////////////////////////encryption mode/////////////////////////////////////////////////////////////
if(strcmp(mode.c_str(), "encrypt")==0)
{
    int PlainText_fd=-1;
    int Encrypt_fd=-1;
    int check=-1;
    std::string buff="";

    //buffer for reading plain text
    unsigned char PlainText[16]={0};

    //buffer for cipher text
    unsigned char CipherText[16]={0};
     AES enc(PlainText,key);

    

    PlainText_fd=open(plain_text_path.c_str(),O_RDONLY);
       //open file to write encrypted data
    Encrypt_fd=open(output_path.c_str(),(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH));


      while((check=read(PlainText_fd, (unsigned char *)(&PlainText[0]),16)) != 0) 
    {
        enc.Set_Data(PlainText,key);
        enc.Encrypt(CipherText);

     

    
        for(int i=0;i<16;i++)
        {
            buff=buff + (char)CipherText[i];
        }

        write(Encrypt_fd,buff.c_str(), 16);


        //empty buffer
        buff="";

    } 



}




/////////////////////////////////////////////////////////////decryption mode/////////////////////////////////////////////////////////////
else if(strcmp(mode.c_str(), "decrypt")==0)
{

    int PlainText_fd=-1;
    int Decrypt_fd=-1;
    int check=-1;
    std::string buff="";


    //buffer for reading plain text
    unsigned char PlainText[16]={0};

    //buffer for Decrypted text
    unsigned char DecryptText[16]={0};
    AES dec(PlainText,key);


    PlainText_fd=open(plain_text_path.c_str(),O_RDONLY);
    
    //open file to write encrypted data
    Decrypt_fd=open(output_path.c_str(),(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH));

      while((check=read(PlainText_fd, (unsigned char *)(&PlainText[0]),16)) != 0) 
    {
        dec.Set_Data(PlainText,key);
        dec.Decrypt(DecryptText);

        
    for(int i=0;i<16;i++)
        {
            buff=buff + (char)DecryptText[i];
        }

        write(Decrypt_fd,buff.c_str(), 16);

        //empty buffer
        buff="";



    } 





    } 











    return 0;
}
