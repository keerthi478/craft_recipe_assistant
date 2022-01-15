#include <json.hpp>

enum class RecipeType
{
    CraftingShaped,    // 顺序合成
    CraftingShapeless, // 无序合成
    Smelting,          // 烧炼
    Blasting,          // 冶炼
    CampfireCooking,   // 营火烹饪
    Smoking,           // 烟熏
    Stonecutting,      // 切石
    Smithing,          // 锻造
    Invalid = -1       // 不可用
};

NLOHMANN_JSON_SERIALIZE_ENUM(RecipeType,
                             {{RecipeType::CraftingShaped, "minecraft:crafting_shaped"},
                              {RecipeType::CraftingShapeless, "minecraft:crafting_shapeless"},
                              {RecipeType::Smelting, "minecraft:smelting"},
                              {RecipeType::Blasting, "minecraft:blasting"},
                              {RecipeType::CampfireCooking, "minecraft:campfire_cooking"},
                              {RecipeType::Smoking, "minecraft:smoking"},
                              {RecipeType::Stonecutting, "minecraft:stonecutting"},
                              {RecipeType::Smithing, "minecraft:smithing"},
                              {RecipeType::Invalid, "N/A"}});
class Recipe
{
public:
    Recipe(/* args */);
    ~Recipe();

public:
private:
    RecipeType type;
    std::string group;
};

Recipe::Recipe(/* args */)
{
}

Recipe::~Recipe()
{
}
