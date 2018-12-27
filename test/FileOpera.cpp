#include "FileOpera.h"

int cloneFile(const char *srcFile, const char* destFile) {
	int rest = -1;
	FILE *prFile = NULL, *pwFile = NULL;
	if(prFile=fopen(srcFile,"rb")) {
		//printf("open read file: %s successful.\n", srcFile);
	}
	else {
		printf("open read file: %s failed\n", srcFile);
		return rest;
	}

	if(pwFile=fopen(destFile,"wb")){ 
		//printf("open write file: %s successful.\n", destFile);
	}
	else {
		printf("open write file: %s failed\n", destFile);
		fclose(prFile);
		return rest;
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

/**
 * @function: 获取cate_dir目录下的所有文件名
 * @param: cate_dir - string类型
 * @result：vector<string>类型
*/
vector<string> getFiles(string cate_dir)
{
	vector<string> files;//存放文件名
 
#ifdef WIN32
	_finddata_t file;
	long lf;
	//输入文件夹路径
	if ((lf=_findfirst(cate_dir.c_str(), &file)) == -1) {
		cout<<cate_dir<<" not found!!!"<<endl;
	} else {
		while(_findnext(lf, &file) == 0) {
			//输出文件名
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
 
	//排序，按从小到大排序
	//sort(files.begin(), files.end());
	return files;
}

void getAllFiles( string path, vector<string>& dirs, vector<string>& files)  
{
    long hFile = 0;               //文件句柄
    struct _finddata_t fileinfo;  //文件信息读取结构
    string p;

    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {   
            if((fileinfo.attrib & _A_SUBDIR))    //比较文件类型是否是文件夹
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                {
					string subDir = p.assign(path).append("\\").append(fileinfo.name);
					dirs.push_back(subDir);
                    getAllFiles( subDir, dirs, files);     //如果是文件夹，继续向下遍历
                }
            }  
            else    //是文件
            {               files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  //是文件，将其路径加入到files集合中
            }  
        }while(_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile); 
    } 
}
