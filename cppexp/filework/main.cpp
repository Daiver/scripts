#include<iostream>
#include<stdio.h>
#include<fstream>

int main(int argc, char** argv)
{
    printf("Start...\n");
    std::ofstream out("myfile.txt"); // Открываем файл для записи
    for (int i = 0; i < 1000000; i++)
    {
        out<<12.012<<" "<<16.12<<"\n"; //Записываем первую строчку
        out<<"UraRabotaet!!!"; //Записываем вторую строчку
        out.flush();
    }
    out.close(); //Закрываем файл
    return 0;
}
