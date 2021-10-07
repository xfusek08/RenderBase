
#pragma once

// data types
namespace App {
    
    struct Config {
        
    };
    
    struct State {
        Config actConfig;
    };
    
    Config configure(int argc, char** argv);
    bool run(const Config& config);
}
