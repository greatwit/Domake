// test.cpp : 定义控制台应用程序的入口点。
//


#include "FileOpera.h"
#include <fstream>

using namespace std;

void usage() {
	printf("Use exe -e/d rootpath.\nNeed create gen and root directory.\n");
}

int main(int argc, char* argv[])
{
	//if(argc<3) {
	//	printf("use exe readpath writepath.\n");
	//	return 0;
	//}

	if(argc<3){
		usage();
		return 0;
	}
	if(!strcmp(argv[1], "-e")) 
		copyFilesToNewDir(argv[2], "gen");

	else if(!strcmp(argv[1], "-d"))
		changeDirAllFilesName(argv[2], "o");
	else
		usage();


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