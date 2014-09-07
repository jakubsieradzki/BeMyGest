#pragma once

#include "AbstractArea.h"
#include "UiButtonId.h"
#include "UiButtonProperties.h"

class UiButtonFactory
{
public:
	Button* createButton(UiButtonProperties properties, UiButtonId button_id);

	static UiButtonFactory& instance()
	{
		static UiButtonFactory instance;
		return instance;
	}

private:
	UiButtonFactory() {}
	UiButtonFactory(const UiButtonFactory&) {}
	UiButtonFactory& operator=(const UiButtonFactory&) {}
};