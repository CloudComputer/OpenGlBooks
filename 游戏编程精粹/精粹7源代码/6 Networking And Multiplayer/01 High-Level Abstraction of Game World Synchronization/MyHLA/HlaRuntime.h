#pragma once

#include "message.h"
#include "ptr.h"

class SynchEntity_S;
class SynchEntity_C;
class SynchViewport_S;

#define DECLARE_HLA_MEMBER(behavior,type,name) \
	private: behavior<type> m_##name##_INTERNAL; \
	public: type get_##name() { return m_##name##_INTERNAL.Get(); } \
	void set_##name(type newVal) { m_##name##_INTERNAL.Set(newVal); } \
	__declspec(property(get=get_##name,put=set_##name)) type name; 

class SynchEntities_S:public map<HLAInstanceID,SynchEntity_S*>
{
};

class SynchViewports_S:public map<HLAInstanceID,SynchViewport_S*>
{
};

/** SynchEntity client-side collection

Note
- Unlike the collection in server-side, this collection has the ownership of the objects. Because the collection items are
created not under control of user. */
class SynchEntities_C:public map<HLAInstanceID,RefCount<SynchEntity_C> >
{
};

class IHlaRuntimeDelegate_S
{
public:
	virtual ~IHlaRuntimeDelegate_S();

	virtual void Send(HLAHostID dest,Protocol protocol,CMessage& message)=0;

	// determines if one synch entity is visible (tangible) to one viewport
	virtual bool IsOneSynchEntityTangibleToOneViewport(SynchEntity_S* entity,SynchViewport_S *viewport)=0;
};

/** Server-side HLA runtime module

Usage
- Create this object 
- Create SWD compiler-generated class instances and associate them to this object */
class CHlaRuntime_S
{
	HLAInstanceID m_instanceIDFactory;
	IHlaRuntimeDelegate_S* m_dg;
public:
	CHlaRuntime_S(IHlaRuntimeDelegate_S* dg);
	~CHlaRuntime_S(void);

	SynchEntities_S m_synchEntities;
	SynchViewports_S m_synchViewports;

	HLAInstanceID CreateInstanceID();
	void FrameMove(double elapsedTime);

	void Check_OneSynchEntity_EveryViewport(SynchEntity_S *entity);
	void Check_EverySynchEntity_OneViewport(SynchViewport_S *viewport);
	void Check_EverySynchEntity_EveryViewport();
private:
	void Check_OneSynchEntity_OneViewport( SynchEntity_S * entity, SynchViewport_S* viewport, CMessage appearMsg, CMessage disappearMsg );
	void Send_INTERNAL(vector<HLAHostID> sendTo,Protocol protocol,CMessage &msg);
public:
	void RemoveOneSynchEntity_INTERNAL(SynchEntity_S* entity);
	void RemoveOneSynchViewport_INTERNAL( SynchViewport_S* entity );
};

class IHlaRuntimeDelegate_C
{
public:
	virtual ~IHlaRuntimeDelegate_C();
	virtual SynchEntity_C* CreateSynchEntityByClassID(HLAClassID classID)=0;
};

/** HLA client-side main runtime

Usage
- Create this object and associate one or more HLA runtime delegates which are generated by SWD compiler.
- Pass the received message to this object by ProcessReceivedMessage(). */
class CHlaRuntime_C
{
	SynchEntity_C* CreateSynchEntityByClassID( HLAClassID classID ,HLAInstanceID instanceID);
	typedef vector<IHlaRuntimeDelegate_C*> DgList;
	DgList m_dgList;
	CString m_lastProcessMessageReport; 
public:
	SynchEntities_C m_synchEntities;

	CHlaRuntime_C() {}
	~CHlaRuntime_C() {}

	void AddDelegate(IHlaRuntimeDelegate_C *dg);
	void ProcessReceivedMessage(CMessage& msg);
	SynchEntity_C* GetSynchEntityByID(HLAInstanceID instanceID);

	CString GetLastProcessMessageReport();
	void Clear();
};

Protocol CombineProtocol(Protocol a,Protocol b);