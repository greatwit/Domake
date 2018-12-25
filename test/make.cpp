// test.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <string.h>
#include <io.h>
#include <iostream>
#include <direct.h>

using namespace std;

int cloneFile(char *srcFile, char* destFile) {
	FILE *prFile = NULL, *pwFile = NULL;
	if(prFile=fopen(srcFile,"rb")) 
		printf("open read file: %s successful.\n", srcFile);
	else {
		printf("open read file: %s failed\n", srcFile);
		return 0;
	}

	if(pwFile=fopen(destFile,"wb")) 
		printf("open write file: %s successful.\n", destFile);
	else {
		printf("open write file: %s failed\n", destFile);
		fclose(prFile);
		return 0;
	}


	char buffer[1024] = {0};
	while(!feof(prFile)) {
		int res = fread(buffer, 1, 1024, prFile);
		fwrite(buffer, res, 1, pwFile);
		//printf("len:%d buffer:%s\n", res, buffer);
	}

	fclose(prFile);
	fclose(pwFile);

	return 0;
}

//求子串
char* substr(const char*str, unsigned start, unsigned end)
{
	unsigned n = end - start;
	static char stbuf[256];
	//复制最后三个字符，即后缀
	strncpy(stbuf, str + start, n);
	//字串最后加上0
	stbuf[n] = 0;
	return stbuf;
}

bool decideSuffix( char* filePath, char* suffix )
{
	char* fileExt;
	char *ptr, c = '.';
	//最后一个出现c的位置
	ptr = strrchr(filePath, c);
	//用指针相减 求得索引
	int pos = ptr-filePath;
	//获取后缀
	fileExt=substr(filePath, pos+1, strlen(filePath));
	//判断后缀是否相同
	if (0==strcmp(fileExt, suffix))
		return true;
	else
		return false;
}

void listFiles(const char * dir)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
	if (handle == -1)
	{
		cout << "Failed to find first file!\n";
		return;
	}

	do
	{
		if (findData.attrib & _A_SUBDIR
			&& strcmp(findData.name, ".") == 0
			&& strcmp(findData.name, "..") == 0
			)    // 是否是子目录并且不为"."或".."
			cout << findData.name << "\t<dir>\n";
		else
			cout << findData.name << "\t" << findData.size << endl;
	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件

	cout << "Done!\n";
	_findclose(handle);    // 关闭搜索句柄
}

int SearchPath(char *pszPath)
{
	int rv = 0;
	rv = chdir(pszPath);
	if (0 != rv)
	{
		printf("func chdir() error\n");
		rv = -1;
		return rv;
	}

	struct _finddata_t data;
	long handle;
	if (-1L == (handle = _findfirst("*.*", &data)))   //成功返回唯一的搜索句柄, 出错返回-1
	{
		return rv;
	}
	do 
	{
		if (data.attrib == _A_SUBDIR )
		{//目录类型
			char szBuf[1024] = {0};
			if (strcmp(data.name, ".") != 0 && strcmp(data.name, "..") != 0)
			{
				sprintf(szBuf, "%s\\%s", pszPath, data.name);
				SearchPath(szBuf);
			}
		}
		else
		{//单个文件
			int nLen = strlen(data.name);
			if (data.name[nLen - 1] == 'p' && data.name[nLen - 2] == 'p' &&
				data.name[nLen - 3] == 'c' &&data.name[nLen - 4] == '.' )
			{//过滤出所有cpp的文件
				printf("   [%s]\n", data.name );
				char szBuf[1024] = {0};
				sprintf(szBuf, "%s\\%s", pszPath, data.name);
				//GetFileLength(szBuf);
			}    
		}
	} while(_findnext( handle, &data ) == 0);     //成功返回0 , 出错返回-1

	_findclose( handle );     // 关闭当前句柄

	return rv;
}

int main(int argc, char* argv[])
{
	if(argc<3) {
		printf("use exe readpath writepath.\n");
		return 0;
	}
	SearchPath(argv[1]);
	//cloneFile(argv[1], argv[2]);

	getchar();

	return 0;
}

