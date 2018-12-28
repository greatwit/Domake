// test.cpp : 定义控制台应用程序的入口点。
//


#include "FileOpera.h"
#include<fstream>

using namespace std;



int main(int argc, char* argv[])
{
	//if(argc<3) {
	//	printf("use exe readpath writepath.\n");
	//	return 0;
	//}

	if(argc<2){
		printf("use exe rootpath.\n");
		return 0;
	}

	changeDirAllFilesName(argv[1], "o");



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