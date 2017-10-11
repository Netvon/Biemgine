#pragma once

#include "bmComponent.h"

#include <map>
#include <iostream>
#include <cassert>

using namespace std;

class bmEntity
{
public:
	bmEntity();
	virtual ~bmEntity();

	template <typename TComponent>
	TComponent getComponent(const string name) const {
		return dynamic_cast<TComponent>(componentHashmap.at(name));
	}

	bool hasComponent(const string name) const {
		return componentHashmap.find(name) != componentHashmap.end();
	}

	void addComponent(const string name, bmComponent * component) {
		componentHashmap.insert(pair<string, bmComponent*>(name, component));
	}

	int getId() const {
		return id;
	}

private:
	int id;
	map<string, bmComponent*> componentHashmap;
};
