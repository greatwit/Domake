#include <stdio.h>

#include <direct.h> //_getcwd(), _chdir()

#include <stdlib.h> //_MAX_PATH, system()

#include <io.h> //_finddata_t, _findfirst(), _findnext(), _findclose()



void main( void )

{

   char buffer[_MAX_PATH];



   //获取当前工作目录

   if( _getcwd( buffer, _MAX_PATH ) == NULL )

      perror( "_getcwd error" );

   else

      printf( "%s\n", buffer );



   //更改当前工作目录 - 相对路径方式

   if( _chdir( "./temp" ) )

       printf( "Unable to locate the directory you specified \n" );

   else

   {

       _getcwd( buffer, _MAX_PATH ); //重新获取当前工作目录

       printf( "The CWD is: %s\n", buffer ); //输出当前工作目录

       system( "type hello.c"); //system用于执行命令行指令

   }



   //更改当前工作目录 - 绝对路径方式

   if( _chdir( "F:\\temp" ) ) //双反斜杠处理转义字符'\'

       printf( "Unable to locate the directory you specified \n" );

   else

   {

       _getcwd( buffer, _MAX_PATH );

       printf( "\n\nThe CWD is: %s\n", buffer );

       system( "dir *.*");

   }



   //查找当前目录中符合要求的文件, 并输出文件的相关信息

    long hFile;

    _finddata_t fileinfo;

    if ((hFile=_findfirst("*.c",&fileinfo)) != -1L)

    {

        do

        {            

            if (!(fileinfo.attrib & _A_SUBDIR)) //检查是不是目录, 如果不是,则进行处理

            {

                printf("%s, %ul bytes\n", fileinfo.name, fileinfo.size);

            }

        } while (_findnext(hFile,&fileinfo) == 0);

        _findclose(hFile);

    }

}
