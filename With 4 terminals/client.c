
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    int fd1; 
    char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666); 
    char str1[80];
        fd1 = open(myfifo,O_RDONLY,0666,0); 
        read(fd1, str1, 80); 
	printf(str1,"%s");
	close(fd1);
} 



