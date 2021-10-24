#include <iostream>


struct load {        //Груз
    std::string content;    //Наименование содержимого
    int weight;        //Вес содержимого
};

struct container {    //Контейнер
    std::string address;    //Адрес назначения
    load c_load;       //Груз в контейнере
};

struct team {     //Команда
    int number;    //Кол-во членов команды
};

struct captain {     //Капитан
    std::string name;       //Имя
    std::string license;    //№ лицензии
    team c_team;       //Команда капитана
};

struct ship {               //Корабль
    container s_container;    //Контейнеры на корабле
    int ccount;               //Кол-во контейнеров
    captain s_captain;        //Капитан корабля
    bool condition;           //Состояние корабля (приемлемое/нет)
};


void init_ship(ship &A, int a, std::string b, std::string c, int d, std::string e, std::string f, int g, bool h) {    //Инициализация корабля
    A.s_container.c_load.weight = a;
    A.s_container.c_load.content = b;
    A.s_container.address = c;
    A.ccount = d;
    A.s_captain.name = e;
    A.s_captain.license = f;
    A.s_captain.c_team.number = g;
    A.condition = h;
}

bool chk_violations(ship A) {    //Проверить нарушения
    if (!A.condition || A.s_captain.c_team.number > 20 || (A.ccount * A.s_container.c_load.weight > 500)) {
        return true;
    }
    else {
        return false;
    }
}

int calc_fee(ship A) {    //Рассчитать плату за проход
    int fine = 0;
    if (chk_violations(A)) {
        fine = 5000;
    }

    return (A.ccount * A.s_container.c_load.weight + fine);
}

void add_load(ship &A) {    //Добавить груз
    A.ccount++;
}


int main()
{
    setlocale(0, "");

    ship ship_one;
    init_ship(ship_one, 15, "Fish", "-15 20 150", 10, "Joe", "1234567", 8, true);

    printf("Плата за проход 1: %d\n", calc_fee(ship_one));

    ship* ship_two = new ship;
    init_ship(*ship_two, 30, "Boxes", "-150 70 -10", 20, "Jake", "7654321", 2, false);

    printf("Плата за проход 2: %d\n", calc_fee(*ship_two));
   
    add_load(ship_one);

    printf("Плата за проход 3: %d\n", calc_fee(ship_one));

    return 0;
}
