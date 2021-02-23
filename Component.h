
class Entity;

class Component
{
	public:
		Entity* owner;
		virtual ~Component(){}
		virtual void initialize() {}
		virtual void update(float delta_time){}
		virtual void render() {}
};

