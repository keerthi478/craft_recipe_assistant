#include <nlohmann/json.hpp>
#include <CImg/CImg.h>

class RecipeRender
{
private:
    /* data */
public:
    RecipeRender(/* args */);
    ~RecipeRender();

    // render recipe
    void render(const nlohmann::json &j);
};

RecipeRender::RecipeRender(/* args */)
{
}

RecipeRender::~RecipeRender()
{
}

void render(const nlohmann::json &j)
{
    
}