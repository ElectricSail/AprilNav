#include <stdio.h>
#include <string.h>
#include <iostream>

char serialPortFilename[] = "/dev/ttyACM0";

using namespace std;

int main()
{
	FILE *serPort = fopen(serialPortFilename, "w");

	if (serPort == NULL)
	{
		printf("ERROR");	
		return 0;
	}

	char writeBuffer[] = "10.23,4.53,24.2,4.24,.52,73.7,346.4,62*";
	cout << writeBuffer<<endl;

	fwrite(writeBuffer, sizeof(char), sizeof(writeBuffer), serPort);
	fclose(serPort);
	return 0;

}
