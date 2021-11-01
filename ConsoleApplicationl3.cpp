#include <iostream>


struct Load {        //Груз
    std::string contentName;    //Наименование содержимого
    int weight;                 //Вес содержимого
};

void InitLoad(Load &A, std::string B, int C) {    //Инициализация груза
    A.contentName = B;
    A.weight = C;
}

void OutputLoad(Load A) {    //Вывод инф. о грузе
    printf("Тип содержимого: %s\n", A.contentName.c_str());
    printf("Вес содержимого (в одном к-ре): %d\n", A.weight);
}



struct Container {    //Контейнер
    std::string destinationAddress;    //Адрес назначения
    std::string IDNumber;              //Идентификационный номер
    Load load;                         //Груз в контейнере
};

void InitContainer(Container &A, std::string B, std::string C, Load D) {    //Инициализация контейнера
    A.destinationAddress = B;
    A.IDNumber = C;
    A.load = D;
}

void correctContainerID(Container &A, std::string B) {    //Скорректировать ID контейнера
    A.IDNumber = B;
}

void OutputContainer(Container A) {    //Вывод инф. о контейнере
    printf("Адрес назначения: %s\n", A.destinationAddress.c_str());
    printf("Идентификационный номер к-ра: %s\n", A.IDNumber.c_str());
    OutputLoad(A.load);
}



struct Team {     //Команда
    int numberOfPeople;           //Кол-во членов команды
    std::string foremanName;      //Имя бригадира
};

void InitTeam(Team &A, int B, std::string C) {    //Инициализация команды
    A.numberOfPeople = B;
    A.foremanName = C;
}

void OutputTeam(Team A) {    //Вывод инф. о команде
    printf("Кол-во членов команды: %d\n", A.numberOfPeople);
    printf("Имя бригадира: %s\n", A.foremanName.c_str());
}



struct Captain {     //Капитан
    std::string name;             //Имя
    std::string licenseNumber;    //№ лицензии
    Team team;                    //Команда капитана
};

void InitCaptain(Captain& A, std::string B, std::string C, Team D) {    //Инициализация капитана
    A.name = B;
    A.licenseNumber = C;
    A.team = D;
}

void OutputCaptain(Captain A) {    //Вывод инф. о капитане
    printf("Имя капитана: %s\n", A.name.c_str());
    printf("№ лицензии капитана: %s\n", A.licenseNumber.c_str());
    OutputTeam(A.team);
}



struct Ship {               //Корабль
    Container container;      //Тип контейнеров, которые перевозит корабль
    int numberOfContainers;   //Кол-во контейнеров на корабле
    Captain captain;          //Капитан корабля
    bool condition;           //Состояние корабля (приемлемое/нет)
};

void InitShip(Ship &A, Container B, int C, Captain D, bool E) {    //Инициализация корабля
    A.container = B;
    A.numberOfContainers = C;
    A.captain = D;
    A.condition = E;
}

bool CheckViolations(Ship A) {    //Проверить нарушения
    if (!A.condition || A.captain.team.numberOfPeople > 20 || (A.numberOfContainers * A.container.load.weight > 500)) {
        return true;
    }
    else {
        return false;
    }
}

int CalcFee(Ship A) {    //Рассчитать плату за проход
    int fine = 0;
    if (CheckViolations(A)) {
        fine = 5000;
    }

    return (A.numberOfContainers * A.container.load.weight + fine);
}

void AddLoad(Ship &A, int additionalLoad) {    //Добавить груз
    A.numberOfContainers += additionalLoad;
}

void ChangeShipContainers(Ship& A, Container B, int C) {    //Перезагрузить корабль (другими контейнерами)
    A.container = B;
    A.numberOfContainers = C;
}

void OutputShip(Ship A) {    //Вывод всей инф. о корабле
    OutputContainer(A.container);
    printf("Кол-во контейнеров: %d\n", A.numberOfContainers);
    OutputCaptain(A.captain);
    if (A.condition) {
        printf("Состояние приемлимое.\n");
    }
    else {
        printf("Состояние неприемлимое.\n");
    }
}



int main()
{
    setlocale(0, "");

    Load fish;
    Load furniture;
    Container contOne;
    Container contTwo;
    Team teamOne;
    Captain captainOne;
    Ship shipOne;

    InitLoad(fish, "Fish", 50);
    InitLoad(furniture, "Furniture", 100);
    InitContainer(contOne, "-15 20 150", "1234567", fish);
    InitContainer(contTwo, "-150 70 -10", "7654321", furniture);
    InitTeam(teamOne, 10, "Joe");
    InitCaptain(captainOne, "Josh", "1234567", teamOne);
    InitShip(shipOne, contOne, 10, captainOne, true);

    printf("Плата за проход 1: %d\n", CalcFee(shipOne));

    ChangeShipContainers(shipOne, contTwo, 20);

    printf("Плата за проход 2: %d\n", CalcFee(shipOne));

    AddLoad(shipOne, 10);

    printf("Плата за проход 3: %d\n", CalcFee(shipOne));

    Ship* shipTwo = new Ship;
    InitShip(*shipTwo, contTwo, 10, captainOne, false);

    printf("Плата за проход 4: %d\n", CalcFee(*shipTwo));
    printf("\n");

    OutputShip(shipOne);

    return 0;
}
