#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Cache.h"
#include "DMCache.h"
#include "FAMCache.h"
#include "GAMCache.h"
#include "type.h"

int main(int argc, char* argv[])
{
	// DMCache cache{ 1, 16, 4, 2, 15, 1 };
	// FAMCache cache { 64, 64, 4, 2, 15, 1 };
	int cacheSize = 256;
	int cacheLine = 16;
	GAMCache gamcache{ cacheSize, cacheLine, 4, 2, 15, 1, 4 };
	DMCache dmcache{ cacheSize, cacheLine, 4, 2, 15, 1 };
	FAMCache famcache{ cacheSize, cacheLine, 4, 2, 15, 1 };

	int cacheSize2 = 512;
	int cacheLine2 = 32;
	GAMCache gamcache2{ cacheSize2, cacheLine2, 4, 2, 15, 1, 8 };
	DMCache dmcache2{ cacheSize2, cacheLine2, 4, 2, 15, 1 };
	FAMCache famcache2{ cacheSize2, cacheLine2, 4, 2, 15, 1 };

	int cacheSize1 = 1024;
	int cacheLine1 = 64;
	GAMCache gamcache1{ cacheSize1, cacheLine1, 4, 2, 15, 1, 16 };
	DMCache dmcache1{ cacheSize1, cacheLine1, 4, 2, 15, 1 };
	FAMCache famcache1{ cacheSize1, cacheLine1, 4, 2, 15, 1 };

	FILE* fp;
	const char* fileName = "D:/trace/block_S500_B16_MEM.out/block_S500_B16_MEM.out";
	errno_t err = fopen_s(&fp, fileName, "r");
	if (err != 0)
	{
		fprintf(stderr, "The File is wrong!\n");
		exit(-1);
	}
	
	char mode[30];
	int address;

	int baseAddr = 0x70FF00;
	int loop = 1000;
	int stride = 128;
	int size = 512;

	/*for (int l = 0; l < loop; l++) {
		for (int i = baseAddr; i < baseAddr + size * 4; i += stride * 4) {
			gamcache.read(i);
		}
	}*/

	/*for (int i = 0; i < loop; i++) {
		gamcache.read((baseAddr + i * stride * 4) % size);
	}*/

	while (!feof(fp)) {
		fscanf(fp, "%s %x", &mode, &address);

		if (strcmp(mode, "W") == 0) {
			gamcache.write(address);
			dmcache.write(address);
			famcache.write(address);

			gamcache1.write(address);
			dmcache1.write(address);
			famcache1.write(address);

			gamcache2.write(address);
			dmcache2.write(address);
			famcache2.write(address);
		}
		else if (strcmp(mode, "R") == 0) {
			gamcache.read(address);
			dmcache.read(address);
			famcache.read(address);

			gamcache1.read(address);
			dmcache1.read(address);
			famcache1.read(address);

			gamcache2.read(address);
			dmcache2.read(address);
			famcache2.read(address);
		}
	}
	gamcache.printInfo();
	dmcache.printInfo();
	famcache.printInfo();
	gamcache2.printInfo();
	dmcache2.printInfo();
	famcache2.printInfo();
	gamcache1.printInfo();
	dmcache1.printInfo();
	famcache1.printInfo();

	fclose(fp);

	//DMCache dmcache{ 256, 16, 4, 2, 15, 1};
	//err = fopen_s(&fp, fileName, "r");
	//if (err != 0)
	//{
	//	fprintf(stderr, "The File is wrong!\n");
	//	exit(-1);
	//}

	///*for (int l = 0; l < loop; l++) {
	//	for (int i = baseAddr; i < baseAddr + size * 4; i += stride * 4) {
	//		dmcache.read(i);
	//	}
	//}*/

	///*for (int i = 0; i < loop; i++) {
	//	dmcache.read((baseAddr + i * stride * 4) % size);
	//}*/

	//while (!feof(fp)) {
	//	fscanf(fp, "%s %x", &mode, &address);

	//	if (strcmp(mode, "W") == 0) {
	//		dmcache.write(address);
	//	}
	//	else if (strcmp(mode, "R") == 0) {
	//		dmcache.read(address);
	//	}
	//}
	//dmcache.printInfo();

	//fclose(fp);

	//FAMCache famcache{ 256, 16, 4, 2, 15, 1};
	//err = fopen_s(&fp, fileName, "r");
	//if (err != 0)
	//{
	//	fprintf(stderr, "The File is wrong!\n");
	//	exit(-1);
	//}

	///*for (int l = 0; l < loop; l++) {
	//	for (int i = baseAddr; i < baseAddr + size * 4; i += stride * 4) {
	//		famcache.read(i);
	//	}
	//}*/

	///*for (int i = 0; i < loop; i++) {
	//	famcache.read((baseAddr + i * stride * 4) % size);
	//}*/

	//while (!feof(fp)) {
	//	fscanf(fp, "%s %x", &mode, &address);

	//	if (strcmp(mode, "W") == 0) {
	//		famcache.write(address);
	//	}
	//	else if (strcmp(mode, "R") == 0) {
	//		famcache.read(address);
	//	}
	//}
	//famcache.printInfo();

	//fclose(fp);

	return 0;

}
