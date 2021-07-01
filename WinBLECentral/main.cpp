#include "pch.h"
#include <iostream>
#include "WinBleCentral.h"

int main()
{
	std::cout << "Start Programme" << std::endl;

	WinBleCentral bleCentral;
	
	bleCentral.scan();
	std::cout << "Start Scanning: Press Enter To Quit" << std::endl;
	while (getchar() != '\n');
	
	bleCentral.stop();

    return EXIT_SUCCESS;
}
