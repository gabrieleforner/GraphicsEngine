//
// Created by forner on 21/10/24.
//
#pragma once

#include <iostream>

#ifndef __CONSOLE_H
#define __CONSOLE_H


void printError(const char* message);
void printWarning(const char* message);
void printInfo(const char* message);
void printSuccess(const char* message);

void em_printError(const char* message);
void em_printWarning(const char* message);
void em_printInfo(const char* message);
void em_printSuccess(const char* message);
#endif // !__CONSOLE_H
