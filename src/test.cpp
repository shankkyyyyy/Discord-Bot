#include <iostream>
#include <string>
struct Thing
{
    std::string* name;
    int* age; 
    void Print()
    {
        std::cout << *age << std::endl; 
        return; 
    } 
};
int main()
{
    Thing idk; 
    std::string name = "Hello, World!"; 
    idk.name = &name;
    int agee = 10; 
    idk.age = &agee;
    idk.Print();
    std::cout << idk.name->length() << std::endl; 
    return 0; 
}