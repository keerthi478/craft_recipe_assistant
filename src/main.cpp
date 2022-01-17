#include <iostream>
#include <nlohmann/json.hpp>
#include <ghc/filesystem.hpp>
#include <CImg/CImg.h>

#include "recipe.hpp"
#include "recipe_render.hpp"

int main(int argc, char const *argv[])
{
    // ghc/filesystem test
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

    // nlohmann/json test
    nlohmann::json j;
    j["type"] = RecipeType::CampfireCooking;

    std::cout << j.dump(4) << std::endl;

    // CImg test
    using namespace cimg_library;
    CImg<unsigned char> img(640, 400, 1, 3);
    img.fill(0);
    unsigned char purple[] = {255, 0, 255};

    img.draw_text(100, 100, "Hello World", purple);
    img.display("My first CImg code");

    return 0;
}
