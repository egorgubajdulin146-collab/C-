#include "funcion.h"

#include <exception>
#include <iostream>

int main(){
    try{
        runProject();
    }
    catch(const ProjectException& error){
        std::cout << "Ошибка проекта: " << error.what() << '\n';
        return 1;
    }
    catch(const std::exception& error){
        std::cout << "Непредвиденная ошибка: " << error.what() << '\n';
        return 1;
    }
    catch(...){
        std::cout << "Непредвиденная ошибка.\n";
        return 1;
    }

    return 0;
}
