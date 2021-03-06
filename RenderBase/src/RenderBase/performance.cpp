
#include <RenderBase/performance.h>

#include <algorithm>
#include <thread>
#include <sstream>

using namespace std;
using namespace rb;
using namespace chrono;

//////////////////////////////////////////////////////////////////////////////////
// IntervalPerformanceReport implementation
//////////////////////////////////////////////////////////////////////////////////

void IntervalPerformanceReport::accountFrameReport(const FrameReport& report) {
    auto duration = report.duration();
    end          = max(end, report.end);
    maxFrameTime = max(maxFrameTime, duration);
    minFrameTime = min(minFrameTime, duration);
    averageFrameTime = (frames > 0)
        ? averageFrameTime + ((duration - averageFrameTime) / frames)
        : duration;
    ++frames;
}

string IntervalPerformanceReport::asFormatedString() {
    return (ostringstream()
        << "Measurement interval:   " << durationFSec() << "s\n"
        << "fps:                    " << getFPS() << "\n"
        << "frames:                 " << frames << "\n"
        << "Longest frame:          " << maxFrameTime.count() << " us\n"
        << "shortest frame:         " << minFrameTime.count() << " us\n"
        << "Average frame duration: " << averageFrameTime.count() << "us\n"
    ).str();
}

//////////////////////////////////////////////////////////////////////////////////
// PerformenceAnalyzer implementation
//////////////////////////////////////////////////////////////////////////////////

PerformenceAnalyzer::PerformenceAnalyzer() { }

void PerformenceAnalyzer::capFPS(uint32_t fpsCap) {
    this->fpsCap = fpsCap;
    if (fpsCap == 0) {
        usPerFrame = 0s;
    } else {
        usPerFrame = 1s;
        usPerFrame /= fpsCap;
    }
}

void PerformenceAnalyzer::perPeriodReport(std::chrono::microseconds periodLength, const periodReportCallback_t& callback) {

    auto item = make_shared<PeriodReportItem>(periodLength, callback);

    if (callback == nullptr) {
        auto it = find(periodicReports.begin(), periodicReports.end(), item);
        periodicReports.erase(it);
    } else {
        periodicReports.push_back(item);
        stable_sort(periodicReports.begin(), periodicReports.end());
    }
}

FrameReport PerformenceAnalyzer::frame() {
    lastFrameReport.end = high_resolution_clock::now();

    auto lastFrameDuration = lastFrameReport.duration();

    if (usPerFrame > lastFrameDuration && this->fpsCap > 0) {
        auto delayTime = usPerFrame - lastFrameDuration;
        this_thread::sleep_for(delayTime); // better capping
    }

    for (auto item : periodicReports) {
        item->report.accountFrameReport(lastFrameReport);
        if (item->timeToPublish <= lastFrameReport.end) {
            item->callback(item->report);
            item->timeToPublish += item->periodLength;
            item->report = IntervalPerformanceReport();
        }
    }

    lastFrameReport.begin = high_resolution_clock::now();
    return lastFrameReport;
}
