#pragma once

#include "bmComponent.h"

class bmUIComponent : public bmComponent
{
public:


    template <typename TComponent>
    TComponent getComponentReference() const {
        return dynamic_cast<TComponent>(componentReference);
    }

    void setComponentReference(bmComponent* component);
    //bmComponent* getComponentReference();

private:

    bmComponent* componentReference = nullptr;

};

