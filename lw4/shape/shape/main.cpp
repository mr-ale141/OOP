#include "ShapeList.h"
#include "CCanvas.h"

const std::string fileName("svg.html");

int main()
{
    std::string str;
    ShapeList shapeList(fileName);

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
