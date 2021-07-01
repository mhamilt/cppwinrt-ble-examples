 /*
 * Bluetooth Central Class
 * 
 * This exmaple aims to scan for and list every possible piece of information it can find about surrounding bluetooth devices. 
 * The structure of the WinBleClass mimic that of the central manager delegate of the CoreBluetooth API
 * 
 */

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
