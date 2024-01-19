// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/Debug.h"

Debug::Debug()
{
}

Debug::~Debug()
{
}

void Debug::Print(FString Message)
{
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::White, Message);
}


