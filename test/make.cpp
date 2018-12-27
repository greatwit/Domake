// test.cpp : 定义控制台应用程序的入口点。
//


#include "FileOpera.h"
#include<fstream>

using namespace std;

void savePath(char *srcPath, string destPath){
	string root = destPath.assign(destPath).append("\\");
    char * distAll  = "path.txt";    //结果保存
    vector<string> dirs, files;           //保存文件路径信息
    ofstream ofn(distAll);          //打开文件
    int size = 0;                   //存储文件个数

	//清空vector
	while(!dirs.empty()) dirs.pop_back();
    while(!files.empty()) files.pop_back();
   

    getAllFiles(srcPath, dirs, files);   //递归查找文件以及文件夹。文件夹路径为filePath
    size = dirs.size();            //包含文件个数
    cout << "dirsize:" << dirs.size() << " filesize:" << files.size() << endl;
	
	int i = 0;
    for (; i < size; i++) {
		string p;
		p.assign(root).append(dirs[i]);
		_mkdir(p.c_str());
	}
	cout << "mkdir num:" << i <<endl;
	i = 0;
	size = files.size();
	int count = 0;
	for (; i < size; i++) {
		string p;
		p.assign(root).append(files[i]).append(".o");
		if(cloneFile(files[i].c_str(), p.c_str())>=0)
			count++;
		if(count%20==0)
			printf("count:%d\n", count);
	}
        //ofn << dirs[i] << endl;    //把文件路径保存
   

    ofn.close();                    //文件关闭
	printf("finished.\n");
}


int main(int argc, char* argv[])
{
	//if(argc<3) {
	//	printf("use exe readpath writepath.\n");
	//	return 0;
	//}
	//_mkdir(argv[2]);
	//cloneFile(argv[1], argv[2]);

	savePath("file", "gen");
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