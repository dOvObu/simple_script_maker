#ifndef SCRIPTTREE_H
#define SCRIPTTREE_H
#include <map>
#include <memory>
#include <string>
#include <vector>

typedef std::string str_t;

template<typename T>
using vec = std::vector<T>;

template<typename T>
using shptr = std::shared_ptr<T>;

enum class lType {term, actorsdef};

class Term
{
public:
	Term ();
	virtual ~Term ();
	virtual lType getType ();
};

class ActorData
{
public:
	ActorData (){}
	~ActorData (){}
	void setNature (const str_t& nature) {this->nature = nature;}
	str_t getNature () {return nature;}
	void addCostume (const str_t& costume, const str_t& description) {this->costume.push_back (std::pair<std::string, std::string> (costume, description));}
private:
	str_t nature;
	vec<std::pair<str_t,str_t> > costume;
};

class BackActorsData
{
public:
	BackActorsData (){}
	~BackActorsData (){}
};

class ActorsDef : public Term
{
public:
	ActorsDef ();
	virtual ~ActorsDef ();
	virtual lType getType ();
	bool add (const str_t& name, const str_t& alias);
	bool addBackAct (const str_t& nametype, unsigned num);

private:
	std::map<str_t, shptr<ActorData> > actors;
	std::map<str_t, shptr<ActorData> > aliasActors;
	std::map<str_t, std::pair<unsigned, shptr<BackActorsData> > > backActors;
};


#endif // SCRIPTTREE_H
