/*
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
// (i may be forgetting some headers)

using namespace std;

char *buff;
int rd, wr;

int main(){


int fd = open("/dev/ttyACM0", O_RDWR);
if (fd == -1) {
  perror("/dev/ttyACM0");
  return 1;
}

struct termios tios;
tcgetattr(fd, &tios);
// disable flow control and all that, and ignore break and parity errors
tios.c_iflag = IGNBRK | IGNPAR;
tios.c_oflag = 0;
tios.c_lflag = 0;
cfsetspeed(&tios, B9600);
tcsetattr(fd, TCSAFLUSH, &tios);

cout << "About to do a serial test\n";

// the serial port has a brief glitch once we turn it on which generates a
// start bit; sleep for 1ms to let it settle
usleep(1000);    

// output to serial port
char msg[] = "test";
wr = write(fd, msg, strlen(msg));

rd = read(fd, buff, 40);
cout << "Bytes sent are " << wr << '\n';
cout << "Bytes recieved are " << rd << '\n';
cout << "DID IT WORK?\n";
close(fd);
}
*/

/*
#include <stdio.h>
#include <string.h>

char serialPortFilename[] = "/dev/ttyACM0";

int main()
{
    char readBuffer[1024];
    int numBytesRead;

    FILE *serPort = fopen(serialPortFilename, "r");

	if (serPort == NULL)
	{
		printf("ERROR");	
		return 0;
	}

	printf(serialPortFilename);
	printf(":\n");
	while(1)
	{
		memset(readBuffer, 0, 1024);
		fread(readBuffer, sizeof(char),1024,serPort);
		if(sizeof(readBuffer) != 0)
		{
			printf(readBuffer);
		}
	}
	return 0;
}

*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <chrono>

using namespace std;

char serialPortFilename[] = "/dev/ttyACM0";
char readBuffer[1024];
int numBytesRead;


int main()
{
	FILE *serPort = fopen(serialPortFilename, "r+");
	int w = 0;
	int rd = 0;
	auto start = std::chrono::system_clock::now();
    	auto end = std::chrono::system_clock::now();

	if (serPort == NULL)
	{
		printf("ERROR");	
		return 0;
	}

	printf(serialPortFilename);
	printf(":\n");

	char writeBuffer[] = {1};


	while( (std::chrono::duration_cast<std::chrono::seconds>(end - start).count() != 1))
	{
		end = std::chrono::system_clock::now();
		//cout<<"Time is"<<std::chrono::duration_cast<std::chrono::seconds>(end - start).count()<<" second"<<endl;
		memset(readBuffer, 0, 1024);
		rd = fread(readBuffer, sizeof(char),1024,serPort);
		if(sizeof(readBuffer) != 0)
		{
			//cout<< sizeof(readBuffer);
			printf(readBuffer);
		}
		if (readBuffer[0] == 'F' && readBuffer[1] == 'a' && readBuffer[2] == 'i')
			printf("yoMama");
	}
	
	cout << "\nBytes recieved: " << rd << '\n';
	fclose(serPort);
	cout << "Serial Port Closed\n";




	return 0;

}

