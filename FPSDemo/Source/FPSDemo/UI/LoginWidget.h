// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPSDEMO_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

    virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Login")
	void OnConfirmButtonClicked();

private:
    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* m_UsernameTextBox;

    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* m_PasswordTextBox;

    UPROPERTY(meta = (BindWidget))
    class UButton* m_ConfirmButton;
};
