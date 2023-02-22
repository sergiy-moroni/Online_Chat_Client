#include "Chat.h"
#if defined(_WIN32) 
#define PLATFORM_NAME "windows 32-bit" // Windows 32-bit
#elif defined(_WIN64)
#define PLATFORM_NAME "windows 64-bit" // Windows 64-bit
#elif defined(__linux__)
#define PLATFORM_NAME "linux"     
#endif
using namespace std;

int main()
{
	cout << PLATFORM_NAME << endl;
	setlocale(LC_ALL, "Rus");
	Chat ch;
	ch.start();
	return 0;
}
