
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    int fd3; 
    char * myfifo3 = "/tmp/myfifo3"; 
    mkfifo(myfifo3, 0666); 
    char str3[80];
        fd3 = open(myfifo3,O_RDONLY,0666,0); 
        read(fd3, str3, 80); 
	printf(str3,"%s");
	close(fd3);
} 



