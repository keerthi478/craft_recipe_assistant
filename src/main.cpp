#include <iostream>
#include <nlohmann/json.hpp>
#include <ghc/filesystem.hpp>
#include <CImg/CImg.h>
#include <cppcodec/base64_default_url.hpp>

#include "recipe.hpp"
#include "recipe_render.hpp"

constexpr auto test_base64_img {"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAGtklEQVR4XmMYaMBIrgNsYkz+cwtygbV/evWZ4fjK82SZRbImz3z7/++efABb/PfvPzDNL8YLpn98/slwdPlZkswkWrFTiuV/kC1cAhwMPz7/Yvj87isDGwcr2OJ///4xcHCzMzCzMjN8efuVgZOPg2HvrGNEmU1QUWij5//HV56DDRVTFGZ4dPkZAxMzEwMr0PLf338z/P//n4Ffgpfh2/vvDEKyAgwMQGd+ATru+6efDH9+/WE4sfoCXjtwSnoXOf7//vkH2If//4E9DzTwL8PPb78Y2LlYwY4ASbKws4DVcPJygB3z+fUXBm4hSNr4BXQgSJIVqGbHpENY7cIQdEg0hyeuX99/QeL2C4RmYWNm+Pr+G4O8gQzDk6vPwXIicoJg+tX9t+AoYOdiYwA5BiTIzMoElnv39COY5hXhZkB3CNwBbtm2/z88/8jAwcPOAFL48RXQJwKcYI0fnn9iYAZaLiDBx/D90w+gTxkYuAU5GVjYWBjePHjHAEqMIF+ycrAwgAzkAuYOUKiB1IIM+AJ0tIA4L8N3YCKVVBVleA3Us2/OcbDdkPADqvoEDDpQkImriDJ8+/Cd4RcwqH///MMAMpgDmKhAtjIyQtwLkvsDlAMZzsjEyMDCxAx0OBsDOzAhfnjxieHLh7cMvELc4OgCJU4eoINAjgAl2hOrzzP8+wuJUnAUMiABkKsfXXzKwMnPCcbIcqCEBzIcFOdCMgKQkAFaBmKAst+PLz8ZQHKcvOwMLMDcABIHWf4bmBBB7CfAhMzMCgwhYAL+9+s33Gh4CIB8xff4C8NneV4GZhYmho9AwzmACQsc3mCvMjJwA6OEnZuN4eXdN2ADRBWEwDQzMySuOUCWA6PlLbCcYIMm3IcXnjAwAuX//vkHpP8x/P31l4Hj/U9MB3Df+8jAq6DH8P7nHQaQYt6Hnxl+63AwwFIyrygPAyiEQIkQ5AhQFHwFRhXIJD4xHoYv774BHc7MAIpKbn4OhlvHH8AtYWZmAGdbpqefGYBMBl4udrgcE4ylpSDOwPnhHoPg828MoOCEBO0PcDyCChZQuvgGTICgfA5KG6BoAIUayFFcwCgD5XmQ5ffPPma4C8R/gD4FlRVMzIxgX4MsR7YYZi/cAW8+fAWLORkqM/A++ARmg0JB6MV3cIj8/f0XLPYHSINKOxAGJVAQffvEA4YH558y3D/3mIH9HaTs4Pr0iwFUQrK8/AZMdMCSUlga7mtJYV7MENBRFGd49eELw4v3X8CSoBARE+ABs0E+AxWzIB+DogeUyEBZChTs7559ZHh17y04m8JyyZ8ffxggIQiJa+Q4B4XCp28/MR1w5f5LBpCFoJCAWQxSBWILv/zOwHHzHTgkWK+8Zvj59Re40PkDDRVQcczExMQAq5xAoQCyiPszJLWD2D/ePmXABuBRICLADZYHhQSXsikDyCGgEAFhmEa+R5/BjhR99wtcTvADcw0sVTM++cTA9fEXgwQweJHjGsQGBbmarAjYGG5ONoav0BIWJICRBkBRwPX2GgPIQSDfg9IELCRgDgFFDyjXgOTZ3gBDBxi/IIthlnwGBjEIw/igIIcF+4u3nxlAjoCZxYQcLCBLQT6HJUiQHChqsDkCpg9kMet3SLkAswTka5Dln6AOAakF+VoSGjpYQwBmICgKQOxrD16ChWAJE0TD5NDTyWdoogIZDDP8OdCnIDbIgTAxkINYheWQ/cyAkgZgPgdZBApekKWwhAkKdlgOQU4vIMNBPob5EBa8yI4C+RzG//32EcNnbLkAluhAlsAsAgU9zDLkaAGxQeIgdbA8DaJhUQCyAOQoEA2TB/FB8Y+cIFESIYgD8iVyKIDiHyQOC36QHHoUgYIapAYW5CBLQPEPCwnkBAgrA7CWA7AECDLs5ac/4AIJZhmojgCJg/ggX8OiCOQgkEUgDPMtchbkAOYOWLpADnbkRICSC2CWMP/7CS4HQJaBLAHVEchRA86qwLIC5GhYAoNZDApiWGiAcgfMYRLQ4hekHhRKMEfAq+OZ2yDNaaCh/0EGw3IBetYERQcoqkAGIKcLEB8WtLD0ALIMFB2waAKF1NGrj1GagTgbpcFWGv9BJeKDs/sZQIlx3/m7YBqWLmBp4x+wlQSyCLmEA7FhaQHkKJD8hXsviWuUMqABkENAoSAhyMMAsxyWNkBKNx6/wQBL9SA+Mhubj9HNxxkC6ArTvYz/Iwc5LHuevPGEAdnHoOAGFTanT58mymyiHQBzEMghyI678vAVA6wQAgU3ehwzEAAkOwBmHihqQAkSlgZwxTHDYAcA2dZjKRgor78AAAAASUVORK5CYII="};

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
    CImg<uint32_t> img(32, 32, 1, 4);

    cimg_for(img, ptr, uint32_t)
    {
        *ptr = 0xFF5722;
    }

    CImgDisplay disp(img.width(), img.height(), "craft recipe assistant", 0);
    disp.display(img);

    while (!disp.is_closed())
    {
        disp.set_button();
    }

    return 0;
}
