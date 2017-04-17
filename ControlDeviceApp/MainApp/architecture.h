#pragma once

class Architecture {

};

/*
	container of states which client want to modify and manage.
*/
class View;
class Model {
public :
	class Serializer;
	virtual void serialize(Serializer& s) {}
	class FileManager;
	virtual void deserialize(FileManager& fm) {}

	void addView(View* view) {}
	class ViewType;
	void removeView(ViewType& vt) {}

	void Update() {}

	static Model* GetCurrentModel() { return _Me; }

private :
	static Model* _Me;
};
Model* Model::_Me = 0;
/*
	presentation of states.
*/
class View {
public :
};
/*
	way which of modify and manage states.
*/
class Controller {
};

/*
	MVC

	Single Model
	Multiple View
		- main View : configurable by client at run-time.
		- section view
			- alarm view
			- IO view
			- manual view
			- teaching view
			- setting view
	Multiple Controller
		- 

*/
#include <list>
class MVCArchitecture : public Architecture {
public :
	virtual void Initialize() {}
	class ModelBuilder {
	public :
		Model* Create() { return nullptr; }
	};
	Model* CreateModel(ModelBuilder* mbuilder) {
		return mbuilder->Create();
	}
	class ViewBuilder {
	public :
		View* Create() { return nullptr; }
	};
	View* CreateView(ViewBuilder* vbuilder) {
		View* pView = vbuilder->Create();

		Model::GetCurrentModel()->addView(pView);

		return pView;
	}
	class ControllerBuilder {
	public :
		Controller* Create() { return nullptr; }
	};
	Controller* CreateController(ControllerBuilder* cbuilder) {
		return cbuilder->Create();
	}

private :
	std::list<Model*> Modellist;
	std::list<View*> Viewlist;
	std::list<Controller*> Controllerlist;
};