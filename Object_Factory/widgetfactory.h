#include <map>
#include <string>
#include "widgetfactoryinterface.h"

class WidgetFactory
{
public:
// Register some default callback functions
	WidgetFactory();
	~WidgetFactory();
// Define a function pointer type that can be used later for extending the object
// factory by adding new typeid and callback_
	typedef WidgetFactoryInterface* (*CreateWidgetCallback)(const QString&);
// Associate a typeid to creation of objects of one corresponding widget. If the type to be registered 
// is not registered yet, the method will register the type, and associate it with the given callback
// and return true; otherwise, the method just return false, meaning the type is registered. In this
// case, either the type has been really registered already, or just it is just a name clashing, a 
// different type id has to be given.
	static bool RegisterWidget(const std::string &type, CreateWidgetCallback callback);
// Dessociate the given type id with its associated callback. If the type id is found and unregistered,
// the method returns true; otherwise, the method throws an exception, and return false.
	static bool UnregisterWidget(const std::string &type);
// Possibly the most important method of object factory, the function for creating objects.
	static WidgetFactoryInterface *CreateWidget(const std::string &type, const QString &ss);
private:
// Use a c++ standard map to manage association between widget typeids and creation of correct widgets
	typedef std::map<const std::string, CreateWidgetCallback> CallbackMap;
// Define the callback map variable, which actually hold associations between type id and callbacks
	static CallbackMap widget_callbacks_;
};

