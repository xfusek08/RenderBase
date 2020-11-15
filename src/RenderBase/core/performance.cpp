
#include <RenderBase/core/performance.h>
#include <RenderBase/platform/platform.h>

#include <algorithm>

using namespace std;
using namespace rb;
using namespace chrono;


PerformenceAnalyzer::PerformenceAnalyzer() {
    usPerFrame = 1s;
    usPerFrame /= FPSCap;
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

    if (usPerFrame > lastFrameDuration) {
        delay(usPerFrame - lastFrameDuration);
    }

    for (auto item : periodicReports) {
        item->report.accountFrameReport(lastFrameReport);
        if (item->timeToPublish <= lastFrameReport.end) {
            item->callback(item->report);
            item->timeToPublish += item->periodLength;
            item->report = IntervalPerformanceReport();
        }
    }

    lastFrameReport.begin = lastFrameReport.end;
    return lastFrameReport;
}
