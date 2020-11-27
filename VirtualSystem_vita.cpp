#include "VirtualSystem.h"
#include "VirtualSystem_vita.h"
#include <input/keyboard.h>


VirtualSystem* VirtualSystem::Create ()
{
	return new VirtualSystemVita ();
}

VirtualSystemVita::VirtualSystemVita ()
{

}

VirtualSystemVita::~VirtualSystemVita ()
{

}
