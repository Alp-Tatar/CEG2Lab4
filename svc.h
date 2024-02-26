#include "stm32f4xx.h"
#include "stdio.h"
#include <string.h>
#include "stock_exchange.h"
#include "investor.h"

typedef struct {
    investor_t *investor_ptr;
    stock_holding_t *holding_ptr;
} investor_stock_holding_t;

void __svc(0) svc_zero(void *obj);
void __svc(1) svc_one(void *obj);
void __svc(2) svc_two(void *obj);
void __svc(3) svc_three(void *obj);

void __SVC_0(void *obj);
void __SVC_1(void *obj);
void __SVC_2(void *obj);
void __SVC_3(void *obj);
extern  char SVC_Handler_s(void);
void SVC_Handler_c (void *obj, unsigned int svc_number);
