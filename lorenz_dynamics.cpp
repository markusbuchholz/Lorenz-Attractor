//https://en.wikipedia.org/wiki/Lorenz_system

//// g++ lorenz_dynamics.cpp -o t -I/usr/include/python3.8 -lpython3.8

#include <iostream>
#include <vector>
#include <tuple>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

//--------------------------------------------------------------------------

void plot3D2(std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> system1, std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> system2)
{
    std::vector<double> xX1 = std::get<0>(system1);
    std::vector<double> yY1 = std::get<1>(system1);
    std::vector<double> zZ1 = std::get<2>(system1);
    std::vector<double> xX2 = std::get<0>(system2);
    std::vector<double> yY2 = std::get<1>(system2);
    std::vector<double> zZ2 = std::get<2>(system2);


    plt::plot3(xX1,yY1, zZ1);
    plt::plot3(xX2, yY2, zZ2);
    plt::xlabel("x");
    plt::ylabel("y");
    plt::set_zlabel("z");
    plt::show();
}

//--------------------------------------------------------------------------

void plot3D1(std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> system)
{
    std::vector<double> xX = std::get<0>(system);
    std::vector<double> yY = std::get<1>(system);
    std::vector<double> zZ = std::get<2>(system);

    plt::plot3(xX, yY, zZ);
    plt::xlabel("x");
    plt::ylabel("y");
    plt::set_zlabel("z");
    plt::show();
}

//--------------------------------------------------------------------------

std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> computeDiffEquation(double x0, double y0, double z0)
{

    int duration = 1000;
    double dt = 0.01;
    double psi{10};
    double ro{28};
    double beta {2.667};

    std::vector<double> xX(duration, 0);
    std::vector<double> yY(duration, 0);
    std::vector<double> zZ(duration, 0);

    xX[0] = x0;
    yY[0] = y0;
    zZ[0] = z0;
    

    for (int i = 1; i < duration; i++)
    {

        xX[i] = xX[i - 1] + psi * (yY[i - 1] - xX[i - 1]) * dt;
        yY[i] = yY[i - 1] + (xX[i - 1] * (ro - zZ[i - 1]) - yY[i - 1]) * dt;
        zZ[i] = zZ[i - 1] + (xX[i - 1] * yY[i - 1] - beta * zZ[i - 1]) * dt;
    }

    return std::make_tuple(xX, yY, zZ);
}

//--------------------------------------------------------------------------

int main()
{

    std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> systemVector1 = computeDiffEquation(0, 1, 1.05);
    std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> systemVector2 = computeDiffEquation(0, 1, 1.25);
    //plot3D1(systemVector1);
    plot3D2(systemVector1, systemVector2);
}
