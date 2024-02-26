#include <stdlib.h>
#include "stock_exchange.h"
#include "svc.h"
#include "investor.h"
#include "stdio.h"
#include <float.h>

static stock_exchange_t singleton_exchange;

void stock_exchange_init(uint32_t seed){
  int i;
  stock_exchange_t * exchange = &singleton_exchange;
  stock_t* stock = exchange->stocks;
  investor_t *investor = exchange->investors;
  char name_buffer[64];

  memset (exchange, 0, sizeof(stock_exchange_t));
  srand(seed);

  // initialize stocks
  for (i=0; i<NUM_STOCKS; i++) {
    uint16_t price = (rand() * 100. / RAND_MAX); 
    sprintf(name_buffer, "stock%04d", i);
    stock_initial_public_offering (stock, price+10, name_buffer);
    stock_display(stock);
    stock++;
  }
  // initialize investors
  for (i=0; i<NUM_INVESTORS; i++) {
    uint32_t cache = (rand() * 1000. / RAND_MAX); 
    sprintf(name_buffer, "investor%04d", i);
    investor_init (investor, name_buffer, 10000);
    investor_display(investor);
    investor++;
  }
}

stock_t* stock_exchange_get_random_stock(){
  int indx = rand() * 1. * NUM_STOCKS / RAND_MAX;
  if (indx == NUM_STOCKS) indx = NUM_STOCKS - 1;
  return &singleton_exchange.stocks[indx];
}

void stock_exchange_update(uint32_t time){
  uint32_t indx = time & (NUM_INVESTORS-1);
  investor_t *investor = &singleton_exchange.investors[indx];
  investor_add_transaction(investor);
}

void stock_exchange_display_stats(void){

    investor_t *best_investor = NULL;
    investor_t *worst_investor = NULL;
    float best_performance = -FLT_MAX;
    float worst_performance = FLT_MAX;

    uint16_t i;
    uint16_t j;
    uint32_t net_worth;
    float initial_cash;
    float gain_loss_percentage;


    for (i = 0; i < NUM_INVESTORS; i++) {
        investor_t *current_investor = &singleton_exchange.investors[i];

        // Calculate net worth
        net_worth = current_investor->cache;
        for (j = 0; j < MAX_HOLDINGS; j++) {
            if (current_investor->holdings[j].stock != NULL) {
                net_worth += current_investor->holdings[j].quantity * stock_get_cur_value(current_investor->holdings[j].stock);
            }
        }

        // Calculate gain/loss percentage
        initial_cash = current_investor->cache;  // Use the initial cash stored in the cache field
        gain_loss_percentage = ((float)net_worth - initial_cash) * 100 / initial_cash;

        printf("Investor %d - Net Worth: %d, Gain/Loss: %.2f%%\n", current_investor->id, net_worth, gain_loss_percentage);

        // Update best and worst investors
        if (gain_loss_percentage > best_performance) {
            best_performance = gain_loss_percentage;
            best_investor = current_investor;
        }

        if (gain_loss_percentage < worst_performance) {
            worst_performance = gain_loss_percentage;
            worst_investor = current_investor;
         }
     }

    if (best_investor != NULL && worst_investor != NULL) {
        printf("\nBest Performing Investor: Investor %d\n", best_investor->id);
        printf("Worst Performing Investor: Investor %d\n", worst_investor->id);
    }
    printf("\nInvestor Statistics:\n");
    printf ("Number of BUY transactions: %d \n", get_num_buy());
    printf ("Number of SELL transactions: %d \n", get_num_sell());

}




