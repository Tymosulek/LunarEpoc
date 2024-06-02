// Project Luna Epoch 


#include "LunaUserWidget.h"

void ULunaUserWidget::SetWidgetController(UObject* NewController)
{
	WidgetController = NewController;
	WidgetControllerSet();
}
