#ifndef INSTANCE_H
#define INSTANCE_H

#include <stack>


// This singleton registers functions and calls them in reverse order of
// registration when it is destroyed. it is used to destroy other singletons.
class InstancesManager {
	static InstancesManager * singleton_;

	std::stack<void(*)()> destroy_funcs_;

	InstancesManager() {}
	~InstancesManager();
	InstancesManager(const InstancesManager&); // no copy
	InstancesManager & operator=(const InstancesManager&); // no copy
public:
	static InstancesManager & Instance();
	static void DestroyInstance();

	void Push(void(*pf)());
};

#endif
