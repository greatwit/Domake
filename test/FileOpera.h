#ifndef FILE_OPERA_H_
#define FILE_OPERA_H_

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

string getFileExtendName(string filename);


char* substr(const char*str, unsigned start, unsigned end);
bool decideSuffix( char* filePath, char* suffix );
vector<string> getFiles(string cate_dir);

void getAllFiles( string path, vector<string>& dirs, vector<string>& files);
int judgeFileSuffix(string filename, string suffix);
string getPureFilename(string originFilename);
int changeFilename(const char*originName, const char*changedName);


////////////////////////////////////////////using////////////////////////////////////////////

//clone one file to new dir path and change file name
int cloneFile(const char *srcFile, const char* destFile);

//copy all subdirs and files from one dir to other
void copyFilesToNewDir(char *srcDir, string destDir);

//change all files name to specify suffix name,e.g:"o"
void changeDirAllFilesName(char*rootDirPath, string extName);


#endif