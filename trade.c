#include "trade.h"

void trade(Player *players, Price price)
{
    int playerInput;
    while (true)
    {
        printf("농작물 판매:1, 씨앗 구매:2, 종료:3\n");
        scanf("%d", &playerInput);

        switch (playerInput)
        {
        case 1:
            sellProduct(players, price);
            printf("판매 완료\n");
            printf("%s의 금액: %d\n", players->name, players->money);
            break;
        case 2:
            purchaseItem(players, price);
            printf("구매 완료\n");
            break;
        case 3:
            printf("거래를 마치고 돌아갑니다.\n");
            return;
        }
    }
}

void sellProduct(Player *player, Price price)
{
    for (int i = 0; i < 14; i++)
    {
        player->money += player->inventory.crop[i] * price.ProductPrice[i]; // 플레이어가 가지고 있는 농작물양 * 현재 농작물 시세
    }
}

void purchaseItem(Player *player, Price price)
{
    int crop;       // 구매할 씨앗 번호
    int seedNumber; // 씨앗 개수
    char fertilizerPurchase;

    printf("구매할 씨앗을 입력하세요: \n");
    printf("사과:0, 복숭아:1, 샤인머스켓:2, 딸기:3, 버섯:4, 쌀:5, 옥수수:6, 밀:7, 콩:8, 고추:9, 고구마:10, 감자:11, 산삼:12, 칡:13\n");
    scanf("%d", &crop);
    printf("씨앗 구매 개수를 입력하세요: \n");
    scanf("%d", &seedNumber);

    if (player->money < price.SeedPrice[crop] * seedNumber)
    {
        printf("금액 부족\n");
        exit(1);
    }

    else
    {
        player->money -= price.SeedPrice[crop] * seedNumber;
        if (player->inventory.booster != 1)
        {
            printf("비료를 구매하시겠습니까?(y 또는 n)\n");
            scanf(" %c", &fertilizerPurchase);

            if (fertilizerPurchase == 'y' || fertilizerPurchase == 'Y')
            {
                if (player->money < FERTILIZER_PRICE)
                {
                    printf("금액이 부족하여 비료를 구매할 수 없습니다. \n");
                    exit(1);
                }
                player->money -= FERTILIZER_PRICE;
            }
        }
    }
}
