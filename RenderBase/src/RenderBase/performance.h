#pragma once

#include <chrono>
#include <functional>
#include <vector>

namespace rb {

    struct TimeDiference {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point end;

        inline std::chrono::microseconds duration()    const { return std::chrono::duration_cast<std::chrono::microseconds>(end - begin); }
        inline float                     durationFSec() const { return std::chrono::duration_cast<std::chrono::duration<float>>(end - begin).count(); }
    };

    struct FrameReport : TimeDiference { };

    struct IntervalPerformanceReport : TimeDiference {
        std::chrono::microseconds averageFrameTime = std::chrono::microseconds::zero();
        std::chrono::microseconds maxFrameTime     = std::chrono::microseconds::min();
        std::chrono::microseconds minFrameTime     = std::chrono::microseconds::max();
        uint32_t                  frames           = 0;

        inline float getFPS() { return float(frames) / durationFSec(); }

        std::string asFormatedString();
        void        accountFrameReport(const FrameReport& report);
    };

    using periodReportCallback_t = std::function<void(IntervalPerformanceReport)>;
    using frameReportCallback_t  = std::function<void(FrameReport)>;

    /**
     * This is an abstract class providing interface and factory method
     * for platform dependent implementation.
     */
    class PerformenceAnalyzer
    {
        public:
            PerformenceAnalyzer();

            FrameReport frame();

            inline FrameReport getLastFrameReport() { return lastFrameReport; }

            void            capFPS(uint32_t fpsCap = 60);
            inline void     unCapFPS()        { capFPS(0); }
            inline uint32_t getFPSCap() const { return fpsCap; }

            void perFrameReport(const periodReportCallback_t& callback);
            void perPeriodReport(std::chrono::microseconds periodLength, const periodReportCallback_t& callback);

            template<typename _rep, typename ratio>
            inline void perPeriodReport(std::chrono::duration<_rep, ratio> periodLength, const periodReportCallback_t& callback) {
                perPeriodReport(std::chrono::duration_cast<std::chrono::microseconds>(periodLength), callback);
            }

        protected:
            uint32_t                  fpsCap              = 0;
            FrameReport               lastFrameReport     = {};
            frameReportCallback_t     frameReportCallback = nullptr;
            std::chrono::microseconds usPerFrame;


            struct PeriodReportItem {
                std::chrono::steady_clock::time_point timeToPublish;
                std::chrono::microseconds             periodLength;
                IntervalPerformanceReport             report;
                periodReportCallback_t                callback;

                PeriodReportItem(std::chrono::microseconds periodLength, const periodReportCallback_t& callback) :
                    periodLength(periodLength),
                    callback(callback),
                    timeToPublish(std::chrono::steady_clock::now() + periodLength),
                    report(IntervalPerformanceReport()) {}

                bool operator<(const PeriodReportItem& other) const { return other.timeToPublish < other.timeToPublish; }
                bool operator==(const PeriodReportItem& other) const { return periodLength == other.periodLength; }
            };
            std::vector<std::shared_ptr<PeriodReportItem>> periodicReports = {};
    };
}