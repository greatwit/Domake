// test.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>

int main(int argc, char* argv[])
{
	if(argc<3) {
		printf("use exe readpath writepath.\n");
		return 0;
	}

	 FILE *prFile = NULL, *pwFile = NULL;
	 if(prFile=fopen(argv[1],"rb")) 
		 printf("open read file: %s successful.\n", argv[1]);
	 else {
	 	 printf("open read file: %s failed\n", argv[1]);
		 return 0;
	 }
		
	 if(pwFile=fopen(argv[2],"wb")) 
		 printf("open write file: %s successful.\n", argv[2]);
	 else {
		 printf("open write file: %s failed\n", argv[2]);
		 fclose(prFile);
		 return 0;
	 }
		 

	char buffer[1024] = {0};
	while(!feof(prFile)) {
		int res = fread(buffer, 1, 1024, prFile);
		fwrite(buffer, res, 1, pwFile);
		//printf("len:%d buffer:%s\n", res, buffer);
	}


	getchar();

	fclose(prFile);
	fclose(pwFile);

	return 0;
}

