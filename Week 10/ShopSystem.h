#ifndef SHOP_SYSTEM_H
#define SHOP_SYSTEM_H

#include <iostream>

class ShopSystem {
public:
    void OpenShop() {
        std::cout << "  [SHOP] offered: Bonus (+2) | cost: 2\n";
        std::cout << "  [SHOP] skipped\n";
    }
};

#endif