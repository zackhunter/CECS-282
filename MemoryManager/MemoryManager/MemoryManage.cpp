//Zack Hunter
//CECS 282-05
//Project 6 - Memory Manager
//Dec 12, 2017

#include "MemoryManager.h"
#include <iomanip>
#include <iostream>
using namespace std;

namespace MemoryManager
{
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT
	//
	// This is the only static memory that you may use, no other global variables
	// may be created, if you need to save data make it fit in MM_pool
	//
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT

	const int MM_POOL_SIZE = 65536;
	char MM_pool[MM_POOL_SIZE];

	// I have provided this tool for your use
	void memView(int start, int end)
	{
		const unsigned int SHIFT = 8;
		const unsigned int MASK = 1 << SHIFT - 1;

		unsigned int value;	// used to facilitate bit shifting and masking

		cout << "         Pool                     Unsignd  Unsigned " << endl;
		cout << "Mem Add  indx   bits   chr ASCII#  short      int    " << endl;
		cout << "-------- ---- -------- --- ------ ------- ------------" << endl;

		for (int i = start; i <= end; i++)
		{
			cout << (long*)(MM_pool + i) << ':';	// the actual address in hexadecimal
			cout << '[' << setw(2) << i << ']';		// the index into MM_pool

			value = MM_pool[i];
			cout << " ";
			for (int j = 1; j <= SHIFT; j++)	// the bit sequence for this byte (8 bits)
			{
				cout << ((value & MASK) ? '1' : '0');
				value <<= 1;
			}
			cout << " ";

			cout << '|' << *(char*)(MM_pool + i) << "| (";	// the ASCII character of the 8 bits (1 byte)
			cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";// the ASCII number of the character

			cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";// the unsigned short value of 16 bits (2 bytes)
			cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")";	// the unsigned int value of 32 bits (4 bytes)

			cout << endl;
		}
	}

	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void)
	{
		int fh = 0;   
		int IUH = 2;   
		int UH = 4;   
		*(unsigned short*)(MM_pool + fh) = 6;           
		*(unsigned short*)(MM_pool + 6) = MM_POOL_SIZE - 6;   
		*(unsigned short*)(MM_pool + IUH) = 0;       
		*(unsigned short*)(MM_pool + UH) = 0;           
	}

	// Return a pointer inside the memory pool
	// If no chunk can accommodate aSize call onOutOfMemory() 
	void* allocate(int aSize)
	{
		int fh = 0;   
		int IUH = 2;   
		int UH = 4;   
		if (freeMemory() > aSize) 
		{
			int size = aSize + 6;       
			int oldfh = *(unsigned short*)(MM_pool + fh);           
			int oldIUH = *(unsigned short*)(MM_pool + IUH);          
			int nextfh = *(unsigned short*)(MM_pool + fh) + size;   
			int oldPrvLnk = oldIUH + 4;   
			int currNxtLnk = oldfh + 2;   
			int currPrvLnk = oldfh + 4;   
			int currIUH = *(unsigned short*)(MM_pool + IUH); 
			*(unsigned short*)(MM_pool + IUH) = oldfh;      
			*(unsigned short*)(MM_pool + fh) = nextfh;     
			if (oldfh != 6) 
			{
				*(unsigned short*)(MM_pool + oldPrvLnk) = oldfh;
			}
			*(unsigned short*)(MM_pool + currNxtLnk) = oldIUH; 
			*(unsigned short*)(MM_pool + currPrvLnk) = 0;              
			*(unsigned short*)(MM_pool + oldfh) = aSize;
			*(unsigned short*)(MM_pool + nextfh) = MM_POOL_SIZE - nextfh;
			return (void*)(MM_pool + *(unsigned short*)MM_pool - aSize);
		}
		else 
		{
			onOutOfMemory();
			return 0;
		}
	}

	// Free up a chunk previously allocated memory
	void deallocate(void* aPointer)
	{
		int size = MM_pool[((char*)aPointer - MM_pool) - 6] + 6;       
		int index = (char*)aPointer - MM_pool - 6;  
		int currDelNode = index;
		int fh = 0;  
		int IUH = 2;   
		int UH = 4;  
		int nextLink = 2;   
		int prevLink = 4;   
		int prevNode = *(unsigned short*)(MM_pool + currDelNode + nextLink);   
		int nextNode = *(unsigned short*)(MM_pool + currDelNode + prevLink); 
		*(unsigned short*)(MM_pool + prevNode + prevLink) = nextNode;
		*(unsigned short*)(MM_pool + nextNode + nextLink) = prevNode;
		int oldUH = *(unsigned short*)(MM_pool + UH);
		*(unsigned short*)(MM_pool + currDelNode + prevLink) = 0;  
		*(unsigned short*)(MM_pool + currDelNode + nextLink) = oldUH;  																	  
		*(unsigned short*)(MM_pool + oldUH + prevLink) = currDelNode;
		*(unsigned short*)(MM_pool + UH) = currDelNode;
	}

	// Scan the memory pool and return the total free space remaining in bytes
	int freeMemory(void)
	{
		int fh = 0;   
		return MM_POOL_SIZE - *(unsigned short*)(MM_pool + fh);
	}

	// Scan the memory pool and return the total deallocated memory in bytes
	int usedMemory(void)
	{
		int usedMem = 0;
		int nextUsedMem = *(unsigned short*)(MM_pool + 4);
		while (nextUsedMem > 0) 
		{
			usedMem = usedMem + *(unsigned short*)(MM_pool + nextUsedMem) + 6;
			nextUsedMem = *(unsigned short*)(MM_pool + nextUsedMem + 2);
		}
		return usedMem;
	}

	// Scan the memory pool and return the total in use memory
	int inUseMemory(void)
	{
		int totalUsedMem = MM_POOL_SIZE - freeMemory() - 6;
		return totalUsedMem - usedMemory();
	}

	// Return the size (in bytes) associated with this memory address
	int size(void * aPointer)
	{
		unsigned short size = (MM_pool[(char*)aPointer - (char*)MM_pool] + 2);
		return size;
	}

	// This is called when no more memory is available to allocate
	void onOutOfMemory(void)
	{
		std::cerr << "/nMemory pool out of memory" << std::endl;
		cin.get();
		exit(1);
	}
}
