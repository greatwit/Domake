// test.cpp : �������̨Ӧ�ó������ڵ㡣
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

//���Ӵ�
char* substr(const char*str, unsigned start, unsigned end)
{
	unsigned n = end - start;
	static char stbuf[256];
	//������������ַ�������׺
	strncpy(stbuf, str + start, n);
	//�ִ�������0
	stbuf[n] = 0;
	return stbuf;
}

bool decideSuffix( char* filePath, char* suffix )
{
	char* fileExt;
	char *ptr, c = '.';
	//���һ������c��λ��
	ptr = strrchr(filePath, c);
	//��ָ����� �������
	int pos = ptr-filePath;
	//��ȡ��׺
	fileExt=substr(filePath, pos+1, strlen(filePath));
	//�жϺ�׺�Ƿ���ͬ
	if (0==strcmp(fileExt, suffix))
		return true;
	else
		return false;
}

void listFiles(const char * dir)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dir, &findData);    // ����Ŀ¼�еĵ�һ���ļ�
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
			)    // �Ƿ�����Ŀ¼���Ҳ�Ϊ"."��".."
			cout << findData.name << "\t<dir>\n";
		else
			cout << findData.name << "\t" << findData.size << endl;
	} while (_findnext(handle, &findData) == 0);    // ����Ŀ¼�е���һ���ļ�

	cout << "Done!\n";
	_findclose(handle);    // �ر��������
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
	if (-1L == (handle = _findfirst("*.*", &data)))   //�ɹ�����Ψһ���������, ������-1
	{
		return rv;
	}
	do 
	{
		if (data.attrib == _A_SUBDIR )
		{//Ŀ¼����
			char szBuf[1024] = {0};
			if (strcmp(data.name, ".") != 0 && strcmp(data.name, "..") != 0)
			{
				sprintf(szBuf, "%s\\%s", pszPath, data.name);
				SearchPath(szBuf);
			}
		}
		else
		{//�����ļ�
			int nLen = strlen(data.name);
			if (data.name[nLen - 1] == 'p' && data.name[nLen - 2] == 'p' &&
				data.name[nLen - 3] == 'c' &&data.name[nLen - 4] == '.' )
			{//���˳�����cpp���ļ�
				printf("   [%s]\n", data.name );
				char szBuf[1024] = {0};
				sprintf(szBuf, "%s\\%s", pszPath, data.name);
				//GetFileLength(szBuf);
			}    
		}
	} while(_findnext( handle, &data ) == 0);     //�ɹ�����0 , ������-1

	_findclose( handle );     // �رյ�ǰ���

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

