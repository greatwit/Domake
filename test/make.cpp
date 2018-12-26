// test.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include <iostream>  
#include <stdlib.h> //_MAX_PATH, system()
#include <stdio.h>  
#include <string.h>  
#include <vector>
#include <string>

#ifdef linux  
#include <unistd.h>  
#include <dirent.h>  
#endif  
#ifdef WIN32  
#include <direct.h> //_getcwd(), _chdir()
#include <io.h> //_finddata_t, _findfirst(), _findnext(), _findclose()
#endif  
using namespace std;  

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

/**
 * @function: ��ȡcate_dirĿ¼�µ������ļ���
 * @param: cate_dir - string����
 * @result��vector<string>����
*/
vector<string> getFiles(string cate_dir)
{
	vector<string> files;//����ļ���
 
#ifdef WIN32
	_finddata_t file;
	long lf;
	//�����ļ���·��
	if ((lf=_findfirst(cate_dir.c_str(), &file)) == -1) {
		cout<<cate_dir<<" not found!!!"<<endl;
	} else {
		while(_findnext(lf, &file) == 0) {
			//����ļ���
			//cout<<file.name<<endl;
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
				continue;
			files.push_back(file.name);
		}
	}
	_findclose(lf);
#endif
 
#ifdef linux
	DIR *dir;
	struct dirent *ptr;
	char base[1000];
 
	if ((dir=opendir(cate_dir.c_str())) == NULL)
        {
		perror("Open dir error...");
                exit(1);
        }
 
	while ((ptr=readdir(dir)) != NULL)
	{
		if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
		        continue;
		else if(ptr->d_type == 8)    ///file
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
			files.push_back(ptr->d_name);
		else if(ptr->d_type == 10)    ///link file
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
			continue;
		else if(ptr->d_type == 4)    ///dir
		{
			files.push_back(ptr->d_name);
			/*
		        memset(base,'\0',sizeof(base));
		        strcpy(base,basePath);
		        strcat(base,"/");
		        strcat(base,ptr->d_nSame);
		        readFileList(base);
			*/
		}
	}
	closedir(dir);
#endif
 
	//���򣬰���С��������
	//sort(files.begin(), files.end());
	return files;
}

int main(int argc, char* argv[])
{
	//if(argc<3) {
	//	printf("use exe readpath writepath.\n");
	//	return 0;
	//}
	//cloneFile(argv[1], argv[2]);

	char current_address[100];  
	memset(current_address, 0, 100);  
	getcwd(current_address, 100); //��ȡ��ǰ·��  
	cout<<current_address<<endl;  
	strcat(current_address, "\\*");  

	vector<string> files=getFiles((string)current_address);  
	for (int i=0; i<files.size(); i++)  
	{  
		cout<<files[i]<<endl;  
	}  

	//cout<<"Hello World"<<endl;  

	cout<<"end..."<<endl;  
	cin.get();  

	getchar();

	return 0;
}


//for linux
//int main(void)  
//{  
//	DIR *dir;  
//	char basePath[100];  
//
//	///get the current absoulte path  
//	memset(basePath, '\0', sizeof(basePath));  
//	getcwd(basePath, 999);  
//	printf("the current dir is : %s\n",basePath);  
//
//
//	cout<<endl<<endl;  
//	vector<string> files=getFiles(basePath);  
//	for (int i=0; i<files.size(); i++)  
//	{  
//		cout<<files[i]<<endl;  
//	}  
//
//
//	cout<<"end..."<<endl<<endl;  
//	return 0;  
//}  