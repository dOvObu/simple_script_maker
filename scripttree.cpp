#include "scripttree.h"

Term::Term (){}
Term::~Term (){}
lType Term::getType (){return lType::term;}

ActorsDef::ActorsDef (){}
ActorsDef::~ActorsDef (){}
lType ActorsDef::getType (){return lType::actorsdef;}
bool ActorsDef::add (const str_t& name, const str_t& alias)
{
	bool ret = false;
	if (actors.count (name) == 0)
	{
		actors[name] = shptr<ActorData>(new ActorData());
		if (!alias.empty ())
		{
			aliasActors[alias] = actors[name];
		}
		ret = true;
	}
	return ret;
}
bool ActorsDef::addBackAct (const str_t& nametype, unsigned num)
{
	bool ret = false;
	if (backActors.count (nametype)==0)
	{
		backActors[nametype] = std::pair<unsigned, shptr<BackActorsData> > (
					num,
					shptr<BackActorsData> (new BackActorsData ()));

		ret = true;
	}
	return ret;
}
