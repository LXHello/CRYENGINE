// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

// *INDENT-OFF* - <hard to read code and declarations due to inconsistent indentation>

namespace uqs
{
	namespace core
	{

		//===================================================================================
		//
		// CHub
		//
		//===================================================================================

		class CHub : public IHub, public ISystemEventListener
		{
		public:
			explicit                                                   CHub();
			                                                           ~CHub();

			// IHub
			virtual void                                               RegisterHubEventListener(IHubEventListener* listener) override;
			virtual void                                               Update() override;
			// the co-variant return types are intended to help getting around casting down along the inheritance hierarchy when double-dispatching is involved
			virtual QueryFactoryDatabase&                              GetQueryFactoryDatabase() override;
			virtual ItemFactoryDatabase&                               GetItemFactoryDatabase() override;
			virtual FunctionFactoryDatabase&                           GetFunctionFactoryDatabase() override;
			virtual GeneratorFactoryDatabase&                          GetGeneratorFactoryDatabase() override;
			virtual InstantEvaluatorFactoryDatabase&                   GetInstantEvaluatorFactoryDatabase() override;
			virtual DeferredEvaluatorFactoryDatabase&                  GetDeferredEvaluatorFactoryDatabase() override;
			virtual CQueryBlueprintLibrary&                            GetQueryBlueprintLibrary() override;
			virtual CQueryManager&                                     GetQueryManager() override;
			virtual CQueryHistoryManager&                              GetQueryHistoryManager() override;
			virtual CUtils&                                            GetUtils() override;
			virtual CEditorService&                                    GetEditorService() override;
			virtual CItemSerializationSupport&                         GetItemSerializationSupport() override;
			virtual datasource::IEditorLibraryProvider*                GetEditorLibraryProvider() override;
			virtual void                                               SetEditorLibraryProvider(datasource::IEditorLibraryProvider* pProvider) override;
			// ~IHub

			bool                                                       HaveConsistencyChecksBeenDoneAlready() const;

		private:
			                                                           UQS_NON_COPYABLE(CHub);

			virtual void                                               OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;

			void                                                       SendHubEventToAllListeners(EHubEvent ev);
			void                                                       DebugDrawHistory2D(int row, const CQueryHistory* whichHistory, const char* descriptiveHistoryName) const;

			static void                                                CmdListFactoryDatabases(IConsoleCmdArgs* pArgs);
			static void                                                CmdListQueryBlueprintLibrary(IConsoleCmdArgs* pArgs);
			static void                                                CmdListRunningQueries(IConsoleCmdArgs* pArgs);
			static void                                                CmdDumpQueryHistory(IConsoleCmdArgs* pArgs);
			static void                                                CmdLoadQueryHistory(IConsoleCmdArgs* pArgs);
			static void                                                CmdClearLiveQueryHistory(IConsoleCmdArgs* pArgs);
			static void                                                CmdClearDeserializedQueryHistory(IConsoleCmdArgs* pArgs);

		private:
			bool                                                       m_consistencyChecksDoneAlready;
			std::list<IHubEventListener*>                              m_eventListeners;
			QueryFactoryDatabase                                       m_queryFactoryDatabase;
			ItemFactoryDatabase                                        m_itemFactoryDatabase;
			FunctionFactoryDatabase                                    m_functionFactoryDatabase;
			GeneratorFactoryDatabase                                   m_generatorFactoryDatabase;
			InstantEvaluatorFactoryDatabase                            m_instantEvaluatorFactoryDatabase;
			DeferredEvaluatorFactoryDatabase                           m_deferredEvaluatorFactoryDatabase;
			CQueryBlueprintLibrary                                     m_queryBlueprintLibrary;
			CQueryHistoryManager                                       m_queryHistoryManager;
			CQueryHistoryInGameGUI                                     m_queryHistoryInGameGUI;
			CQueryManager                                              m_queryManager;
			CEditorService                                             m_editorService;
			CItemSerializationSupport                                  m_itemSerializationSupport;
			datasource::IEditorLibraryProvider*                        m_pEditorLibraryProvider;
			CUtils                                                     m_utils;
		};

		// - this gets set to a valid instance in CHub::CHub() and reset in CHub::~CHub()
		// - only one instance can exist at a time (or an assert() will fail)
		extern CHub*   g_hubImpl;

	}
}
