/*Задание 2. Модель данных для посёлка
Что нужно сделать
С помощью структур данных создайте подробную модель посёлка.
В посёлке множество участков, каждый имеет уникальный номер.
На каждом участке должен быть расположен как минимум один жилой дом,
но возможны и другие сооружения, такие как гараж, сарай (бытовка)
и баня. Для каждого здания предусмотрена информация о площади,
которую он занимает на участке.
В жилом доме может быть 1–3 этажа, на каждом из этажей — 2–4 комнаты:
спальня, кухня, ванная, детская, гостиная. Для каждой комнаты
предусмотрены данные о площади. Для каждого этажа также есть данные
о высоте потолка. В жилом доме и бане может быть печь с трубой,
информация об этом также должна быть предусмотрена в данных.
Для всех упомянутых сущностей надо объявить соответствующие структуры
данных.
Вначале работы программы пользователь заполняет данные о посёлке:
вводит общее количество участков и далее начинает детализировать каждый
участок.
Для участка сначала заполняется общее количество построек, а затем
детализируются постройки, этажи, комнаты на этажах.
По итогам введённых данных вы можете рассчитать суммарный параметр,
например процент земли, занимаемой постройками, к общей площади всего
посёлка. Главное в этой задаче — не операция подсчёта, а структуры данных.*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//Перечисление комнат дома
enum room_type {
    BEDROOM = 1,
    KITCHEN,
    BATHROOM,
    CHILDRENS_ROOM,
    LIVING_ROOM
};
//Функция получения типа комнаты дома
int сhoosingRoom() {
    std::cout << R"(1 - Bedroom
2 - Kitchen
3 - Bathroom
4 - Childrens room
5 - Living
Choose a room: )";
    unsigned int name_room;
    std::cin >> name_room;
    switch (name_room) {
    case BEDROOM:
        return BEDROOM;
        break;
    case KITCHEN:
        return KITCHEN;
        break;
    case BATHROOM:
        return BATHROOM;
        break;
    case CHILDRENS_ROOM:
        return CHILDRENS_ROOM;
        break;
    case LIVING_ROOM:
        return LIVING_ROOM;
        break;
    default:
        return -1;
        break;
    }
}

//Перечисление построек участка
enum buildings {
    GARAGE = 1,
    BARN,
    BATHHOUSE
};

//Функция получения типа строения участка
int chosingBuiling() {
    std::cout << R"(1 -Ggarage
2 - Barn
3 - Bathhouse
Choose a buildings: )";
    unsigned int name_buildings;
    std::cin >> name_buildings;
    switch (name_buildings) {
    case GARAGE:
        return GARAGE;
        break;
    case BARN:
        return BARN;
        break;
    case BATHHOUSE:
        return BATHHOUSE;
        break;    
    default:
        return -1;
        break;
    }
}

//Структура комнаты
struct room {
    int name{ 0 };
    int square{ 0 };
};

//Структура этажа
struct floors {
    int number_floor{ 0 };
    std::vector <room> premises{};
    float height{ 0 };   
};

//Структура дома
struct house {
    bool oven{ false };
    std::vector <floors> house_layout{};    
};

//Структура построек участка
struct building {
    int name{ 0 };
    int square{ 0 };
    bool oven{ false };
};

//Структура участка
struct region {
    int number{ 0 };
    int square{ 0 };
    house h;
    std::vector <building> build;
};

//Функция контроля соотношения площади участка к площади построек
bool totalArea(int& total_area, int& area) {    
    if ((total_area - area) < 0)
        return false;
    else {
        total_area -= area;
        return true;
    }
}

//Фунция заполнения структуры дома
house creatHouse(int& total_area) {
    house tmp_house;
    std::cout << "Enter the number of floors of the house (from 1 to 3): ";
    int count_floors{ 0 };
    std::cin >> count_floors;
    while (count_floors < 1 || count_floors > 3) {
        std::cout << "Number of floors out of range!";
        std::cin >> count_floors;
    }
    int count_rooms{ 0 };
    int name_room{ 0 };
    for (int j = 0; j < count_floors; j++) {
        tmp_house.house_layout.push_back({});
        std::cout << "Enter the ceiling height: ";
        std::cin >> tmp_house.house_layout[j].height;
        std::cout << "Enter the number of rooms on the " <<  j + 1 << " floor (from 2 to 4): ";
        std::cin >> count_rooms;
        while (count_rooms < 2 || count_rooms > 4) {
            std::cout << "Number of rooms out of range!";
            std::cin >> count_rooms;
        }
        for (int i = 0; i < count_rooms; i++) {
            tmp_house.house_layout[j].premises.push_back({});
            name_room = сhoosingRoom();
            while (!name_room) {
                std::cout << "Incorrecr input!";
                name_room = сhoosingRoom();
            }                
            switch (name_room) {
            case BEDROOM:
                tmp_house.house_layout[j].premises[i].name = BEDROOM;
                std::cout << "Enter the bedroom area: ";
                std::cin >> tmp_house.house_layout[j].premises[i].square;
                while (!totalArea(total_area, tmp_house.house_layout[j].premises[i].square)) {
                    std::cout << "Exceeded the total area of the plot!\n";
                    std::cout << "Enter the bedroom area: ";
                    std::cin >> tmp_house.house_layout[j].premises[i].square;
                }
                break;
            case KITCHEN:
                tmp_house.house_layout[j].premises[i].name = KITCHEN;
                std::cout << "Enter the kitchen area: ";
                std::cin >> tmp_house.house_layout[j].premises[i].square;
                while (!totalArea(total_area, tmp_house.house_layout[j].premises[i].square)) {
                    std::cout << "Exceeded the total area of the plot!\n";
                    std::cout << "Enter the kitchen area: ";
                    std::cin >> tmp_house.house_layout[j].premises[i].square;
                }
                break;
            case BATHROOM:
                tmp_house.house_layout[j].premises[i].name = BATHROOM;
                std::cout << "Enter the bathroom area: ";
                std::cin >> tmp_house.house_layout[j].premises[i].square;
                while (!totalArea(total_area, tmp_house.house_layout[j].premises[i].square)) {
                    std::cout << "Exceeded the total area of the plot!\n";
                    std::cout << "Enter the bathroom area: ";
                    std::cin >> tmp_house.house_layout[j].premises[i].square;
                }
                break;
            case CHILDRENS_ROOM:
                tmp_house.house_layout[j].premises[i].name = CHILDRENS_ROOM;
                std::cout << "Enter the childrens room area: ";
                std::cin >> tmp_house.house_layout[j].premises[i].square;
                while (!totalArea(total_area, tmp_house.house_layout[j].premises[i].square)) {
                    std::cout << "Exceeded the total area of the plot!\n";
                    std::cout << "Enter the childrens room area: ";
                    std::cin >> tmp_house.house_layout[j].premises[i].square;
                }
                break;
            case LIVING_ROOM:
                tmp_house.house_layout[j].premises[i].name = LIVING_ROOM;
                std::cout << "Enter the living room area: ";
                std::cin >> tmp_house.house_layout[j].premises[i].square;
                while (!totalArea(total_area, tmp_house.house_layout[j].premises[i].square)) {
                    std::cout << "Exceeded the total area of the plot!\n";
                    std::cout << "Enter the living room area: ";
                    std::cin >> tmp_house.house_layout[j].premises[i].square;
                }
                break;            
            }
        }
    }    
    std::cout << "The house has a fireplace? Yes/No: ";
    std::cin.ignore(100, '\n');
    std::cin.clear();
    std::string fireplace;
    std::getline(std::cin, fireplace);
    std::transform(fireplace.begin(), fireplace.end(), fireplace.begin(), ::toupper);
    while (true)
    {
        if (fireplace == "YES") {
            tmp_house.oven = true;
            break;
        }            
        else if (fireplace == "NO") {
            tmp_house.oven = true;
            break;
        }
        else {
            std::cout << "Incorrect input!";
            std::cout << "The house has a fireplace? Yes/No: ";            
            std::getline(std::cin, fireplace);
            std::transform(fireplace.begin(), fireplace.end(), fireplace.begin(), ::toupper);
        }
    }
    return tmp_house;
}

//Функция заполнения структуры построек на участке
std::vector <building> creatBildVec(int& total_area) {
    building tmp;
    std::vector <building> tmp_vec;
    std::cout << "Enter the number of buildings on the site: ";
    int count_buildings{ 0 };
    std::cin >> count_buildings;
    for (int i = 0; i < count_buildings; i++) {
        tmp.name = chosingBuiling();
        if (tmp.name == BATHHOUSE) {
            std::cin.ignore(100, '\n');
            std::cin.clear();
            std::cout << "The house has a fireplace? Yes/No: ";
            std::string fireplace;
            std::getline(std::cin, fireplace);
            std::transform(fireplace.begin(), fireplace.end(), fireplace.begin(), ::toupper);
            while (true)
            {
                if (fireplace == "YES") {
                    tmp.oven = true;
                    break;
                }
                else if (fireplace == "NO") {
                    tmp.oven = true;
                    break;
                }
                else {
                    std::cout << "Incorrect input!";
                    std::cout << "The house has a fireplace? Yes/No: ";
                    std::getline(std::cin, fireplace);
                    std::transform(fireplace.begin(), fireplace.end(), fireplace.begin(), ::toupper);
                }
            }
        }
        std::cout << "Enter the building area: ";
        std::cin >> tmp.square;
        while (!totalArea(total_area, tmp.square)) {
            std::cout << "Exceeded the total area of the plot!\n";
            std::cout << "Enter the building area: ";
            std::cin >> tmp.square;
        }
        tmp_vec.push_back(tmp);
    }
    return tmp_vec;
}

//Функция конироля номеров домов поселка
int checkNumberRegion( std::vector <int>& number_region, int& number) {
    std::cout << "Enter the site number: ";
    int num{ 0 };
    std::cin >> number;
    for (auto p : number_region) {
        if (p == number || number < 1)
            return 0;
    }
    number_region.push_back(number);
    return number;
}

//Функция заполняющая структуру участка
region creatRegion(std::vector <int>& number_region) {
    
    region tmp;
    while (!checkNumberRegion(number_region, tmp.number))
        std::cout << "The site number is not set correctly!\n";
    
    std::cout << "Enter the area of the plot: ";    
    std::cin >> tmp.square;
    int total_area = tmp.square;
    tmp.h = creatHouse(total_area);
    tmp.build = creatBildVec(total_area);
    return tmp;
}

//Функция заполнения участков поселка
void creatSettlement(std::vector <region>& reg, std::vector <int>& numbers_region) {
    unsigned int quantity;
    std::cout << "Enter the number of plots: ";
    std::cin >> quantity;    

    for (int i = 0; i < quantity; i++) {
        reg.push_back(creatRegion(numbers_region));
    }
}

//Функция посчета площади построек участков поселка
int sumBildingsSquare(const std::vector <region>& reg) {
    int sum_square{ 0 };
    for (auto p : reg) {
        for (auto pp : p.build) {
            sum_square += pp.square;
        }
        for (auto ppp : p.h.house_layout[0].premises) {
            sum_square += ppp.square;
        }                
    }
    return sum_square;
}

int main()
{
    std::vector <int> number_region;
    int number;
    std::vector <region> reg;
    creatSettlement(reg, number_region);

    std::cout << "\n\nThe total area of buildings in the village is flat " << sumBildingsSquare(reg);
}

