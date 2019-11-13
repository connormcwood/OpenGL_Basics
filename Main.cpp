#include "GameManager.h"

int main(void)
{
	GameManager* gManager = new GameManager();
	if (gManager->Initilise() == -1) {
		return -1;
	}

	gManager->Run();
	return 0;
}