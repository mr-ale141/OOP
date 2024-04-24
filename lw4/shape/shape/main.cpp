#include "ShapeList.h"

#define USE_DEFAULT_FILE_NAME 1

static std::string GetFileName()
{
#if USE_DEFAULT_FILE_NAME
    return "svg.html";
#elif
    std::string str;
    std::cout << "Enter file name for visualization:" << std::endl << ">";
    std::getline(std::cin, str);
    return str;
#endif
}
// max area
int main()
{
    std::string fileName = GetFileName();

    ShapeList shapeList(fileName);

    std::string str;
    std::cout << ">";
    while (std::getline(std::cin, str))
    {
        std::stringstream ss(str);
        if (!shapeList.Add(ss))
            std::cout << "Error!" << std::endl;
        else
            std::cout << "Ok." << std::endl;
        std::cout << ">";
    }

    auto minAreaShape = shapeList.GetMinArea();
    auto minPerimeterShape = shapeList.GetMinPerimeter();

    std::cout << "-----------Min Area is:------------" << std::endl;
    ShapeList::ShowShape(minAreaShape);
    std::cout << "-----------Min Perimeter is:------------" << std::endl;
    ShapeList::ShowShape(minPerimeterShape);
}
