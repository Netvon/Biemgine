#include "UIButtonListBuilder.h"
#include "ButtonUIEntity.h"

namespace spacebiem
{
    UIButtonListBuilder::UIButtonListBuilder(
        initializer_list<UIButtonDef> buttonDefs,
        Color backgroundColor
    ) : buttonDefs(buttonDefs)
    {

    }

    vector<int> UIButtonListBuilder::build(shared_ptr<EntityManager> placeIn, UIButtonList listDef)
    {
        auto count = 0;
        vector<int> ids;

        for (auto& def : buttonDefs) {

            auto x = listDef.startX;
            auto y = listDef.startY;

            if (listDef.stackMode == StackMode::Vertical) {
                y += ((def.buttonSize.height + listDef.hPadding) * count);
            }
            else {
                x += ((def.buttonSize.width + listDef.wPadding) * count);
            }

            int id = placeIn->addEntity<ButtonUIEntity>(x, y, listDef.buttonColor, listDef.textColor, def.text, listDef.texture, def.onClick);
            ids.push_back(id);

            count++;
        }

        return ids;
    }
}
