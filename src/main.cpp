#include <iostream>
#include <json.hpp>
#include <filesystem.hpp>

#include "recipe.hpp"
#include "recipe_render.hpp"

int main(int argc, char const *argv[])
{
    ghc::filesystem::path recipePath{"recipes/"};
    for (const auto &recipeIterator : ghc::filesystem::directory_iterator(recipePath))
    {
        auto filepath = recipeIterator.path();
        ghc::filesystem::ifstream ifs(filepath, std::ios::in);

        std::string content{std::istreambuf_iterator<char>(ifs),
                            std::istreambuf_iterator<char>()};

        auto j = nlohmann::json::parse(content);
        auto type = j["type"];
        auto result = type == "minecraft:crafting_shapeless" ||
                              type == "minecraft:crafting_shaped"
                          ? j["result"]["item"]
                          : j["result"];
        std::cout << filepath << ": \n\t"
                  << type << " => " << result << std::endl;
    }

    return 0;
}