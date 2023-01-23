#include "instance.h"


InstancesManager * InstancesManager::singleton_ (0);


InstancesManager & InstancesManager::Instance()
{
	if (!singleton_) singleton_ = new InstancesManager;
	return *singleton_;
}


void InstancesManager::DestroyInstance()
{
	delete singleton_;
	singleton_ = 0;
}


InstancesManager::~InstancesManager() {
	while (!destroy_funcs_.empty()) {
		destroy_funcs_.top()();
		destroy_funcs_.pop();
	}
}


void InstancesManager::Push(void(*pf)())
{
	destroy_funcs_.push(pf);
}
