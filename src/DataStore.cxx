#include "LArCafJobs/DataStore.h"

#include "LArCafJobs/ShapeInfo.h"
#include "LArCafJobs/HistoryContainer.h"
#include "LArCafJobs/DataContainer.h"
#include "LArCafJobs/EventData.h"
#include "LArCafJobs/RunData.h"
#include "LArCafJobs/PersistentAccessor.h"
#include "Identifier/IdentifierHash.h"
#include "TRandom.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>

using std::cout;
using std::endl;

using namespace LArSamples;


DataStore::DataStore()
{
  acc = NULL;
  for (unsigned int i = 0; i < nChannels(); i++) m_cellHistories.push_back(0);
}


DataStore::DataStore(const char* fileName):
  cellcounter(0),
  eventcounter(0),
  runcounter(0)
{
  acc = new PersistentAccessor(fileName);

  for (unsigned int i = 0; i < nChannels(); i++) m_cellHistories.push_back(0);
}
  
  
DataStore::~DataStore()
{
  for (std::vector<HistoryContainer*>::iterator hist = m_cellHistories.begin(); 
       hist != m_cellHistories.end(); hist++) 
    if (*hist) delete *hist;
}


HistoryContainer* DataStore::makeNewHistory(const IdentifierHash& hash, CellInfo* info)
{
  HistoryContainer*& histCont = hist_cont(hash);
  if (histCont) return histCont;
  histCont = new HistoryContainer(info);
  return histCont;
}


bool DataStore::addData(const IdentifierHash& hash, DataContainer* data)
{
  HistoryContainer*& histCont = hist_cont(hash);
  histCont->add(data);
  acc->add(histCont);// this calls Tree->Fill()
  return true;
}


unsigned int DataStore::addEvent(EventData* eventData)
{
  m_events.push_back(eventData);
  return nEvents() - 1;
}


unsigned int DataStore::addRun(RunData* runData)
{
  m_runs.push_back(runData);
  return nRuns() - 1;
}


unsigned int DataStore::size() const
{
  unsigned int size = 0;
 
 for (unsigned int i = 0; i < nChannels(); i++) {
   const HistoryContainer* hist = historyContainer(i);
   if (!hist) continue;
   size += hist->nDataContainers();
 }
 
 return size;
}


unsigned int DataStore::nFilledChannels() const
{
  unsigned int n = 0;
 
 for (unsigned int i = 0; i < nChannels(); i++) {
   const HistoryContainer* hist = historyContainer(i);
   if (!hist) continue;
   n++;
 }
 
 return n;
}


double DataStore::footprint() const 
{  
  double fp = sizeof(*this); 
  for (unsigned int i = 0; i < nChannels(); i++) {
    const HistoryContainer* hist = historyContainer(i);
    if (!hist) continue;
    fp += hist->footprint();
  }
    
  return fp; 
}

bool DataStore::clearEvent()
{
  
  for (unsigned int i = 0; i < nChannels(); i++) {
    HistoryContainer*& hc = hist_cont(i);
    if(!hc)continue;
    acc->add(hc);
    hc->clearData();
    cellcounter++;
  }

 return 1;
}

bool DataStore::writeTrees(const char* fileName)
{
  cout<<"DataStore::writeTrees to file:"<<fileName<<endl;
  // PersistentAccessor* acc = new PersistentAccessor(fileName);

  for (unsigned int i = 0; i < nRuns(); i++) {
    RunData*& r = runData(i);
    acc->addRun(r);
    delete r; r = 0;
    runcounter++;
  }

  for (unsigned int i = 0; i < nEvents(); i++) {
    EventData*& ev = eventData(i);
    acc->addEvent(ev);
    delete ev; ev = 0;
    eventcounter++;
  }
  
  // for (unsigned int i = 0; i < nChannels(); i++) {
  //   HistoryContainer*& hc = hist_cont(i);
  //   acc->add(hc);	
  //   delete hc; hc = 0;
  // }

  
  cout<<"DataStore Summary: "
      <<" N cells : "<<cellcounter
      <<" N events : "<<eventcounter
      <<" N runs : "<<runcounter
      <<endl;

  bool result = acc->save();
  delete acc;
  return result;
}
