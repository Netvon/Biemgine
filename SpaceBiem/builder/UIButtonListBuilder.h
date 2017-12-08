#pragma once

#include "stdafx.h"
#include "Biemgine.h"
#include <functional>
#include <string>
#include <initializer_list>
#include <memory>
#include <vector>

using std::string;
using biemgine::EntityManager;
using biemgine::Entity;
using biemgine::Color;

using std::string;
using std::function;
using std::initializer_list;
using std::shared_ptr;

namespace spacebiem
{
    struct UIButtonDef {
        string text;
        Size buttonSize;
        function<void(StateManager*)> onClick = nullptr;
    };

    struct UIButtonList {
        float startX, startY;

        Color buttonColor;
        Color textColor;
        string texture;
        StackMode stackMode = StackMode::Vertical;
        float hPadding = 0, wPadding = 0;
    };

    enum class StackMode {
        Vertical,
        Horizontal
    };

    class UIButtonListBuilder
    {
    public:
        UIButtonListBuilder(
            initializer_list<UIButtonDef> buttonDefs,
            Color backgroundColor = Color::Black().WithAlpha(128)
        );

        vector<int> build(shared_ptr<EntityManager> placeIn, UIButtonList listDef);

    private:
        std::vector<UIButtonDef> buttonDefs;
    };
}
