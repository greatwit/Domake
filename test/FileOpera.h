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

int cloneFile(const char *srcFile, const char* destFile);
char* substr(const char*str, unsigned start, unsigned end);
bool decideSuffix( char* filePath, char* suffix );
vector<string> getFiles(string cate_dir);

void getAllFiles( string path, vector<string>& dirs, vector<string>& files);

#endif