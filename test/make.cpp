// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdio.h>
#include <string.h>


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

int main(int argc, char* argv[])
{
	if(argc<3) {
		printf("use exe readpath writepath.\n");
		return 0;
	}

	cloneFile(argv[1], argv[2]);

	getchar();

	return 0;
}

