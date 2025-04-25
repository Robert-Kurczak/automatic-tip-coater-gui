#ifndef HEATERTESTSRESULTS_HPP
#define HEATERTESTSRESULTS_HPP

#include <gui_generated/containers/HeaterTestsResultsBase.hpp>

class HeaterTestsResults : public HeaterTestsResultsBase
{
public:
    HeaterTestsResults();
    virtual ~HeaterTestsResults() {}

    virtual void initialize();
protected:
};

#endif // HEATERTESTSRESULTS_HPP
