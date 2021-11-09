#include <iostream>


class Load {        //Груз
private:
    std::string contentName;    //Наименование содержимого
    int weight;                 //Вес содержимого

public:
    Load(std::string B, int C);    //Инициализация груза (конструктор)
    Load();
    int GetWeight();
    void Output();    //Вывод инф. о грузе
  
};

Load::Load(std::string B, int C) {
    contentName = B;
    weight = C;
}

Load::Load() {
    contentName = "none";
    weight = 0;
}

int Load::GetWeight() {
    return weight;
}

void Load::Output() {
    printf("Тип содержимого: %s\n", contentName.c_str());
    printf("Вес содержимого (в одном к-ре): %d\n", weight);
}



class Container {    //Контейнер
private:
    std::string destinationAddress;    //Адрес назначения
    std::string IDNumber;              //Идентификационный номер
    Load load;                         //Груз в контейнере

public:
    Container(std::string B, std::string C, Load D);    //Инициализация контейнера (конструктор)
    Container();
    Load GetLoad();
    void correctContainerID(std::string B);    //Скорректировать ID контейнера
    void Output();    //Вывод инф. о контейнере
    
};

Container::Container(std::string B, std::string C, Load D) {
    destinationAddress = B;
    IDNumber = C;
    load = D;
}

Container::Container() {
    destinationAddress = "none";
    IDNumber = "none";
}

Load Container::GetLoad() {
    return load;
}

void Container::correctContainerID(std::string B) {
    IDNumber = B;
}

void Container::Output() {
    printf("Адрес назначения: %s\n", destinationAddress.c_str());
    printf("Идентификационный номер к-ра: %s\n", IDNumber.c_str());
    load.Output();
}



class Team{     //Команда
private:
    int numberOfPeople;           //Кол-во членов команды
    std::string foremanName;      //Имя бригадира

public:
    Team(int B, std::string C);    //Инициализация команды (конструктор)
    Team();
    int GetNumberOfPeople();
    void Output();    //Вывод инф. о команде
};

Team::Team(int B, std::string C) {
    numberOfPeople = B;
    foremanName = C;
}

Team::Team() {
    numberOfPeople = 0;
    foremanName = "none";
}

int Team::GetNumberOfPeople() {
    return numberOfPeople;
}

void Team::Output() {
    printf("Кол-во членов команды: %d\n", numberOfPeople);
    printf("Имя бригадира: %s\n", foremanName.c_str());
}



class Captain{     //Капитан
private:
    std::string name;             //Имя
    std::string licenseNumber;    //№ лицензии
    Team team;                    //Команда капитана

public:
    Captain(std::string B, std::string C, Team D);    //Инициализация капитана (конструктор)
    Captain();
    Team GetTeam();
    std::string GetLicense();
    void Output();    //Вывод инф. о капитане
};

Captain::Captain(std::string B, std::string C, Team D) {
    name = B;
    licenseNumber = C;
    team = D;
}

Captain::Captain() {
    name = "none";
    licenseNumber = "none";
}

Team Captain::GetTeam() {
    return team;
}

std::string Captain::GetLicense() {
    return licenseNumber;
}

void Captain::Output() {
    printf("Имя капитана: %s\n", name.c_str());
    printf("№ лицензии капитана: %s\n", licenseNumber.c_str());
    team.Output();
}



class CaptainDatabase {   //База доступных капитанов (вспомог. класс)
private:
    Captain* Database[5];
    int arrayCounter;

public:
    CaptainDatabase() {
        arrayCounter = 0;
        *Database = {};
    }

    void AddEntry(Captain &A) {
        if (arrayCounter < 5) {
            Database[arrayCounter] = &A;
            arrayCounter++;
        }
    }

    Captain* GetCaptain(std::string licenseNumber) {
        for (int i = 0; i < arrayCounter; i++) {
            if (Database[i]->GetLicense() == licenseNumber) {
                return Database[i];
            }
        }
        return nullptr;
    }

}Database1;    //Объявление базы данных капитанов



class Ship {               //Корабль
private:
    Container container;       //Тип контейнеров, которые перевозит корабль
    int numberOfContainers;    //Кол-во контейнеров на корабле
    std::string assignedCaptainLicense;    //№ лицензии капитана корабля, назначенного на судно
    Captain* captain;          //Капитан корабля
    bool condition;            //Состояние корабля (приемлемое/нет)

public:
    Ship(Container B, int C, std::string D, bool E);    //Инициализация корабля (конструктор)
    Ship();
    void AddLoad(int additionalLoad);    //Добавить груз
    void ChangeShipContainers(Container B, int C);    //Перезагрузить корабль (другими контейнерами)
    bool CheckViolations();    //Проверить нарушения
    int CalcFee();    //Рассчитать плату за проход
    void Output();     //Вывод всей инф. о корабле
};

Ship::Ship(Container B, int C, std::string D, bool E) {
    container = B;
    numberOfContainers = C;
    captain = Database1.GetCaptain(D);
    condition = E;
}

Ship::Ship() {
    numberOfContainers = 0;
    condition = false;
    captain = nullptr;
}

void Ship::AddLoad(int additionalLoad) {
    numberOfContainers += additionalLoad;
}

void Ship::ChangeShipContainers(Container B, int C) {
    container = B;
    numberOfContainers = C;
}

bool Ship::CheckViolations() {
    if (!condition || captain->GetTeam().GetNumberOfPeople() > 20 || (numberOfContainers * container.GetLoad().GetWeight() > 500)) {
        return true;
    }
    else {
        return false;
    }
}

int Ship::CalcFee() {
    int fine = 0;
    if (CheckViolations()) {
        fine = 5000;
    }

    return (numberOfContainers * container.GetLoad().GetWeight() + fine);
}

void Ship::Output() {
    container.Output();
    printf("Кол-во контейнеров: %d\n", numberOfContainers);
    captain->Output();
    if (condition) {
        printf("Состояние приемлимое.\n");
    }
    else {
        printf("Состояние неприемлимое.\n");
    }
}


int main()
{
    setlocale(0, "");

    Load fish("Fish", 50);
    Load furniture("Furniture", 100);
    Container contOne("-15 20 150", "1234567", fish);
    Container contTwo("-150 70 -10", "7654321", furniture);
    Team teamOne(10, "Joe");
    Team teamTwo(5, "Mark");
    Captain captainOne("Josh", "1234567", teamOne);
    Captain captainTwo("Jon", "7654321", teamTwo);

    Database1.AddEntry(captainOne);
    Database1.AddEntry(captainTwo);

    Ship shipOne(contOne, 10, "1234567", true);


    printf("Плата за проход 1: %d\n", shipOne.CalcFee());

    shipOne.ChangeShipContainers(contTwo, 20);

    printf("Плата за проход 2: %d\n", shipOne.CalcFee());

    shipOne.AddLoad(10);

    printf("Плата за проход 3: %d\n", shipOne.CalcFee());

    Ship* shipTwo = new Ship (contTwo, 10, "7654321", false);

    printf("Плата за проход 4: %d\n\n", shipTwo->CalcFee());

    (*shipTwo).Output();

    printf("\nРабота с динамическим массивом объектов: \n");    ///
    Ship* shipArray = new Ship[3]{{contOne, 10, "1234567", true}, {contTwo, 15, "7654321", true}, {contOne, 20, "1234567", true}};

    printf("Плата за проход 5: %d\n\n", shipArray[2].CalcFee());

    shipArray[0].Output();

    delete[] shipArray;

    printf("\nРабота с массивом динамических объектов: \n");    ///

    Ship** shipArray2 = new Ship* [2] {&shipOne, shipTwo};

    shipArray2[0]->AddLoad(10);

    printf("Плата за проход 6: %d\n\n", shipArray2[0]->CalcFee());

    delete[] shipArray2;
    delete shipTwo;

    return 0;
}
