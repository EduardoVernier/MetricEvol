#include "repository.h"

int main(int argc, char *argv[])
{
	string fileName = "/home/eduardo/Desktop/calcuta-android-mirror/";
	char path[256];
	strcpy(path, fileName.c_str());

	Repository repository(path, 0);
}
