#include "widgetfactory.h"
//-------------------------------------------------------------------------------------------------
WidgetFactory::CallbackMap WidgetFactory::widget_callbacks_;
//-------------------------------------------------------------------------------------------------
WidgetFactory::WidgetFactory()
{
//	RegisterWidget("label",     Widgets0::Create);
//	RegisterWidget("button",    Widgets1::Create);
//	RegisterWidget("line_edit", Widgets2::Create);
}
//-------------------------------------------------------------------------------------------------
WidgetFactory::~WidgetFactory()
{
}
//-------------------------------------------------------------------------------------------------
bool WidgetFactory::RegisterWidget(const std::string &type, CreateWidgetCallback callback)
{
	return widget_callbacks_.insert(CallbackMap::value_type(type, callback)).second;
}
//-------------------------------------------------------------------------------------------------
bool WidgetFactory::UnregisterWidget(const std::string &type)
{
	return widget_callbacks_.erase(type) == 1;
}
//-------------------------------------------------------------------------------------------------
WidgetFactoryInterface*  WidgetFactory::CreateWidget(const std::string &type, const QString &ss)
{
	CallbackMap::const_iterator itr = widget_callbacks_.find(type);
	if (itr == widget_callbacks_.end())
	{// the type is not registered yet, throw exception
		throw std::runtime_error("Unknown Widget Type");
	}
	// if the type is found, invoke the associated callback function
	return (itr->second)(ss);
}
//-------------------------------------------------------------------------------------------------

