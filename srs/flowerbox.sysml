// FlowerBox — модель бизнес-требований, вариантов использования и структуры GUI (SysML v2)
package FlowerBox {

    // ---------- участники ----------
    part def Buyer { doc /* Покупатель: заказывает букеты себе и близким */ }
    part def Recipient { doc /* Получатель букета */ }
    part def ShopBackend { doc /* Сервер магазина: каталог, заказы, бонусы (REST API) */ }
    part def Florist { doc /* Флорист: собирает букет и присылает фото */ }

    // ---------- бизнес-цели ----------
    requirement def BusinessGoal;
    requirement <'BG-1'> mobileSales : BusinessGoal {
        doc /* Не менее 60 % заказов оформляется через приложение */
    }
    requirement <'BG-3'> repeatOrders : BusinessGoal {
        doc /* Не менее 30 % пользователей с важными датами заказывают по напоминанию */
    }

    // ---------- ключевые функциональные требования ----------
    requirement <'REQ-FUNC-003'> catalogFilters {
        doc /* Каталог с категориями, поиском и фильтрами по цене, поводу и цвету */
    }
    requirement <'REQ-FUNC-005'> bouquetBuilder {
        doc /* Конструктор: виды цветов и количество каждого вида */
    }
    requirement <'REQ-FUNC-007'> packaging {
        doc /* Упаковка: минимум листов бумаги считается по числу стеблей,
             * размеры коробки, которые не вместят букет, недоступны */
    }
    requirement <'REQ-FUNC-009'> checkout {
        doc /* Оформление: получатель, адрес или «уточнить у получателя», время, оплата */
    }
    requirement <'REQ-FUNC-011'> dateReminders {
        doc /* Напоминание о важной дате за 1, 3 или 7 дней с подбором букета */
    }

    // ---------- варианты использования ----------
    use case def BrowseCatalog { subject buyer : Buyer; }
    use case def BuildBouquet {
        subject buyer : Buyer;
        doc /* Шаг «расположение» есть только при двух и более видах цветов */
    }
    use case def PlaceOrder {
        subject buyer : Buyer;
        actor backend : ShopBackend;
        include use case browse : BrowseCatalog;
    }
    use case def TrackOrder {
        subject buyer : Buyer;
        actor florist : Florist;
    }
    use case def GetReminder { subject buyer : Buyer; }

    use case def BuyerScenarios {
        part buyer : Buyer;
        part backend : ShopBackend;
        include use case build : BuildBouquet;
        include use case order : PlaceOrder;
        include use case track : TrackOrder;
        include use case remind : GetReminder;
    }

    // ---------- структура GUI ----------
    part def Screen;
    part def BottomCarousel {
        doc /* Живая карусель из 5 вкладок: видно 3, остальные листаются свайпом */
        attribute visibleTabs = 3;
        attribute totalTabs = 5;
    }
    part def FlowerBoxApp {
        part nav : BottomCarousel;
        part home : Screen { doc /* Главная: логотип, поиск, напоминание, акции, по поводу, хиты */ }
        part catalog : Screen { doc /* Каталог с фильтрами */ }
        part builder : Screen { doc /* Собери свой букет: цветы → расположение → упаковка → цвет */ }
        part cart : Screen { doc /* Корзина и оформление заказа */ }
        part profile : Screen { doc /* Профиль: бонусы, избранное, важные даты, заказы */ }
        part product : Screen { doc /* Карточка букета */ }
        part tracking : Screen { doc /* Отслеживание заказа */ }
    }

    part flowerBox : FlowerBoxApp {
        satisfy catalogFilters by catalog;
        satisfy bouquetBuilder by builder;
        satisfy packaging by builder;
        satisfy checkout by cart;
        satisfy dateReminders by profile;
    }
}
