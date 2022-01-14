#include <json.hpp>

class Recipe
{
public:
    Recipe(/* args */);
    ~Recipe();

public:
    enum RecipeType
    {
        CraftingShaped,    // 顺序合成
        CraftingShapeless, // 无序合成
        Smelting,          // 烧炼
        Blasting,          // 熔炼
        CampfireCooking,   // 营火
        Smoking,           // 烟熏
        Stonecutting,      // 切石
        Smithing           // 锻造
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(RecipeType,
                                 {{CraftingShaped, "crafting_shaped"},
                                  {CraftingShapeless, "crafting_shapeless"},
                                  {Smelting, "smelting"},
                                  {Blasting, "blasting"},
                                  {CampfireCooking, "campfire_cooking"},
                                  {Smoking, "smoking"},
                                  {Stonecutting, "stonecutting"},
                                  {Smithing, "smithing"}});

private:
};

Recipe::Recipe(/* args */)
{
}

Recipe::~Recipe()
{
}
