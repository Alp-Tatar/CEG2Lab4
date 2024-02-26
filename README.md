# CEG3136 – Lab4: Supervisor Calls Stock Exchange Application

## Overview
This repository contains the completed project for Lab4 in CEG3136, focusing on adding Supervisor call support to a stock exchange application. The project aims to enhance the stock exchange system by enabling transactions between investors and stocks via Supervisor calls, allowing for privileged execution of critical functions.

## Project Structure
- **Source Code:** Contains the source code files for all system components.
- **µVision Project:** The µVision project file containing all project configurations.
- **svc.h:** Header file containing the SVC function prototypes.
- **svc.s:** Assembly file containing the SVC exception handler implementation.
- **svc.c:** C file containing the SVC function implementations.

## System Components
1. **Stock Exchange:** Data structure including publicly traded stocks and registered investors.
2. **Stock:** Holds information related to the publicly traded stocks.
3. **Investor:** Keeps track of cash and stock shares held by an investor.
4. **Investor_Stock_Holding:** Structure containing pointers to an investor and a stock holding.

## User Interface
- Displays system logging of all BUY/SELL transactions performed by investors.
- Dynamically updates share value and statistics of transactions.

## CPU Control
- Sets the thread mode to non-privileged and the handler mode to privileged.
- Uses CONTROL register to control access to CPU features.

## Supervisor Call (SVC)
- SVC instruction raises a supervisor exception, moving the processor from thread/unprivileged mode to handler/privileged mode.
- SVC functions __SVC_0 and __SVC_1 implemented to demonstrate SVC usage.
- Added __SVC_2 and __SVC_3 to call investor_buy and investor_sell functions.

## Tasks Completed
### TASK 0
- Compiled and ran the project, confirming that functions __SVC_0 & __SVC_1 run in handler mode and are privileged.
### TASK 1
1. Added __SVC_2 and __SVC_3 to call investor_buy and investor_sell functions.
2. Packed investor and stock-holding data structures into investor_stock_holding_t for SVC arguments.
3. Ensured transactions took place in privileged handler mode.
### TASK 2
- Enhanced stock_exchange_display_stats function to display gains/losses of all investors and identify best and worst performers.
