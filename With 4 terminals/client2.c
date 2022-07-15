
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    int fd2; 
    char * myfifo2 = "/tmp/myfifo2"; 
    mkfifo(myfifo2, 0666); 
    char str2[80];
        fd2 = open(myfifo2,O_RDONLY,0666,0); 
        read(fd2, str2, 80); 
	printf(str2,"%s");
	close(fd2);
} 



